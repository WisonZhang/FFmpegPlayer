//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_VIDEONATIVERENDER_H
#define FFMEPGPROJECT_VIDEONATIVERENDER_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include "VideoRender.h"

class VideoNativeRender: VideoRender {

public:
    int getRenderWidth() override;
    int getRenderHeight() override;
    AVPixelFormat getRenderPixel() override;
    void setSurface(JNIEnv *env, jobject& surface) override;
    void drawFrame(AVFrame* frame) override;
    void release() override;

private:
    ANativeWindow* m_nativeWindow;
    ANativeWindow_Buffer m_buffer;

    int m_renderWidth = 0;
    int m_renderHeight = 0;
};

#endif //FFMEPGPROJECT_VIDEONATIVERENDER_H
