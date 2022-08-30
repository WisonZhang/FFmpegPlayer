//
// Created by wison on 2022/8/25.
//

#ifndef FFMEPGPROJECT_AUDIORENDER_H
#define FFMEPGPROJECT_AUDIORENDER_H

#include <jni.h>

extern "C" {
#include <libavcodec/avcodec.h>
}

class AudioRender {

public:
    virtual ~AudioRender() = default;
    virtual void init(JNIEnv* env, jobject obj) = 0;
    virtual void playData(uint8_t* data, int size) = 0;
    virtual void release() = 0;
};

#endif //FFMEPGPROJECT_AUDIORENDER_H
