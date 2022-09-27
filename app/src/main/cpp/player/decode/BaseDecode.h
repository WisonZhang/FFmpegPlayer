//
// Created by wison on 2022/8/1.
//

#ifndef FFMEPGPROJECT_BASEDECODE_H
#define FFMEPGPROJECT_BASEDECODE_H

#include <PlayerCallback.h>
#include <render/VideoNativeRender.h>
#include "LogUtils.h"
#include "thread"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
}

using namespace std;

enum DecoderState {
    STATE_UNKNOWN,
    STATE_PLAY,
    STATE_PAUSE,
    STATE_STOP
};

enum MediaType {
    TYPE_VIDEO,
    TYPE_AUDIO
};

class BaseDecode {
public:
    void start(char* url);
    void pause();
    virtual void stop();
    void setJavaInfo(JavaVM* vm, jobject obj);

private:
    static void startDecode(char* url, BaseDecode *decode);
    void attachThread();
    void doParse(char *url);
    virtual void onInfoReady() = 0;
    virtual int doDecode() = 0;

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

    //解码器状态
    volatile int m_state = STATE_UNKNOWN;
    mutex m_mutex;
    condition_variable m_condition;
    thread *m_thread = nullptr;
    JavaVM *m_jvm = nullptr;
    JNIEnv *m_env = nullptr;
    jobject m_obj = nullptr;
};

#endif //FFMEPGPROJECT_BASEDECODE_H
