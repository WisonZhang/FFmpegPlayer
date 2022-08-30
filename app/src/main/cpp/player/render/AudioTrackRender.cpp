//
// Created by wison on 2022/8/21.
//

#include <LogUtils.h>
#include "AudioTrackRender.h"

void AudioTrackRender::init(JNIEnv *env, jobject obj) {
    LOG_D("AudioTrackRender init");
    jclass clazz = env->GetObjectClass(obj);
    jmethodID methodId = env->GetMethodID(clazz, "initAudioTrack", "()V");
    env->CallVoidMethod(obj, methodId);

    m_env = env;
    m_obj = obj;
    m_playMethod = env->GetMethodID(clazz, "audioTrackPlay", "([BI)V");
}

void AudioTrackRender::playData(uint8_t *data, int size) {
    jbyteArray audioArray = m_env->NewByteArray(size);
    m_env->SetByteArrayRegion(audioArray, 0, size, reinterpret_cast<const jbyte *>(data));
    m_env->CallVoidMethod(m_obj, m_playMethod, audioArray, size);
    m_env->DeleteLocalRef(audioArray);




}

void AudioTrackRender::release() {

}