//
// Created by wison on 2022/6/26.
//

#include "FFmpegPlayer.h"

void FFmpegPlayer::init(JavaVM *vm, JNIEnv *env, jobject obj) {
    m_playCore = new PlayerCore(vm ,env, obj);
}

void FFmpegPlayer::setSurface(JNIEnv *env, jobject surface) {
    if (m_playCore) {
        m_playCore->setSurface(env, surface);
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
        m_playCore->play();
    }
}

void FFmpegPlayer::resume() {
    if (m_playCore) {
        m_playCore->start();
    }
}

void FFmpegPlayer::pause() {
    if (m_playCore) {
        m_playCore->pause();
    }
}

void FFmpegPlayer::seekTo(long position) {

}

void FFmpegPlayer::stop() {
    if (m_playCore) {
        m_playCore->stop();
    }
}

void FFmpegPlayer::release() {

}
