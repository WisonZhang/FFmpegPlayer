//
// Created by wison on 2022/6/26.
//

#include "Decoder.h"

void Decoder::setUrl(const char *url) {
    m_url = new char[(strlen(url) + 1) * sizeof(char)];
    strcpy(m_url, url);
}

void Decoder::setRender(Render *render) {
    m_render = render;
}

void Decoder::startDecode() {
    if (!m_url) {
        return;
    }
    init();
    doDecode();
    end();
}

void Decoder::init() {
    int res;
    m_fmContext = avformat_alloc_context();
    res = avformat_open_input(&m_fmContext, m_url, NULL, NULL);
    if (res < 0) {
        goto __FAIL;
    }
    res = avformat_find_stream_info(m_fmContext, NULL);
    if (res < 0) {
        goto __FAIL;
    }

    for (int i = 0; i < m_fmContext->nb_streams; ++i) {
        if (m_fmContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            m_streamIndex = i;
            break;
        }
    }
    if (m_streamIndex < 0) {
        goto __FAIL;
    }

    m_codecParam = m_fmContext->streams[m_streamIndex]->codecpar;
    m_decoder = avcodec_find_decoder(m_codecParam->codec_id);
    if (!m_decoder) {
        goto __FAIL;
    }

    m_decoderContext = avcodec_alloc_context3(m_decoder);
    res = avcodec_parameters_to_context(m_decoderContext, m_codecParam);
    if (res < 0) {
        goto __FAIL;
    }

    res = avcodec_open2(m_decoderContext, m_decoder, NULL);
    if (res < 0) {
        goto __FAIL;
    }

    m_videoWidth = m_decoderContext->width;
    m_videoHeight = m_decoderContext->height;
    m_render->setVideoSize(m_videoWidth, m_videoHeight);

    m_swContext = sws_getContext(m_videoWidth, m_videoHeight, m_decoderContext->pix_fmt,
                                 m_render->getRenderWidth(),
                                 m_render->getRenderHeight(), AV_PIX_FMT_RGBA, SWS_FAST_BILINEAR,
                                 NULL, NULL, NULL);
    m_packet = av_packet_alloc();
    m_frame = av_frame_alloc();
    m_rgbFrame = av_frame_alloc();

    m_bufferSize = av_image_get_buffer_size(AV_PIX_FMT_RGBA, m_render->getRenderWidth(),
                                            m_render->getRenderHeight(), 1);
    m_frameBuffer = static_cast<uint8_t *>(malloc(m_bufferSize * sizeof(uint8_t)));
    av_image_fill_arrays(m_rgbFrame->data, m_rgbFrame->linesize, m_frameBuffer, AV_PIX_FMT_RGBA,
                         m_render->getRenderWidth(), m_render->getRenderHeight(), 1);
    return;

    __FAIL:
    avcodec_close(m_decoderContext);
    avcodec_free_context(&m_decoderContext);
    avformat_close_input(&m_fmContext);
    avformat_free_context(m_fmContext);
    m_fmContext = nullptr;
}

void Decoder::doDecode() {
    if (!m_fmContext) {
        return;
    }
    int res;
    while (av_read_frame(m_fmContext, m_packet) >= 0) {
        if (m_packet->stream_index != m_streamIndex) {
            av_packet_unref(m_packet);
            continue;
        }
        res = avcodec_send_packet(m_decoderContext, m_packet);
        if (res < 0) {
            continue;
        }
        while (avcodec_receive_frame(m_decoderContext, m_frame) == 0) {
            sws_scale(m_swContext, m_frame->data, m_frame->linesize, 0,
                      m_videoHeight, m_rgbFrame->data, m_rgbFrame->linesize);
            m_render->drawFrame(m_rgbFrame);
        }
        av_packet_unref(m_packet);
    }
}

void Decoder::end() {
    avcodec_close(m_decoderContext);
    avcodec_free_context(&m_decoderContext);
    avformat_close_input(&m_fmContext);
    avformat_free_context(m_fmContext);
    av_packet_unref(m_packet);
}