//
// Created by wison on 2022/8/9.
//

#ifndef FFMEPGPROJECT_PLAYERCORE_H
#define FFMEPGPROJECT_PLAYERCORE_H

#include "PlayerCallback.h"
#include "VideoDecode.h"

enum DecodeType {
    DECODE_TYPE_FFM,
    DECODE_TYPE_MC
};

enum VideoRenderType {
    RENDER_TYPE_AN,
    RENDER_TYPE_OPEN_GL
};

class PlayerCore {

public:
    void setUrl(const char* url);
    void setSurface(JNIEnv* env, jobject& surface);
    void startDecode();
    void setCallback(PlayerCallback* callback);
    void setDecodeType(DecodeType type);
    void setVideoRenderType(VideoRenderType type);
    void release();

private:
    void init();

    char* m_url;
    DecodeType m_decodeType = DECODE_TYPE_FFM;
    VideoRenderType m_renderType = RENDER_TYPE_AN;

    PlayerCallback* m_callback = nullptr;
    VideoDecode* m_videoDecode = nullptr;
    VideoDecode* m_audioDecode = nullptr;
    VideoRender* m_videoRender = nullptr;

    JNIEnv* m_env = nullptr;
    jobject m_surface = nullptr;

    bool isInit = false;
};


#endif //FFMEPGPROJECT_PLAYERCORE_H
