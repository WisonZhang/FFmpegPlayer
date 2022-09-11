//
// Created by wison on 2022/8/21.
//

#ifndef FFMEPGPROJECT_AUDIOTRACKRENDER_H
#define FFMEPGPROJECT_AUDIOTRACKRENDER_H

#include "AudioRender.h"

class AudioTrackRender: AudioRender {

public:
    void init(JNIEnv *env) override;
    void setObject(jobject obj) override;
    void playData(uint8_t *data, int size) override;
    void release() override;

private:
    JNIEnv* m_env = nullptr;
    jobject m_obj = nullptr;
    jmethodID m_playMethod = nullptr;
};


#endif //FFMEPGPROJECT_AUDIOTRACKRENDER_H
