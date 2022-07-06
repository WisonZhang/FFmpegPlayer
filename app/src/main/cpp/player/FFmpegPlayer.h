//
// Created by wison on 2022/6/26.
//

#ifndef FFMEPGPROJECT_FFMPEGPLAYER_H
#define FFMEPGPROJECT_FFMPEGPLAYER_H

#include "Player.h"

class FFmpegPlayer : public Player {

public:
    void init(JNIEnv *env) override;

    void setUrl(JNIEnv *env, jstring jurl) override;

    void setSurface(JNIEnv *env, jobject surface) override;

    void play() override;

    void resume() override;

    void pause() override;

    void stop() override;

    void seekTo(long position) override;

    void release() override;

private:


};

#endif //FFMEPGPROJECT_FFMPEGPLAYER_H