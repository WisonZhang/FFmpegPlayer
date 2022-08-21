//
// Created by wison on 2022/8/1.
//

#ifndef FFMEPGPROJECT_BASEDECODE_H
#define FFMEPGPROJECT_BASEDECODE_H

#include <PlayerCallback.h>
#include <render/VideoNativeRender.h>
#include "LogUtils.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

enum MediaType {
    TYPE_VIDEO,
    TYPE_AUDIO
};

class BaseDecode {
public:
    void init(char* url);
    void setCallback(PlayerCallback *callback);
    virtual void onInfoReady() = 0;
    virtual void startDecode() = 0;
    virtual void release();

protected:
    AVFormatContext* m_fmContext;
    AVCodecParameters* m_codecParam;
    AVCodec* m_decoder;
    AVCodecContext* m_codecContext;
    AVPacket* m_packet;
    AVFrame* m_frame;

    MediaType m_mediaType;
    PlayerCallback* m_callback;
    int m_streamIndex = -1;
};

#endif //FFMEPGPROJECT_BASEDECODE_H
