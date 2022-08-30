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
    m_swrContext = swr_alloc();
    swr_alloc_set_opts(m_swrContext, AUDIO_CHANNEL_COUNT, AUDIO_SAMPLE_FMT, AUDIO_DST_SAMPLE_RATE,
            m_codecContext->channel_layout, m_codecContext->sample_fmt, m_codecContext->sample_rate, 0, nullptr);
    swr_init(m_swrContext);

    int channelCount = av_get_channel_layout_nb_channels(AUDIO_CHANNEL_COUNT);
    int sample = (int)av_rescale_rnd(1024, AUDIO_DST_SAMPLE_RATE, m_codecContext->sample_rate, AV_ROUND_UP);
    m_bufferSize = av_samples_get_buffer_size(NULL, channelCount, sample, AUDIO_SAMPLE_FMT, 1);
    m_buffer = static_cast<uint8_t *>(malloc(m_bufferSize));
}

void AudioDecode::startDecode() {
    LOG_D("AudioDecode startDecode");
    while (av_read_frame(m_fmContext, m_packet) >= 0) {
        if (m_packet->stream_index != m_streamIndex) {
            av_packet_unref(m_packet);
            continue;
        }
        int res = avcodec_send_packet(m_codecContext, m_packet);
        if (res < 0) {
            av_packet_unref(m_packet);
            continue;
        }
        while (avcodec_receive_frame(m_codecContext, m_frame) >= 0) {
            res = swr_convert(m_swrContext, &m_buffer, m_bufferSize, (const uint8_t**) m_frame->data, m_frame->nb_samples);
            if (res >= 0) {
                m_render->playData(m_buffer, m_bufferSize);
            }
        }
    }
}

void AudioDecode::release() {
    BaseDecode::release();
    swr_close(m_swrContext);
    swr_free(&m_swrContext);
}
