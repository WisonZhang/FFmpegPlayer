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

#include "Render.h"

class Decoder {

public:
    void setUrl(const char* url);
    void startDecode();
    void setRender(Render* render);

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
    Render* m_render = nullptr;

    char* m_url;
    int m_streamIndex = -1;
    int m_videoWidth = 0;
    int m_videoHeight = 0;
    int m_bufferSize = 0;

private:
    void init();
    void doDecode();
    void end();
};

#endif //FFMEPGPROJECT_DECODER_H
