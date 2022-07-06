//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_RENDER_H
#define FFMEPGPROJECT_RENDER_H

extern "C" {
#include <libavcodec/avcodec.h>
}

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

class Render {

public:
    Render(JNIEnv* env, jobject surface);
    void drawFrame(AVFrame* frame);
    void setVideoSize(int width, int height);
    int getRenderWidth();
    int getRenderHeight();

private:
    ANativeWindow* m_nativeWindow;
    ANativeWindow_Buffer m_buffer;

    int m_videoWidth = 0;
    int m_videoHeight = 0;
    int m_renderWidth = 0;
    int m_renderHeight = 0;
};

#endif //FFMEPGPROJECT_RENDER_H
