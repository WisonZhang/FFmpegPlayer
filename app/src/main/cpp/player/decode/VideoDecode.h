//
// Created by wison on 2022/8/1.
//

#ifndef FFMEPGPROJECT_VIDEODECODE_H
#define FFMEPGPROJECT_VIDEODECODE_H

#include "BaseDecode.h"

extern "C" {
#include <libswscale/swscale.h>
}

class VideoDecode: public BaseDecode {
public:
    VideoDecode();
    void setVideoRender(VideoRender* render);
    void onInfoReady() override;
    void startDecode() override;
    void release() override;

private:
    SwsContext* m_swContext = nullptr;
    AVFrame* m_rgbFrame = nullptr;

    VideoRender* m_render;
    uint8_t* m_buffer;
    int m_videoWidth;
    int m_videoHeight;
};

#endif //FFMEPGPROJECT_VIDEODECODE_H