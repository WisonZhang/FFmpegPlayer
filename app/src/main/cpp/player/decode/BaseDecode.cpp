//
// Created by wison on 2022/8/1.
//

#include "BaseDecode.h"

void BaseDecode::init(char *url) {
    int res;

    m_fmContext = avformat_alloc_context();
    res = avformat_open_input(&m_fmContext, url, nullptr, nullptr);
    if (res < 0) {
        release();
        return;
    }

    res = avformat_find_stream_info(m_fmContext, NULL);
    if (res < 0) {
        release();
        return;
    }

    AVMediaType type;
    if (m_mediaType == TYPE_VIDEO) {
        type = AVMEDIA_TYPE_VIDEO;
    } else if (m_mediaType == TYPE_AUDIO) {
        type = AVMEDIA_TYPE_AUDIO;
    }

    for (int i = 0; i < m_fmContext->nb_streams; ++i) {
        if (m_fmContext->streams[i]->codecpar->codec_type == type) {
            m_streamIndex = i;
            break;
        }
    }

    if (m_streamIndex < 0) {
        release();
        return;
    }

    m_codecParam = m_fmContext->streams[m_streamIndex]->codecpar;
    m_decoder = avcodec_find_decoder(m_codecParam->codec_id);
    m_codecContext = avcodec_alloc_context3(m_decoder);
    avcodec_parameters_to_context(m_codecContext, m_codecParam);
    res = avcodec_open2(m_codecContext, m_decoder, NULL);
    if (res < 0) {
        release();
        return;
    }

    m_packet = av_packet_alloc();
    m_frame = av_frame_alloc();

    onInfoReady();
}

void BaseDecode::setCallback(PlayerCallback *callback) {
    m_callback = callback;
}

void BaseDecode::release() {
    if (m_frame) {
        av_frame_free(&m_frame);
        m_frame = nullptr;
    }
    if (m_packet) {
        av_packet_unref(m_packet);
        av_packet_free(&m_packet);
        m_packet = nullptr;
    }
    if (m_codecContext) {
        avcodec_close(m_codecContext);
        avcodec_free_context(&m_codecContext);
        m_codecContext = nullptr;
    }
    if (m_fmContext) {
        avformat_close_input(&m_fmContext);
        avformat_free_context(m_fmContext);
        m_fmContext = nullptr;
    }
}