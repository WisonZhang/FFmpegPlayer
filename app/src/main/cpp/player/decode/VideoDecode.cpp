//
// Created by wison on 2022/8/1.
//

#include "VideoDecode.h"

VideoDecode::VideoDecode() {
    m_mediaType = TYPE_VIDEO;
}

void VideoDecode::setVideoRender(VideoRender *render) {
    m_render = render;
}

void VideoDecode::onInfoReady() {
    if (!m_codecContext) {
        return;
    }
    m_render->init(m_env);
    m_videoWidth = m_codecContext->width;
    m_videoHeight = m_codecContext->height;
    LOG_D("onInfoReady, width: %d; height: %d", m_videoWidth, m_videoHeight);

    m_callback->onVideoSize(m_videoWidth, m_videoHeight);
    m_swContext = sws_getContext(m_videoWidth, m_videoHeight, m_codecContext->pix_fmt,
                                 m_render->getRenderWidth(), m_render->getRenderHeight(),
                                 m_render->getRenderPixel(), SWS_FAST_BILINEAR, NULL, NULL, NULL);
    m_rgbFrame = av_frame_alloc();

    int bufferSize = av_image_get_buffer_size(m_render->getRenderPixel(), m_render->getRenderWidth(), m_render->getRenderHeight(), 1);
    m_buffer = static_cast<uint8_t*>(malloc(bufferSize * sizeof(uint8_t)));
    av_image_fill_arrays(m_rgbFrame->data, m_rgbFrame->linesize, m_buffer, m_render->getRenderPixel(),
                         m_render->getRenderWidth(), m_render->getRenderHeight(), 1);
}

void VideoDecode::doDecode() {
    LOG_D("VideoDecode startDecode");
    while (av_read_frame(m_fmContext, m_packet) == 0) {
        if (m_packet->stream_index != m_streamIndex) {
            av_packet_unref(m_packet);
            continue;
        }
        int res = avcodec_send_packet(m_codecContext, m_packet);
        if (res != 0) {
            av_packet_unref(m_packet);
            continue;
        }
        while (avcodec_receive_frame(m_codecContext, m_frame) == 0) {
            sws_scale(m_swContext, m_frame->data, m_frame->linesize, 0, m_videoHeight,
                      m_rgbFrame->data, m_rgbFrame->linesize);
            m_render->drawFrame(m_rgbFrame);
        }
        av_packet_unref(m_packet);
    }
}

void VideoDecode::release() {
    BaseDecode::release();

    if (m_buffer) {
        free(m_buffer);
        m_buffer = nullptr;
    }
    if (m_rgbFrame) {
        av_frame_free(&m_rgbFrame);
        m_rgbFrame = nullptr;
    }
    if (m_swContext) {
        sws_freeContext(m_swContext);
        m_swContext = nullptr;
    }

    m_render = nullptr;
    m_videoWidth = 0;
    m_videoHeight = 0;
}