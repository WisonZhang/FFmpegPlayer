//
// Created by wison on 2022/7/6.
//

#ifndef FFMEPGPROJECT_PLAYERCALLBACK_H
#define FFMEPGPROJECT_PLAYERCALLBACK_H

#include <jni.h>

class PlayerCallback {

public:
    PlayerCallback(JNIEnv *env, jobject obj);
    void setVideoSize(int width, int height);

private:
    JNIEnv* m_env = nullptr;
    jobject m_obj = nullptr;
};

#endif //FFMEPGPROJECT_PLAYERCALLBACK_H
