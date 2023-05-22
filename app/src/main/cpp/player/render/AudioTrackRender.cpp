//
// Created by wison on 2022/8/21.
//

#include <LogUtils.h>
#include "AudioTrackRender.h"

void AudioTrackRender::init(JNIEnv *env, int dataSize) {
    LOG_D("AudioTrackRender init");
    jclass clazz = env->GetObjectClass(m_obj);
    jmethodID methodId = env->GetMethodID(clazz, "initAudioTrack", "()V");
    env->CallVoidMethod(m_obj, methodId);

    m_env = env;
    m_playMethod = env->GetMethodID(clazz, "audioTrackPlay", "([BI)V");

    m_audioArray = m_env->NewByteArray(dataSize);
    m_audioData = m_env->GetByteArrayElements(m_audioArray, NULL);
}

void AudioTrackRender::setObject(jobject obj) {
    m_obj = obj;
}

void AudioTrackRender::playFrame(uint8_t *data, int size) {
    memcpy(m_audioData, data, size);
    m_env->ReleaseByteArrayElements(m_audioArray, m_audioData, JNI_COMMIT);
    m_env->CallVoidMethod(m_obj, m_playMethod, m_audioArray, size);
}

void AudioTrackRender::onFrameEnd() {
    m_env->ReleaseByteArrayElements(m_audioArray, m_audioData, 0);
}

void AudioTrackRender::release() {

}