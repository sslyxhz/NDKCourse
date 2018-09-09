//
// Created by xh.zeng on 2017/8/2.
// 动态注册
//

#include <jni.h>
#include <string>
#include <android/log.h>
#include <sys/syscall.h>
#include "native_register.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-threads", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-threads", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-threads", __VA_ARGS__))

jclass g_registerAdapter;

void native_testRegisterMethod(JNIEnv *env, jobject obj);

static JNINativeMethod gNatvieMethods[] = {
        {"testRegisterMethod",             "()V",                             (void *) native_testRegisterMethod},
};

extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    //获取JNI版本
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("**** OnLoad GetEnv failed!");
        return result;
    }

    g_registerAdapter = (jclass)env->NewGlobalRef((jobject)env->FindClass("com/sslyxhz/ndkcourse/NativeRegisterAdapter"));
    env->RegisterNatives(g_registerAdapter, gNatvieMethods, sizeof(gNatvieMethods)/ sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT jint JNICALL
JNI_UnLoad(JavaVM *vm, void *reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("**** UnLoad GetEnv failed!");
        return result;
    }
    env->UnregisterNatives(g_registerAdapter);
    env->DeleteGlobalRef(g_registerAdapter);
    return JNI_VERSION_1_6;
}

void native_testRegisterMethod(JNIEnv *env, jobject instance) {
//    LOGI("****  call native_testRegisterMethod, TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
}