#include <jni.h>
#include <string>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    printf("pthread_self()=%d", pthread_self());
    return env->NewStringUTF(hello.c_str());
}
