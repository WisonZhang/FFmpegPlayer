//
// Created by wison on 2022/8/21.
//

#ifndef FFMEPGPROJECT_AUDIODECODE_H
#define FFMEPGPROJECT_AUDIODECODE_H

#include <render/AudioRender.h>
#include "BaseDecode.h"

extern "C" {
#include <libswresample/swresample.h>
}

static const int AUDIO_DST_SAMPLE_RATE = 44100;
static const int AUDIO_CHANNEL_COUNT = AV_CH_LAYOUT_STEREO;
static const AVSampleFormat AUDIO_SAMPLE_FMT = AV_SAMPLE_FMT_S16;

class AudioDecode : public BaseDecode {
public:
    AudioDecode();
    void setAudioRender(AudioRender* render);
    void onInfoReady() override;
    void startDecode() override;
    void release() override;


private:
    SwrContext* m_swrContext = nullptr;
    AudioRender* m_render = nullptr;
    uint8_t* m_buffer;
    int m_bufferSize;
};


#endif //FFMEPGPROJECT_AUDIODECODE_H
