//
// Created by xh.zeng on 2017/7/16.
//

#include <jni.h>
#include <string>
#include "native_transfer.h"
#include "logger.h"

//#define LOG_TAG "native_transfer"

/**
 * native解析int参数，返回int结果
 */
extern "C"
JNIEXPORT jint JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getIntData(JNIEnv *env, jobject instance, jint param) {
    LOGI("getIntData, param:%d", param);
    jint result = param + 1;
    return result;
}


/**
 * native解析二维数组参数，返回二维数组结果
 */
extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getIntByteArraysData(JNIEnv *env, jobject instance, jobjectArray param) {
    jint rows = env->GetArrayLength(param);
    for(int i=0;i<rows; ++i) {
        jintArray rowArray = (jintArray) env->GetObjectArrayElement(param, i);
        int cols = env->GetArrayLength(rowArray);
        for(int j=0; j<cols; ++j){
            jint value = env->GetIntArrayElements(rowArray, 0)[j];
            LOGI("getIntByteArraysData, param : <%d, %d> = %d", i, j, value);
        }
    }

    int size = 3;
    jclass intArrayClass = env->FindClass("[I");
    jobjectArray result = env->NewObjectArray(size,intArrayClass, NULL);

    for(int i=0;i<size;i++){
        jintArray rowArray = env->NewIntArray(size);
        jint tempArray[size];
        for(int j=0;j<size;j++){
            tempArray[j]=i+j;
        }
        env->SetIntArrayRegion(rowArray,0,size,tempArray);

        env->SetObjectArrayElement(result,i,rowArray);

        env->DeleteLocalRef(rowArray);
    }
    env->DeleteLocalRef(intArrayClass);

    return result;
}


/**
 * native解析byte参数，返回byte结果
 */
extern "C"
JNIEXPORT jbyte JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getByteData(JNIEnv *env, jobject instance, jbyte param) {
    LOGI("getByteData, param:%c", param);

    jbyte result = (jbyte) (param+1);
    return result;
}

/**
 * native返回字节数组类型
 */
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getByteArrayData(JNIEnv *env, jobject instance, jbyteArray param) {
    jint rows = env->GetArrayLength(param);
    for(int i=0;i<rows; ++i) {
        LOGI("getByteArrayData, param[%d] = %d", i, param[i]);
    }

    int size = 3;
    jbyteArray result = env->NewByteArray(size);
    jbyte* data = (jbyte *)malloc(size * sizeof(jbyte));
    env->SetByteArrayRegion(result, 0, size, data);  // jbyte* to jbyteArray
    return result;
}

/**
 * native返回基本引用类型
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getStringData(JNIEnv *env, jobject instance, jstring param) {
    const char* content = env->GetStringUTFChars(param, JNI_FALSE);
    LOGI("getStringData, param:%s", content);
    env->DeleteLocalRef(param);

    jstring result = env->NewStringUTF("Hello from JNI 666");
    return result;
}

/**
 * native返回自定义类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getRefData(JNIEnv *env, jobject instance, jobject param) {
    jclass ref_cls = env->GetObjectClass(param);
    if(ref_cls == NULL){
        return env->NewStringUTF("Error, ref_cls = NULL.");
    }

//    jmethodID initMethidID = env->GetMethodID(ref_cls, "<init>", "(ILjava/lang/String;)V");
    jmethodID initMethidID = env->GetMethodID(ref_cls, "<init>", "()V");

    jfieldID idFieldID = env->GetFieldID(ref_cls, "id", "I");
    jfieldID nameFieldID = env->GetFieldID(ref_cls, "name", "Ljava/lang/String;");

    jint id = env->GetIntField(param, idFieldID);
    jstring name = (jstring)env->GetObjectField(param, nameFieldID);
    const char* c_name = env->GetStringUTFChars(name, NULL);
    LOGI("getRefData, param:<%d,%s>", id, c_name);
    env->DeleteLocalRef(param);

//    jstring name2 = env->NewStringUTF("name2hhh");
//    jobject result = env->NewObject(ref_cls, initMethidID, id+1, name2);

    jobject result = env->NewObject(ref_cls,initMethidID);
    jstring testName = env->NewStringUTF("TestName");
    env->SetIntField(result, idFieldID, 101);
    env->SetObjectField(result, nameFieldID, testName);
    env->DeleteLocalRef(testName);
    env->DeleteLocalRef(ref_cls);

    return result;
}

/**
 * native返回List类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getListData(JNIEnv *env, jobject instance, jobject param) {
    jclass listClass = env->FindClass("java/util/ArrayList");
    if(listClass == NULL){
        return NULL;
    }
    jmethodID init_list_mid = env->GetMethodID(listClass, "<init>", "()V");
    jmethodID add_list_mid = env->GetMethodID(listClass, "add", "(Ljava/lang/Object;)Z");
    jmethodID get_list_mid = env->GetMethodID(listClass, "get", "(I)Ljava/lang/Object;");
    jmethodID size_list_mid = env->GetMethodID(listClass, "size", "()I");

    int len = env->CallIntMethod(param, size_list_mid);
    for (int i = 0; i < len; ++i) {
        jstring jvalue = (jstring)env->CallObjectMethod(param, get_list_mid, i);
        const char* cvalue = env->GetStringUTFChars(jvalue, JNI_FALSE);
        LOGI("getListData, param item:%s", cvalue);
        env->DeleteLocalRef(jvalue);
    }

    int size = 3;
    jobject result = env->NewObject(listClass, init_list_mid);
    for(int i=0;i<size;++i){
        jstring testName = env->NewStringUTF("TestName");
        env->CallBooleanMethod(result, add_list_mid, testName);
        env->DeleteLocalRef(testName);
    }
    env->DeleteLocalRef(listClass);
    return result;
}

/**
 * native返回set类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getSetData(JNIEnv *env, jobject instance, jobject param) {
    jclass hashSetClass = env->FindClass("java/util/HashSet");
    jclass iteratorClass = env->FindClass("java/util/Iterator");
    if(hashSetClass == NULL || iteratorClass == NULL){
        return NULL;
    }
    jmethodID init_set_mid = env->GetMethodID(hashSetClass, "<init>", "()V");
    jmethodID add_set_mid = env->GetMethodID(hashSetClass, "add", "(Ljava/lang/Object;)Z");
    jmethodID iterator_set_mid = env->GetMethodID(hashSetClass, "iterator", "()Ljava/util/Iterator;");

    jmethodID hasNext_iter_mid = env->GetMethodID(iteratorClass, "hasNext", "()Z");
    jmethodID next_iter_mid = env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");

    jobject iter_obj = env->CallObjectMethod(param, iterator_set_mid);
    while(env->CallBooleanMethod(iter_obj, hasNext_iter_mid)) {
        jstring jvalue = (jstring) env->CallObjectMethod(iter_obj, next_iter_mid);
        const char* cvalue = env->GetStringUTFChars(jvalue, JNI_FALSE);
        LOGI("getSetData, param item:%s", cvalue);
        env->DeleteLocalRef(jvalue);
    }

    jobject result = env->NewObject(hashSetClass, init_set_mid);
    int size = 3;
    for(int i=0;i<size;++i){
        jstring testName = env->NewStringUTF("TestNameFromC++");
        env->CallBooleanMethod(result, add_set_mid, testName);
        env->DeleteLocalRef(testName);
    }
    env->DeleteLocalRef(hashSetClass);
    env->DeleteLocalRef(iteratorClass);
    return result;
}

/**
 * native返回map类型
 */
extern "C"
JNIEXPORT jobject JNICALL
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getMapData(JNIEnv *env, jobject instance, jobject param) {
    jclass hashMapClass = env->FindClass("java/util/HashMap");
    jclass setClass = env->FindClass("java/util/Set");
    jclass iteratorClass = env->FindClass("java/util/Iterator");
    if(hashMapClass == NULL || iteratorClass == NULL){
        return NULL;
    }

    jmethodID init_map_mid = env->GetMethodID(hashMapClass, "<init>", "()V");
    jmethodID put_map_mid = env->GetMethodID(hashMapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
    jmethodID get_map_mid = env->GetMethodID(hashMapClass, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
    jmethodID keySet_map_mid = env->GetMethodID(hashMapClass, "keySet", "()Ljava/util/Set;");

    jmethodID iterator_set_mid = env->GetMethodID(setClass, "iterator", "()Ljava/util/Iterator;");

    jmethodID hasNext_iter_mid = env->GetMethodID(iteratorClass, "hasNext", "()Z");
    jmethodID next_iter_mid = env->GetMethodID(iteratorClass, "next", "()Ljava/lang/Object;");


    jobject jKeySet = env->CallObjectMethod(param, keySet_map_mid);
    jobject jIterarot = env->CallObjectMethod(jKeySet, iterator_set_mid);
    while(env->CallBooleanMethod(jIterarot, hasNext_iter_mid)) {
        jstring jHashMapKey = (jstring) env->CallObjectMethod(jIterarot, next_iter_mid);
        jstring jHashMapValue = (jstring) env->CallObjectMethod(param, get_map_mid, jHashMapKey);

        const char *strKey = env->GetStringUTFChars(jHashMapKey, JNI_FALSE);
        const char *strValue = env->GetStringUTFChars(jHashMapValue, JNI_FALSE);

        LOGI("getMapData, param <%s, %s>", strKey, strValue);

//        env->ReleaseStringUTFChars(jHashMapKey, strKey);
//        env->ReleaseStringUTFChars(jHashMapValue, strValue);
        env->DeleteLocalRef(jHashMapKey);
        env->DeleteLocalRef(jHashMapValue);
    }
    env->DeleteLocalRef(jKeySet);
    env->DeleteLocalRef(jIterarot);
    env->DeleteLocalRef(setClass);
    env->DeleteLocalRef(iteratorClass);

    jobject result = env->NewObject(hashMapClass, init_map_mid);
    for(int i=0;i<3;++i){
        jstring testKey = env->NewStringUTF("TestKey");
        jstring testValue = env->NewStringUTF("TestValue");
        env->CallObjectMethod(result, put_map_mid, testKey, testValue);

        env->DeleteLocalRef(testKey);
        env->DeleteLocalRef(testValue);
    }
    env->DeleteLocalRef(hashMapClass);

    return result;
}