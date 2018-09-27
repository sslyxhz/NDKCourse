package com.sslyxhz.ndkcourse;

/**
 * Created by xh.zeng on 2017/8/27.
 *
 * 测试调用的耗费时间
 */

public class NativeCostTimeAdapter {
    public static final int TEST_TIMES = 100000000;   // 测试次数

    public void getTestVoid(){
        // void method, be called by jni
    }

    public void java2JavaVoid(){
        // void method, be called by java
    }

    public native void nativeJni2JniVoid();


    public native void nativeJava2JniVoid();


    public native void nativeJni2JavaVoid();


    static {
        System.loadLibrary("native-costtime");
    }
}
