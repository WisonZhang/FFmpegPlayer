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
#include <libavutil/time.h>
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

typedef long (*AsyncCallback)(void* context, MediaType type);

class BaseDecode {
public:
    void start(char* url);
    void pause();
    virtual void stop();
    void setJavaInfo(JavaVM* vm, jobject obj);
    void setAsyncCallback(void* context, AsyncCallback callback);
    long getCurrentTimeStamp();

protected:
    void updateTimeStamp();
    void doAsync();

private:
    static void startDecode(char* url, BaseDecode *decode);
    void attachThread();
    void doParse(char *url);
    virtual void onInfoReady() = 0;
    virtual int doDecode() = 0;

protected:
    AVFormatContext* m_fmContext = nullptr;;
    AVCodecParameters* m_codecParam = nullptr;;
    AVCodec* m_decoder = nullptr;;
    AVCodecContext* m_codecContext = nullptr;;
    AVPacket* m_packet = nullptr;;
    AVFrame* m_frame = nullptr;;

    MediaType m_mediaType;
    PlayerCallback* m_callback = nullptr;;
    void* m_asyncContext = nullptr;;
    AsyncCallback m_asyncCallback = nullptr;;
    int m_streamIndex = -1;
    long m_curTimeStamp = 0;

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
