//
// Created by wison on 2022/6/26.
//

#include "Render.h"
#include <cstring>

Render::Render(JNIEnv *env, jobject surface) {
    m_nativeWindow = ANativeWindow_fromSurface(env, surface);
}

void Render::setVideoSize(int width, int height) {
    m_videoWidth = width;
    m_videoHeight = height;

    int windowWidth = ANativeWindow_getWidth(m_nativeWindow);
    int windowHeight = ANativeWindow_getHeight(m_nativeWindow);
    if (windowWidth < windowHeight * m_videoWidth / m_videoHeight) {
        m_renderWidth = windowWidth;
        m_renderHeight = windowWidth * m_videoHeight / m_videoWidth;
    } else {
        m_renderWidth = windowHeight * m_videoWidth / m_videoHeight;
        m_renderHeight = windowHeight;
    }

    ANativeWindow_setBuffersGeometry(m_nativeWindow, m_renderWidth, m_renderHeight, WINDOW_FORMAT_RGBA_8888);
}

int Render::getRenderWidth() {
    return m_renderWidth;
}

int Render::getRenderHeight() {
    return m_renderHeight;
}

void Render::drawFrame(AVFrame* frame) {
    if (m_nativeWindow == nullptr || frame == nullptr) {
        return;
    }
    ANativeWindow_lock(m_nativeWindow, &m_buffer, nullptr);

    uint8_t* dst = static_cast<uint8_t *>(m_buffer.bits);
    int dstStride = m_buffer.stride * 4;

    uint8_t* src = frame->data[0];
    int lineSize = m_renderWidth * 4;

    for (int i = 0; i < m_renderHeight; i++) {
        memcpy(dst + i * dstStride, src + i * lineSize, lineSize);
    }

    ANativeWindow_unlockAndPost(m_nativeWindow);
}