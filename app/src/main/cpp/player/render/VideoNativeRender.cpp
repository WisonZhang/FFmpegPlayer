//
// Created by wison on 2022/6/26.
//

#include "VideoNativeRender.h"
#include <cstring>
#include <android/native_window.h>
#include <android/native_window_jni.h>

void VideoNativeRender::setSurface(JNIEnv *env, jobject& surface) {
    m_nativeWindow = ANativeWindow_fromSurface(env, surface);
    m_renderWidth = ANativeWindow_getWidth(m_nativeWindow);
    m_renderHeight = ANativeWindow_getHeight(m_nativeWindow);
    LOG_D("setSurface, width: %d; height: %d", m_renderWidth, m_renderHeight);
    ANativeWindow_setBuffersGeometry(m_nativeWindow, m_renderWidth, m_renderHeight, WINDOW_FORMAT_RGBA_8888);
}

int VideoNativeRender::getRenderWidth() {
    return m_renderWidth;
}

int VideoNativeRender::getRenderHeight() {
    return m_renderHeight;
}

AVPixelFormat VideoNativeRender::getRenderPixel() {
    return AV_PIX_FMT_RGBA;
}

void VideoNativeRender::drawFrame(AVFrame* frame) {
    if (m_nativeWindow == nullptr || frame == nullptr) {
        return;
    }

    ANativeWindow_lock(m_nativeWindow, &m_buffer, nullptr);

    auto* dst = static_cast<uint8_t *>(m_buffer.bits);
    int dstStride = m_buffer.stride * 4;

    uint8_t* src = frame->data[0];
    int lineSize = frame->linesize[0];

    for (int i = 0; i < m_renderHeight; i++) {
        memcpy(dst + i * dstStride, src + i * lineSize, lineSize);
    }

    ANativeWindow_unlockAndPost(m_nativeWindow);
}

void VideoNativeRender::release() {
    ANativeWindow_release(m_nativeWindow);
}