//
// Created by xh.zeng on 2017/7/16.
//

#include <jni.h>
#include <string>
#include "native_transfer.h"

extern "C"
JNIEXPORT jint JNICALL
/**
 * native返回基本数据类型
 * @param env
 * @param instance
 * @return jint
 */
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_basicTypeDataFromJNI(JNIEnv *env, jobject instance) {
//    printf("pthread_self()=%d", pthread_self());
    jint result = 123;
    return result;
}

extern "C"
JNIEXPORT jstring JNICALL
/**
 * native返回基本引用类型
 * @param env
 * @param instance
 * @return jstring
 */
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_basicRefDataFromJNI(JNIEnv *env, jobject instance) {
    jstring result = env->NewStringUTF("Hello from JNI 666");
    return result;
}

extern "C"
JNIEXPORT jobjectArray JNICALL
/**
 * native返回数组类型
 * @param env
 * @param instance
 * @return jobjectArray
 */
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_arrayRefDataFromJNI(JNIEnv *env, jobject instance) {
    jobjectArray result = 0;
    jsize len = 3;
    jstring str;

    result = (jobjectArray)(env->NewObjectArray(len, env->FindClass("java/lang/String"), 0));
    for(int i = 0; i < len; i++) {
        str = env->NewStringUTF("hello ref data.");
        env->SetObjectArrayElement(result, i, str);
    }
    return result;
}

extern "C"
JNIEXPORT jobject JNICALL
/**
 * native返回自定义类型
 * @param env
 * @param instance
 * @return jobject
 */
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_customTypeDataFromJNI(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/RefData");
    jmethodID initMid = env->GetMethodID(cls, "<init>", "()V");
    jfieldID id = env->GetFieldID(cls,"id","I");
    jfieldID name = env->GetFieldID(cls,"name","Ljava/lang/String;");

    jobject obj = env->NewObject(cls,initMid);
    env->SetIntField(obj, id, 101);
    env->SetObjectField(obj, name,env->NewStringUTF("TestName"));

    return obj;
}

extern "C"
JNIEXPORT jobject JNICALL
/**
 * native返回List类型
 * @param env
 * @param instance
 * @return jobject
 */
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_listDataFromJNI(JNIEnv *env, jobject instance) {
    jclass list_cls = env->FindClass("java/util/ArrayList");
    if(list_cls == NULL){
        return NULL;
    }
    jmethodID init_list_mid = env->GetMethodID(list_cls, "<init>", "()V");
    jmethodID add_list_mid = env->GetMethodID(list_cls, "add", "(Ljava/lang/Object;)Z");
    jobject list_obj = env->NewObject(list_cls, init_list_mid);

    jclass ref_cls = env->FindClass("com/sslyxhz/ndkcourse/RefData");
    jmethodID init_ref_mid = env->GetMethodID(ref_cls, "<init>", "(ILjava/lang/String;)V");

    for(int i=0;i<3;++i){
        jstring testName = env->NewStringUTF("TestName");
        jobject testRefData = env->NewObject(ref_cls, init_ref_mid, i, testName);
        env->CallBooleanMethod(list_obj, add_list_mid, testRefData);
    }
    return list_obj;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_dealWithParam(JNIEnv *env, jobject instance, jstring param_) {
    const char *param = env->GetStringUTFChars(param_, 0);

    env->ReleaseStringUTFChars(param_, param);

    return env->NewStringUTF("Deal by jni..");
}