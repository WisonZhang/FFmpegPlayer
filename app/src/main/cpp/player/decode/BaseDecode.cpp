//
// Created by wison on 2022/8/1.
//

#include "BaseDecode.h"

void BaseDecode::setJavaInfo(JavaVM *vm, jobject obj) {
    m_jvm = vm;
    m_obj = obj;
}

void BaseDecode::setAsyncCallback(void* context, AsyncCallback callback) {
    m_asyncContext = context;
    m_asyncCallback = callback;
}

long BaseDecode::getCurrentTimeStamp() {
    return m_curTimeStamp;
}

void BaseDecode::startDecode(char *url, BaseDecode *decode) {
    decode->attachThread();
    decode->doParse(url);
    decode->onInfoReady();

    for (;;) {
        if (decode->m_state == STATE_PAUSE) {
            unique_lock<mutex> lock(decode->m_mutex);
            decode->m_condition.wait(lock);
        }
        if (decode->m_state == STATE_STOP) {
            return;
        }
        if(decode->doDecode() < 0) {
            unique_lock<mutex> lock(decode->m_mutex);
            decode->m_state = STATE_PAUSE;
            return;
        }
    }
}

void BaseDecode::attachThread() {
    m_jvm->AttachCurrentThread(&m_env, nullptr);
    m_callback = new PlayerCallback(m_env, m_obj);
}

void BaseDecode::doParse(char *url) {
    int res;

    m_fmContext = avformat_alloc_context();
    res = avformat_open_input(&m_fmContext, url, nullptr, nullptr);
    if (res < 0) {
        stop();
        return;
    }

    res = avformat_find_stream_info(m_fmContext, NULL);
    if (res < 0) {
        stop();
        return;
    }

    AVMediaType type;
    if (m_mediaType == TYPE_VIDEO) {
        type = AVMEDIA_TYPE_VIDEO;
    } else if (m_mediaType == TYPE_AUDIO) {
        type = AVMEDIA_TYPE_AUDIO;
    }

    for (int i = 0; i < m_fmContext->nb_streams; ++i) {
        if (m_fmContext->streams[i]->codecpar->codec_type == type) {
            m_streamIndex = i;
            break;
        }
    }

    if (m_streamIndex < 0) {
        stop();
        return;
    }

    m_codecParam = m_fmContext->streams[m_streamIndex]->codecpar;
    m_decoder = avcodec_find_decoder(m_codecParam->codec_id);
    m_codecContext = avcodec_alloc_context3(m_decoder);
    avcodec_parameters_to_context(m_codecContext, m_codecParam);
    res = avcodec_open2(m_codecContext, m_decoder, NULL);
    if (res < 0) {
        stop();
        return;
    }

    m_packet = av_packet_alloc();
    m_frame = av_frame_alloc();
}

void BaseDecode::updateTimeStamp() {
    if (m_frame == nullptr) {
        return;
    }
    int pts = 0;
    if (m_frame->pts != AV_NOPTS_VALUE) {
        pts = m_frame->pts;
    }
    m_curTimeStamp = (int64_t)((pts * av_q2d(m_fmContext->streams[m_streamIndex]->time_base)) * 1000);
}

void BaseDecode::doAsync() {
    if(m_asyncCallback != nullptr) {
        long elapsedTime = m_asyncCallback(m_asyncContext, m_mediaType);
        if(m_curTimeStamp > elapsedTime) {
            auto sleepTime = static_cast<unsigned int>(m_curTimeStamp - elapsedTime);
            av_usleep(sleepTime * 1000);
        }
    }
}

void BaseDecode::start(char *url) {
    if (m_thread == nullptr) {
        m_thread = new thread(startDecode, url, this);
    } else {
        unique_lock<mutex> lock(m_mutex);
        m_state = STATE_PLAY;
        m_condition.notify_all();
    }
}

void BaseDecode::pause() {
    unique_lock<mutex> lock(m_mutex);
    m_state = STATE_PAUSE;
    m_condition.notify_all();
}

void BaseDecode::stop() {
    unique_lock<mutex> lock(m_mutex);
    m_state = STATE_STOP;
    m_condition.notify_all();

    m_thread->join();

    if (m_frame) {
        av_frame_free(&m_frame);
        m_frame = nullptr;
    }
    if (m_packet) {
        av_packet_unref(m_packet);
        av_packet_free(&m_packet);
        m_packet = nullptr;
    }
    if (m_codecContext) {
        avcodec_close(m_codecContext);
        avcodec_free_context(&m_codecContext);
        m_codecContext = nullptr;
    }
    if (m_fmContext) {
        avformat_close_input(&m_fmContext);
        avformat_free_context(m_fmContext);
        m_fmContext = nullptr;
    }
    m_env = nullptr;
}