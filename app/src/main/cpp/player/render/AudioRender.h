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
    virtual void init(JNIEnv* env, int dataSize) = 0;
    virtual void setObject(jobject obj) = 0;
    virtual void playFrame(uint8_t* data, int size) = 0;
    virtual void onFrameEnd() = 0;
    virtual void release() = 0;

protected:
    jobject m_obj = nullptr;
};

#endif //FFMEPGPROJECT_AUDIORENDER_H
