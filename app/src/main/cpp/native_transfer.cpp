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
    const char* content = env->GetStringUTFChars(param, 0);
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
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getSetData(JNIEnv *env, jobject instance, jobject param) {



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
Java_com_sslyxhz_ndkcourse_NativeTransferAdapter_getMapData(JNIEnv *env, jobject instance, jobject param) {



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
