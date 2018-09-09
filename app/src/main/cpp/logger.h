//
// Created by zengxinhong on 2018/9/10.
//

#ifndef NDKCOURSE_LOGGER_H
#define NDKCOURSE_LOGGER_H

#include <android/log.h>

#ifndef  LOG_TAG
#define  LOG_TAG    "jni-native"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif


#endif //NDKCOURSE_LOGGER_H
