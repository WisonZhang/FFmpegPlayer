//
// Created by wison on 2022/7/3.
//

#include <jni.h>
#include <FFmpegPlayer.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_playVideo(JNIEnv *env, jobject thiz, jstring path, jobject surface) {
    FFmpegPlayer* player = new FFmpegPlayer();
    player->init(env);
    player->setUrl(env, path);
    player->setSurface(env, surface);
    player->play();
}
