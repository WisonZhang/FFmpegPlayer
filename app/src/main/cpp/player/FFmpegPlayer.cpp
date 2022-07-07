//
// Created by wison on 2022/6/26.
//

#include "FFmpegPlayer.h"
#include <Decoder.h>

void FFmpegPlayer::init(JNIEnv *env, jobject obj) {
    m_decoder = new Decoder();
    m_callback = new PlayerCallback(env, obj);
    m_decoder->setCallback(m_callback);
}

void FFmpegPlayer::setSurface(JNIEnv *env, jobject surface) {
    if (!m_render) {
        m_render = new Render(env, surface);
        m_decoder->setRender(m_render);
    }
}

void FFmpegPlayer::setUrl(JNIEnv *env, jstring jurl) {
    const char* url = env->GetStringUTFChars(jurl, nullptr);
    if (m_decoder) {
        m_decoder->setUrl(const_cast<char *>(url));
    }
    env->ReleaseStringUTFChars(jurl, url);
}

void FFmpegPlayer::play() {
    if (m_decoder) {
        m_decoder->startDecode();
    }
}

void FFmpegPlayer::resume() {

}

void FFmpegPlayer::pause() {

}

void FFmpegPlayer::stop() {

}

void FFmpegPlayer::seekTo(long position) {

}

void FFmpegPlayer::release() {

}
