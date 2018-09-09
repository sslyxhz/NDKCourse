//
// Created by xh.zeng on 2017/7/16.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#include "native_operate.h"

extern "C"
JNIEXPORT jint JNICALL
/**
 * native调用Java非静态方法
 * @param env
 * @param instance
 * @return
 */
Java_com_sslyxhz_ndkcourse_NativeOperateAdapter_nativeCallJavaNonStaticMethod(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/NativeOperateAdapter");
    jmethodID init_mid = env->GetMethodID(cls, "<init>", "()V");
    jobject objAdapter = env->NewObject(cls, init_mid);

    jmethodID non_static_mid = env->GetMethodID(cls, "javaNonStaticMethod", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring param = env->NewStringUTF("native params 2333.");
    if(non_static_mid){
        jstring result = (jstring)env->CallObjectMethod(objAdapter, non_static_mid, param);
        const char* charsResults = env->GetStringUTFChars(result, 0);
//        __android_log_print(ANDROID_LOG_DEBUG, "native_operate->nativeCallJavaNonStaticMethod", charsResults);
        return 1;
    } else{
        return -1;
    }
}

extern "C"
JNIEXPORT jint JNICALL
/**
 * native调用静态方法
 * @param env
 * @param instance
 * @return
 */
Java_com_sslyxhz_ndkcourse_NativeOperateAdapter_nativeCallJavaStaticMethod(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/NativeOperateAdapter");
    jmethodID static_mid = env->GetStaticMethodID(cls, "javaStaticMethod", "(Ljava/lang/String;)Ljava/lang/String;");
    if(static_mid){
        jstring param = env->NewStringUTF("native params 2333.");
        jstring result = (jstring)env->CallStaticObjectMethod(cls, static_mid, param);
        return 1;
    } else{
        return -1;
    }
}