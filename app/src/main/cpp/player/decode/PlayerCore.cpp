//
// Created by wison on 2022/8/9.
//

#include "PlayerCore.h"
#include "VideoDecode.h"
#include <string>

void PlayerCore::setUrl(const char *url) {
    m_url = new char[(strlen(url) + 1) * sizeof(char)];
    strcpy(m_url, url);
}

void PlayerCore::setSurface(JNIEnv *env, jobject& surface) {
    m_env = env;
    m_surface = surface;
}

void PlayerCore::setCallback(PlayerCallback *callback) {
    m_callback = callback;
}

void PlayerCore::setDecodeType(DecodeType type) {
    m_decodeType = type;
}

void PlayerCore::setVideoRenderType(VideoRenderType type) {
    m_renderType = type;
}

void PlayerCore::startDecode() {
    init();
    if (!isInit) {
        return;
    }
    m_videoRender->setSurface(m_env, m_surface);
    m_videoDecode->setCallback(m_callback);
    m_videoDecode->setVideoRender(m_videoRender);
    m_videoDecode->init(m_url);
    m_videoDecode->startDecode();
}

void PlayerCore::init() {
    if (isInit) {
        return;
    }
    if (m_decodeType == DECODE_TYPE_FFM) {
        m_videoDecode = new VideoDecode();
        m_audioDecode = new VideoDecode();
    }
    if (m_renderType == RENDER_TYPE_AN) {
        m_videoRender = reinterpret_cast<VideoRender *>(new VideoNativeRender());
    }
    if (m_videoDecode != nullptr && m_videoRender != nullptr) {
        isInit = true;
    }
}

void PlayerCore::release() {
    if (m_videoDecode) {
        m_videoDecode->release();
        delete m_videoDecode;
        m_videoDecode = nullptr;
    }
    if (m_videoRender) {
        m_videoRender->release();
        delete m_videoRender;
        m_videoRender = nullptr;
    }

    m_decodeType = DECODE_TYPE_FFM;
    m_renderType = RENDER_TYPE_AN;
    delete m_url;
    m_url = nullptr;
    m_env = nullptr;
    m_surface = nullptr;
    isInit = false;
}