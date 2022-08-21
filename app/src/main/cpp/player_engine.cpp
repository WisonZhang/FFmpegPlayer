//
// Created by wison on 2022/7/3.
//

#include <jni.h>
#include <FFmpegPlayer.h>
#include <android/log.h>

extern "C"
JNIEXPORT jlong JNICALL
Java_com_wison_ffmpeg_player_MediaView_playVideo(JNIEnv *env, jobject thiz, jstring path, jobject surface) {
    auto* player = new FFmpegPlayer();
    player->init(env, thiz);
    player->setUrl(env, path);
    player->setSurface(env, surface);
    player->play();
    return reinterpret_cast<jlong>(player);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_stopVideo(JNIEnv *env, jobject thiz, jlong ptr) {
    auto* player = reinterpret_cast<FFmpegPlayer*>(ptr);
    if (!player) {
        return;
    }
    player->stop();
}