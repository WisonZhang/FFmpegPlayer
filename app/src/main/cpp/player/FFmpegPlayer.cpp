//
// Created by wison on 2022/6/26.
//

#include "FFmpegPlayer.h"

void FFmpegPlayer::init(JNIEnv *env, jobject obj) {
    m_playCore = new PlayerCore(env, obj);
    m_callback = new PlayerCallback(env, obj);
    m_playCore->setCallback(m_callback);
}

void FFmpegPlayer::setSurface(JNIEnv *env, jobject surface) {
    if (m_playCore) {
        m_playCore->setSurface(surface);
    }
}

void FFmpegPlayer::setUrl(JNIEnv *env, jstring jurl) {
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    if (m_playCore) {
        m_playCore->setUrl(const_cast<char *>(url));
    }
    env->ReleaseStringUTFChars(jurl, url);
}

void FFmpegPlayer::play() {
    if (m_playCore) {
        m_playCore->startDecode();
    }
}

void FFmpegPlayer::resume() {

}

void FFmpegPlayer::pause() {

}

void FFmpegPlayer::seekTo(long position) {

}

void FFmpegPlayer::stop() {
    if (m_playCore) {
        m_playCore->release();
    }
}

void FFmpegPlayer::release() {

}
