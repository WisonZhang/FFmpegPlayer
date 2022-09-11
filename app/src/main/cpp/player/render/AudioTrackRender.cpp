//
// Created by wison on 2022/8/21.
//

#include <LogUtils.h>
#include "AudioTrackRender.h"

void AudioTrackRender::init(JNIEnv *env) {
    LOG_D("AudioTrackRender init");
    jclass clazz = env->GetObjectClass(m_obj);
    jmethodID methodId = env->GetMethodID(clazz, "initAudioTrack", "()V");
    env->CallVoidMethod(m_obj, methodId);

    m_env = env;
    m_playMethod = env->GetMethodID(clazz, "audioTrackPlay", "([BI)V");
}

void AudioTrackRender::setObject(jobject obj) {
    m_obj = obj;
}

void AudioTrackRender::playData(uint8_t *data, int size) {
    jbyteArray audioArray = m_env->NewByteArray(size);
    m_env->SetByteArrayRegion(audioArray, 0, size, reinterpret_cast<const jbyte *>(data));
    m_env->CallVoidMethod(m_obj, m_playMethod, audioArray, size);
    m_env->DeleteLocalRef(audioArray);
}

void AudioTrackRender::release() {

}