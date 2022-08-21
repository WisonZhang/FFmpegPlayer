//
// Created by wison on 2022/8/21.
//

#ifndef FFMEPGPROJECT_LOGUTILS_H
#define FFMEPGPROJECT_LOGUTILS_H

#include<android/log.h>

#define  LOG_TAG "FFM_CORE"

#define  LOG_D(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)

#endif //FFMEPGPROJECT_LOGUTILS_H
