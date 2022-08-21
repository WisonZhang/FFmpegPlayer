//
// Created by wison on 2022/8/1.
//

#ifndef FFMEPGPROJECT_VIDEODECODE_H
#define FFMEPGPROJECT_VIDEODECODE_H

#include "BaseDecode.h"

class VideoDecode: public BaseDecode {
public:
    VideoDecode();
    void onInfoReady() override;
    void startDecode() override;
    void release() override;
    void setVideoRender(VideoRender* render);

private:
    SwsContext* m_swContext = nullptr;
    AVFrame* m_rgbFrame = nullptr;

    VideoRender* m_render;
    uint8_t* m_buffer;
    int m_videoWidth;
    int m_videoHeight;
};

#endif //FFMEPGPROJECT_VIDEODECODE_H