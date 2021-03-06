//
// Created by xh.zeng on 2017/8/27.
//

#include <jni.h>
#include <string>
#include <sys/time.h>
#include "logger.h"

long getCurrentTime();
void jni2jniVoid();

extern "C"
JNIEXPORT void JNICALL
Java_com_sslyxhz_ndkcourse_NativeCostTimeAdapter_nativeJava2JniVoid(JNIEnv *env, jobject instance) {

}


extern "C"
JNIEXPORT void JNICALL
Java_com_sslyxhz_ndkcourse_NativeCostTimeAdapter_nativeJni2JavaVoid(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/NativeCostTimeAdapter");
    jmethodID init_mid = env->GetMethodID(cls, "<init>", "()V");
    jmethodID test_mid = env->GetMethodID(cls, "getTestVoid", "()V");
    jfieldID test_times_fid = env->GetStaticFieldID(cls, "TEST_TIMES", "I");
    jobject objAdapter = env->NewObject(cls, init_mid);

    int TEST_TIMES =  env->GetStaticIntField(cls,test_times_fid);
    long startTime = getCurrentTime();
    for(int i = 0; i< TEST_TIMES;++i){
        env->CallVoidMethod(objAdapter, test_mid);
    }
    long costTime = getCurrentTime() - startTime;
    LOGI("nativeJni2JavaVoid, cost time = %ld, times:%d", costTime, TEST_TIMES);

    env->DeleteLocalRef(objAdapter);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sslyxhz_ndkcourse_NativeCostTimeAdapter_nativeJni2JniVoid(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/NativeCostTimeAdapter");
    jfieldID test_times_fid = env->GetStaticFieldID(cls, "TEST_TIMES", "I");
    int TEST_TIMES =  env->GetStaticIntField(cls,test_times_fid);
    long startTime = getCurrentTime();
    for(int i = 0; i< TEST_TIMES;++i){
        jni2jniVoid();
    }
    long costTime = getCurrentTime() - startTime;
    LOGI("nativeJni2JniVoid, cost time = %ld, test times:%d", costTime, TEST_TIMES);

}

void jni2jniVoid(){

}

long getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}