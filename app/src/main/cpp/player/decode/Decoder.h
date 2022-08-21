//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_DECODER_H
#define FFMEPGPROJECT_DECODER_H

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#include "VideoNativeRender.h"
#include "PlayerCallback.h"

class Decoder {

public:
    void setUrl(const char* url);
    void startDecode();
    void setRender(VideoNativeRender* render);
    void setCallback(PlayerCallback* callback);

protected:
    AVFormatContext* m_fmContext;
    AVCodecParameters* m_codecParam;
    AVCodec* m_decoder;
    AVCodecContext* m_decoderContext;
    SwsContext *m_swContext = nullptr;
    AVPacket* m_packet;
    AVFrame* m_frame;
    AVFrame* m_rgbFrame;
    uint8_t* m_frameBuffer = nullptr;
    VideoNativeRender* m_render = nullptr;
    PlayerCallback* m_callback = nullptr;

    char* m_url;
    int m_streamIndex = -1;
    int m_videoWidth = 0;
    int m_videoHeight = 0;
    int m_bufferSize = 0;

private:
    void init();
    void doDecode();
    void doVideoDecode();
    void doAudioDecode();
    void end();
};

#endif //FFMEPGPROJECT_DECODER_H
