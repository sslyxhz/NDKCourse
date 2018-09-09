//
// Created by xh.zeng on 2017/7/16.
//

#include <jni.h>
#include <string>
#include "native_transfer.h"

/**
 * native返回基本数据类型
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getIntData(JNIEnv *env, jobject instance) {
//    printf("pthread_self()=%d", pthread_self());
    jint result = 123;
    return result;
}

extern "C"
JNIEXPORT jbyte JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getByteData(JNIEnv *env, jobject instance) {
    jbyte result = 'a';
    return result;
}

extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getByteArrayData(JNIEnv *env, jobject instance) {
    jbyteArray result;
    return result;
}

/**
 * native返回基本引用类型
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getStringData(JNIEnv *env, jobject instance) {
    jstring result = env->NewStringUTF("Hello from JNI 666");
    return result;
}

/**
 * native返回数组类型
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getArrayRefData(JNIEnv *env, jobject instance) {
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

/**
 * native返回自定义类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getRefData(JNIEnv *env, jobject instance) {
    jclass cls = env->FindClass("com/sslyxhz/ndkcourse/RefData");
    jmethodID initMid = env->GetMethodID(cls, "<init>", "()V");
    jfieldID id = env->GetFieldID(cls,"id","I");
    jfieldID name = env->GetFieldID(cls,"name","Ljava/lang/String;");

    jobject obj = env->NewObject(cls,initMid);
    env->SetIntField(obj, id, 101);
    env->SetObjectField(obj, name,env->NewStringUTF("TestName"));

    return obj;
}

/**
 * native返回List类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getListData(JNIEnv *env, jobject instance) {
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

/**
 * native返回set类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getSetData(JNIEnv *env, jobject instance) {
    jclass hashset_cls = env->FindClass("java/util/HashSet");
    if(hashset_cls == NULL){
        return NULL;
    }
    jmethodID init_set_mid = env->GetMethodID(hashset_cls, "<init>", "()V");
    jmethodID add_set_mid = env->GetMethodID(hashset_cls, "add", "(Ljava/lang/Object;)Z");
    jobject set_obj = env->NewObject(hashset_cls, init_set_mid);

    jclass ref_cls = env->FindClass("com/sslyxhz/ndkcourse/RefData");
    jmethodID init_ref_mid = env->GetMethodID(ref_cls, "<init>", "(ILjava/lang/String;)V");

    for(int i=0;i<3;++i){
        jstring testName = env->NewStringUTF("TestName");
        jobject testRefData = env->NewObject(ref_cls, init_ref_mid, i, testName);
        env->CallBooleanMethod(set_obj, add_set_mid, testRefData);
    }
    return set_obj;
}

/**
 * native返回map类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getMapData(JNIEnv *env, jobject instance) {
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    if(hashMapClass == NULL){
        return NULL;
    }
    jmethodID init_map_mid = env->GetMethodID(hashMapClass, "<init>", "()V");
    jmethodID put_map_mid = env->GetMethodID(hashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jobject map_obj = env->NewObject(hashMapClass, init_map_mid);

    jclass ref_cls = env->FindClass("com/sslyxhz/ndkcourse/RefData");
    jmethodID init_ref_mid = env->GetMethodID(ref_cls, "<init>", "(ILjava/lang/String;)V");
    jclass long_cls = env->FindClass("java/lang/Long");
    jmethodID longInitMethod = env->GetStaticMethodID(long_cls, "valueOf", "(J)Ljava/lang/Long;");

    for(int i=0;i<3;++i){
        jstring testName = env->NewStringUTF("TestName");
        jobject testRefData = env->NewObject(ref_cls, init_ref_mid, i, testName);
        jobject testData = env->CallStaticObjectMethod(long_cls, longInitMethod, i);
        env->CallObjectMethod(map_obj, put_map_mid, testRefData, testData);

        env->DeleteLocalRef(testRefData);
        env->DeleteLocalRef(testData);
    }

    return map_obj;
}

/**
 * 传递基本类型数据
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_passBasicTypeData(JNIEnv *env, jobject instance, jstring param_) {
    const char *param = env->GetStringUTFChars(param_, 0);

    env->ReleaseStringUTFChars(param_, param);

    return env->NewStringUTF("Deal by jni..");
}

/**
 * 传递自定义类型数据
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_passCustomTypeData(JNIEnv *env, jobject instance, jobject param) {
    jclass ref_cls = env->GetObjectClass(param);
    if(ref_cls == NULL){
        return env->NewStringUTF("Error, ref_cls = NULL.");
    }

    jfieldID idFieldID = env->GetFieldID(ref_cls, "id", "I");
    jfieldID nameFieldID = env->GetFieldID(ref_cls, "name", "Ljava/lang/String;");

    jint id = env->GetIntField(param, idFieldID);
    jstring name = (jstring)env->GetObjectField(param, nameFieldID);

    const char* c_name = env->GetStringUTFChars(name, NULL);

    std::string str_name = c_name;
//    env->ReleaseStringUTFChars(name, c_name);

    return env->NewStringUTF(c_name);
}