//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_PLAYER_H
#define FFMEPGPROJECT_PLAYER_H

#include <jni.h>
#include <PlayerCore.h>
#include <render/VideoNativeRender.h>
#include "PlayerCallback.h"

class Player {
public:
    Player() {}

    virtual void init(JavaVM *vm, JNIEnv *env, jobject obj) = 0;
    virtual void setSurface(JNIEnv *env, jobject surface) = 0;
    virtual void setUrl(JNIEnv *env, jstring jurl) = 0;
    virtual void play() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void seekTo(long position) = 0;
    virtual void release() = 0;

protected:
    PlayerCore* m_playCore = nullptr;
};

#endif //FFMEPGPROJECT_PLAYER_H