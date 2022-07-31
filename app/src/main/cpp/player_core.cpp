//
// Created by wison on 2022/7/3.
//

#include <jni.h>
#include <FFmpegPlayer.h>
#include <android/log.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_playVideo(JNIEnv *env, jobject thiz, jstring path, jobject surface) {
    FFmpegPlayer* player = new FFmpegPlayer();
    player->init(env, thiz);
    player->setUrl(env, path);
    player->setSurface(env, surface);
    player->play();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_getVideoInfo(JNIEnv *env, jobject thiz, jstring path) {
    int res;
    AVFormatContext* fmt;
    const char* url = env->GetStringUTFChars(path, NULL);
    res = avformat_open_input(&fmt, url, NULL, NULL);
    if (res < 0) {
        return;
    }
    av_dump_format(fmt, 0, url, 0);
}