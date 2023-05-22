//
// Created by wison on 2022/8/21.
//

#include "AudioDecode.h"

AudioDecode::AudioDecode() {
    m_mediaType = TYPE_AUDIO;
}

void AudioDecode::setAudioRender(AudioRender *render) {
    m_render = render;
}

void AudioDecode::onInfoReady() {
    m_swrContext = swr_alloc_set_opts(NULL, AUDIO_CHANNEL_COUNT, AUDIO_SAMPLE_FMT, AUDIO_DST_SAMPLE_RATE,
                       m_codecContext->channel_layout, m_codecContext->sample_fmt,
                       m_codecContext->sample_rate, 0, nullptr);
    swr_init(m_swrContext);

    int channelCount = av_get_channel_layout_nb_channels(AUDIO_CHANNEL_COUNT);
    int resample = (int) av_rescale_rnd(m_codecContext->frame_size, AUDIO_DST_SAMPLE_RATE,
                                      m_codecContext->sample_rate, AV_ROUND_UP);

    m_bufferSize = av_samples_get_buffer_size(nullptr, channelCount, m_codecContext->frame_size, AUDIO_SAMPLE_FMT, 0);
    m_buffer = (uint8_t*) malloc(m_bufferSize);

    m_render->init(m_env, m_bufferSize);

    LOG_D("sample_rate = %d", m_codecContext->frame_size);
    LOG_D("channelCount = %d", channelCount);
    LOG_D("buffer size = %d", m_bufferSize);
}

int AudioDecode::doDecode() {
    while (av_read_frame(m_fmContext, m_packet) >= 0) {
        if (m_packet->stream_index != m_streamIndex) {
            av_packet_unref(m_packet);
            continue;
        }
        int res = avcodec_send_packet(m_codecContext, m_packet);
        if (res < 0) {
            LOG_D("AudioDecode avcodec_send_packet error");
            av_packet_unref(m_packet);
            return -1;
        }
        int frameCount = 0;
        while (avcodec_receive_frame(m_codecContext, m_frame) >= 0) {
            updateTimeStamp();
//            doAsync();
            res = swr_convert(m_swrContext, &m_buffer, m_bufferSize,
                              (const uint8_t **) m_frame->data, m_frame->nb_samples);
            if (res >= 0) {
                m_render->playFrame(m_buffer, m_bufferSize);
            }
            frameCount++;
        }
        av_packet_unref(m_packet);
        if (frameCount > 0) {
            return 0;
        }
    }
    m_render->onFrameEnd();
}

void AudioDecode::stop() {
    BaseDecode::stop();
    swr_close(m_swrContext);
    swr_free(&m_swrContext);
}
