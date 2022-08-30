//
// Created by wison on 2022/8/9.
//

#ifndef FFMEPGPROJECT_PLAYERCORE_H
#define FFMEPGPROJECT_PLAYERCORE_H

#include "PlayerCallback.h"
#include "VideoDecode.h"
#include "AudioDecode.h"

enum DecodeType {
    DECODE_TYPE_FFM,
    DECODE_TYPE_MC
};

enum VideoRenderType {
    VIDEO_RENDER_TYPE_AN,
    VIDEO_RENDER_TYPE_OPEN_GL
};

enum AudioRenderType {
    AUDIO_RENDER_TYPE_AT
};

class PlayerCore {

public:
    PlayerCore(JNIEnv* env, jobject obj);
    void setUrl(const char* url);
    void setSurface(jobject& surface);
    void startDecode();
    void setCallback(PlayerCallback* callback);
    void setDecodeType(DecodeType type);
    void setVideoRenderType(VideoRenderType type);
    void setAudioRenderType(AudioRenderType type);
    void release();

private:
    void init();

    char* m_url;
    DecodeType m_decodeType = DECODE_TYPE_FFM;
    VideoRenderType m_videoRenderType = VIDEO_RENDER_TYPE_AN;
    AudioRenderType m_audioRenderType = AUDIO_RENDER_TYPE_AT;

    PlayerCallback* m_callback = nullptr;
    VideoDecode* m_videoDecode = nullptr;
    AudioDecode* m_audioDecode = nullptr;
    VideoRender* m_videoRender = nullptr;
    AudioRender* m_audioRender = nullptr;

    JNIEnv* m_env = nullptr;
    jobject m_obj = nullptr;
    jobject m_surface = nullptr;

    bool isInit = false;
};


#endif //FFMEPGPROJECT_PLAYERCORE_H
