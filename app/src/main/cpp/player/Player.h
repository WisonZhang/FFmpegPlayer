//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_PLAYER_H
#define FFMEPGPROJECT_PLAYER_H

#include <jni.h>
#include <decode/Decoder.h>
#include <render/Render.h>

class Player {
public:
    Player() {}

    virtual void init(JNIEnv *env) = 0;
    virtual void setSurface(JNIEnv *env, jobject surface) = 0;
    virtual void setUrl(JNIEnv *env, jstring jurl) = 0;
    virtual void play() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void seekTo(long position) = 0;
    virtual void release() = 0;

protected:
    Decoder* m_decoder = nullptr;
    Render* m_render = nullptr;

};

#endif //FFMEPGPROJECT_PLAYER_H