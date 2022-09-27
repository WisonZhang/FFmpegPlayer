//
// Created by wison on 2022/8/9.
//

#include "PlayerCore.h"
#include "VideoDecode.h"
#include "AudioDecode.h"
#include <string>
#include <render/AudioTrackRender.h>

PlayerCore::PlayerCore(JavaVM *vm, JNIEnv* env, jobject obj) {
    m_jvm = vm;
    m_obj = env->NewGlobalRef(obj);
}

void PlayerCore::setUrl(const char *url) {
    m_url = new char[(strlen(url) + 1) * sizeof(char)];
    strcpy(m_url, url);
}

void PlayerCore::setSurface(JNIEnv *env, jobject &surface) {
    m_surface = env->NewGlobalRef(surface);
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

void PlayerCore::play() {
    init();
    if (!isInit) {
        return;
    }
    // 开始解码
    m_videoDecode->start(m_url);
    m_audioDecode->start(m_url);
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
        m_videoRender->setSurface(m_surface);
    }

    // 音频渲染
    if (m_audioRenderType == AUDIO_RENDER_TYPE_AT) {
        auto render = new AudioTrackRender();
        m_audioRender = reinterpret_cast<AudioRender *>(render);
        m_audioRender->setObject(m_obj);
    }

    if (m_videoDecode != nullptr && m_audioDecode != nullptr
        && m_videoRender != nullptr && m_audioRender != nullptr) {
        isInit = true;
    }

    // 设置视频解码
    m_videoDecode->setJavaInfo(m_jvm, m_obj);
    m_videoDecode->setVideoRender(m_videoRender);

    // 设置音频解码
    m_audioDecode->setJavaInfo(m_jvm, m_obj);
    m_audioDecode->setAudioRender(m_audioRender);
}

void PlayerCore::start() {
    if (m_videoDecode) {
        m_videoDecode->start(m_url);
    }
    if (m_audioDecode) {
        m_audioDecode->start(m_url);
    }
}

void PlayerCore::pause() {
    if (m_videoDecode) {
        m_videoDecode->pause();
    }
    if (m_audioDecode) {
        m_audioDecode->pause();
    }
}

void PlayerCore::stop() {
    if (m_videoDecode) {
        m_videoDecode->stop();
        delete m_videoDecode;
        m_videoDecode = nullptr;
    }
    if (m_audioDecode) {
        m_audioDecode->stop();
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
    m_surface = nullptr;
    m_obj = nullptr;
    isInit = false;
}