//
// Created by wison on 2022/7/6.
//

#include "PlayerCallback.h"

PlayerCallback::PlayerCallback(JNIEnv *env, jobject obj) {
    m_env = env;
    m_obj = obj;
}

void PlayerCallback::setVideoSize(int width, int height) {
    if (!m_env || !m_obj) {
        return;
    }

    jclass clazz = m_env->GetObjectClass(m_obj);
    jfieldID fieldId = m_env->GetFieldID(clazz, "mListener", "Lcom/wison/ffmpeg/player/PlayerListenerImpl;");
    jobject listener = m_env->GetObjectField(m_obj, fieldId);
    clazz = m_env->GetObjectClass(listener);
    jmethodID methodId = m_env->GetMethodID(clazz, "onVideoSize", "(II)V");
    m_env->CallVoidMethod(listener, methodId, width, height);
}
