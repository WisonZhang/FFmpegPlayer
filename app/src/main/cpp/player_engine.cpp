//
// Created by wison on 2022/7/3.
//

#include <jni.h>
#include <FFmpegPlayer.h>
#include <android/log.h>

static JavaVM *jvm;

extern "C"
JNIEXPORT int JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    jvm = vm;
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_wison_ffmpeg_player_MediaView_playVideo(JNIEnv *env, jobject thiz, jstring path, jobject surface) {
    auto *player = new FFmpegPlayer();
    player->init(jvm, env, thiz);
    player->setUrl(env, path);
    player->setSurface(env, surface);
    player->play();
    return reinterpret_cast<jlong>(player);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_resumeVideo(JNIEnv *env, jobject thiz, jlong ptr) {
    auto *player = reinterpret_cast<FFmpegPlayer *>(ptr);
    if (!player) {
        return;
    }
    player->resume();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_pauseVideo(JNIEnv *env, jobject thiz, jlong ptr) {
    auto *player = reinterpret_cast<FFmpegPlayer *>(ptr);
    if (!player) {
        return;
    }
    player->pause();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_wison_ffmpeg_player_MediaView_stopVideo(JNIEnv *env, jobject thiz, jlong ptr) {
    auto *player = reinterpret_cast<FFmpegPlayer *>(ptr);
    if (!player) {
        return;
    }
    player->stop();
}