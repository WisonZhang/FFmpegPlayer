//
// Created by wison on 2022/8/9.
//

#include "PlayerCore.h"
#include "VideoDecode.h"
#include "AudioDecode.h"
#include <string>
#include <render/AudioTrackRender.h>

PlayerCore::PlayerCore(JNIEnv* env, jobject obj) {
    m_env = env;
    m_obj = obj;
}

void PlayerCore::setUrl(const char *url) {
    m_url = new char[(strlen(url) + 1) * sizeof(char)];
    strcpy(m_url, url);
}

void PlayerCore::setSurface(jobject &surface) {
    m_surface = surface;
}

void PlayerCore::setCallback(PlayerCallback *callback) {
    m_callback = callback;
}

void PlayerCore::setDecodeType(DecodeType type) {
    m_decodeType = type;
}

void PlayerCore::setVideoRenderType(VideoRenderType type) {
    m_videoRenderType = type;
}

void PlayerCore::setAudioRenderType(AudioRenderType type) {
    m_audioRenderType = type;
}

void PlayerCore::startDecode() {
    init();
    if (!isInit) {
        return;
    }
    // 设置视频解码
    m_videoRender->setSurface(m_env, m_surface);
    m_videoDecode->setCallback(m_callback);
    m_videoDecode->setVideoRender(m_videoRender);
    m_videoDecode->init(m_url);

    // 设置音频解码
    m_audioDecode->setCallback(m_callback);
    m_audioDecode->setAudioRender(m_audioRender);
    m_audioDecode->init(m_url);

    // 开始解码
//    m_videoDecode->startDecode();
    m_audioDecode->startDecode();
}

void PlayerCore::init() {
    if (isInit) {
        return;
    }

    // 音视频解码
    if (m_decodeType == DECODE_TYPE_FFM) {
        m_videoDecode = new VideoDecode();
        m_audioDecode = new AudioDecode();
    }

    // 视频渲染
    if (m_videoRenderType == VIDEO_RENDER_TYPE_AN) {
        m_videoRender = reinterpret_cast<VideoRender *>(new VideoNativeRender());
    }

    // 音频渲染
    if (m_audioRenderType == AUDIO_RENDER_TYPE_AT) {
        auto render = new AudioTrackRender();
        render->init(m_env, m_obj);
        m_audioRender = reinterpret_cast<AudioRender *>(render);
    }

    if (m_videoDecode != nullptr && m_audioDecode != nullptr
        && m_videoRender != nullptr && m_audioRender != nullptr) {
        isInit = true;
    }
}

void PlayerCore::release() {
    if (m_videoDecode) {
        m_videoDecode->release();
        delete m_videoDecode;
        m_videoDecode = nullptr;
    }
    if (m_audioDecode) {
        m_audioDecode->release();
        delete m_audioDecode;
        m_audioDecode = nullptr;
    }
    if (m_videoRender) {
        m_videoRender->release();
        delete m_videoRender;
        m_videoRender = nullptr;
    }
    if (m_audioRender) {
        m_audioRender->release();
        delete m_audioRender;
        m_audioRender = nullptr;
    }

    m_decodeType = DECODE_TYPE_FFM;
    m_videoRenderType = VIDEO_RENDER_TYPE_AN;
    m_audioRenderType = AUDIO_RENDER_TYPE_AT;
    delete m_url;
    m_url = nullptr;
    m_env = nullptr;
    m_surface = nullptr;
    isInit = false;
}