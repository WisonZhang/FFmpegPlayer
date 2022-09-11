//
// Created by wison on 2022/8/20.
//

#ifndef FFMEPGPROJECT_VIDEORENDER_H
#define FFMEPGPROJECT_VIDEORENDER_H

#include "LogUtils.h"

extern "C" {
#include <libavcodec/avcodec.h>
}

class VideoRender {

public:
    virtual ~VideoRender() = default;
    virtual void init(JNIEnv *env) = 0;
    virtual int getRenderWidth() = 0;
    virtual int getRenderHeight() = 0;
    virtual AVPixelFormat getRenderPixel() = 0;
    virtual void setSurface(jobject surface) = 0;
    virtual void drawFrame(AVFrame* frame) = 0;
    virtual void release() = 0;

protected:
    jobject m_surface = nullptr;
};

#endif //FFMEPGPROJECT_VIDEORENDER_H
