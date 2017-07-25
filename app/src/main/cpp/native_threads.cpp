//
// Created by xh.zeng on 2017/7/16.
//

#include <jni.h>
#include <string>
#include <pthread.h>
#include <sys/syscall.h>
#include <android/log.h>
#include "native_threads.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-threads", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-threads", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "native-threads", __VA_ARGS__))

#define NUMTHREADS 1

//全局变量
JavaVM *g_jvm = NULL;
jobject g_instance = NULL;      // activity instance
jobject g_testClass = NULL;     // test class

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
    env->DeleteGlobalRef(g_instance);
    env->DeleteGlobalRef(g_testClass);
    return JNI_VERSION_1_6;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sslyxhz_ndkcourse_NativeThreadsAdapter_setJNIEnv(JNIEnv *env, jobject instance) {
    LOGI("**** Java call setJNIEnv, TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    env->GetJavaVM(&g_jvm); //保存全局JVM以便在子线程中使用
    g_instance = env->NewGlobalRef(instance);

    if(env->FindClass("com/sslyxhz/ndkcourse/JNINeedTestClass") == NULL) {
        LOGE("**** OnLoad FindClass() Error.....");
    } else{
        g_testClass = env->NewGlobalRef((jobject)env->FindClass("com/xhz/ndkcourse/JniNeedTestClass"));
    }
}

extern "C"
void *thread_callStaticFun(void *arg) {
    JNIEnv *env;
    jclass cls;
    jmethodID staticMid;

    LOGI("**** jni child thread, callStaticFun, before attach TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    if(g_jvm->AttachCurrentThread( &env, NULL) != JNI_OK) {
        LOGE("**** %s: AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    LOGI("**** jni child thread, callStaticFun, after attach TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));

    cls = env->GetObjectClass(g_instance);
    if(cls == NULL) {
        LOGE("**** jni child thread, GetObjectClass() Error.....");
        goto error;
    }
    staticMid = env->GetStaticMethodID(cls, "staticMethodInJava", "(I)V");  // 调用Java中的静态方法
    if (staticMid == NULL) {
        LOGE("**** GetStaticMethodID() Error.....");
        goto error;
    }
    env->CallStaticVoidMethod(cls, staticMid, (long)arg);
    env->DeleteLocalRef(cls);

    error:
    if(g_jvm->DetachCurrentThread() != JNI_OK) {
        LOGE("**** %s: DetachCurrentThread() failed", __FUNCTION__);
    }

    pthread_exit(0);
}

extern "C"
void *thread_callNonStaticFun(void *arg) {
    JNIEnv *env;
    jclass cls;
    jmethodID ctor, mid;
    jobject obj;

    LOGI("**** jni child thread, callNonStaticFun, before attach TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    if(g_jvm->AttachCurrentThread( &env, NULL) != JNI_OK) {
        LOGE("%s: AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    LOGI("**** jni child thread, callNonStaticFun, after attach TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));

//    cls = env->FindClass("com/xhz/ndkcourse/JniNeedTestClass");   // 找不到这个类，放在setJNIEnv或OnLoad中加载
    cls = (jclass)env->NewLocalRef(g_testClass);
    if(cls == NULL) {
        LOGE("**** jni child thread, FindClass() Error.....");
        goto error;
    }
    ctor = env->GetMethodID(cls, "<init>", "()V");
    mid = env->GetMethodID(cls, "nonStaticMethodInJava", "(I)V");   // 调用Java中的实例方法
    if (mid == NULL) {
        LOGE("**** jni child thread, GetMethodID() Error.....");
        goto error;
    }
    obj = env->NewObject(cls, ctor);
    env->CallVoidMethod(obj, mid);

    env->DeleteLocalRef(obj);
    env->DeleteLocalRef(cls);

    error:
    if(g_jvm->DetachCurrentThread() != JNI_OK) {
        LOGE("**** %s: DetachCurrentThread() failed", __FUNCTION__);
    }

    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sslyxhz_ndkcourse_NativeThreadsAdapter_callJNIMethodInMainThread(JNIEnv *env, jobject instance) {
    LOGI("**** Java call callJNIMethodInMainThread, TID: %d, PID: %d", syscall(__NR_gettid), syscall(__NR_getpid));
    int i = 0;
    pthread_t ptStaticFunc[NUMTHREADS], ptNonStaticFunc[NUMTHREADS];

    for (i = 0; i < NUMTHREADS; i++) {
        pthread_create(&ptStaticFunc[i], NULL, &thread_callStaticFun, (void *) i);
    }

    for (i = 0; i < NUMTHREADS; i++) {
        pthread_create(&ptNonStaticFunc[i], NULL, &thread_callNonStaticFun, (void *) i);
    }

}