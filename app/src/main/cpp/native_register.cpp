//
// Created by xh.zeng on 2017/8/2.
// 动态注册
//

#include <jni.h>
#include <string>
#include "logger.h"
#include <sys/syscall.h>
#include "native_register.h"

jclass g_registerAdapter;


static JNINativeMethod gNatvieMethods[] = {
        {
                "testRegisterMethod",
                "()V",
                (void *) native_testRegisterMethod
        },
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

    jclass jAdapterClz = env->FindClass("com/sslyxhz/ndkcourse/NativeRegisterAdapter");
    g_registerAdapter = (jclass) env->NewGlobalRef((jobject)jAdapterClz);
    env->RegisterNatives(g_registerAdapter, gNatvieMethods, sizeof(gNatvieMethods)/ sizeof(JNINativeMethod));
    env->DeleteLocalRef(jAdapterClz);
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