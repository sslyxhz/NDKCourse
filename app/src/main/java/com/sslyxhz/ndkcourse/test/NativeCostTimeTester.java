package com.sslyxhz.ndkcourse.test;

import android.util.Log;

import com.sslyxhz.ndkcourse.NativeCostTimeAdapter;

public class NativeCostTimeTester {
    private static final String TAG = NativeCostTimeTester.class.getSimpleName();

    private NativeCostTimeAdapter mAdapter;

    public NativeCostTimeTester(){
        mAdapter = new NativeCostTimeAdapter();
    }

    public void testAll(){
        Log.d(TAG, "开始测试");

        javaCallJniVoidMethod();

        jniCallJavaMethod();

        javaCallJavaMethod();

        jniCallJniMethod();
    }

    /**
     * Java层，反复调用Jni空方法
     * @return
     */
    private long javaCallJniVoidMethod(){
        long startTime = System.currentTimeMillis();
        for(int i=0; i<NativeCostTimeAdapter.TEST_TIMES; ++i){
            mAdapter.nativeJava2JniVoid();
        }
        long costTime = System.currentTimeMillis() - startTime;
        Log.d(TAG, "java层反复调用jni空方法，耗时："+costTime+"ms");
        return costTime;
    }

    /**
     * Jni层，反复调用Java空方法
     * @return
     */
    private long jniCallJavaMethod(){
        long startTime = System.currentTimeMillis();
        mAdapter.nativeJni2JavaVoid();
        long costTime = System.currentTimeMillis() - startTime;
        Log.d(TAG, "jni层反复调用java空方法，耗时："+costTime+"ms");
        return costTime;
    }

    /**
     * Java层，反复调用Java空方法
     * @return
     */
    private long javaCallJavaMethod(){
        long startTime = System.currentTimeMillis();
        for(int i=0; i<NativeCostTimeAdapter.TEST_TIMES; ++i){
            mAdapter.java2JavaVoid();
        }
        long costTime = System.currentTimeMillis() - startTime;
        Log.d(TAG, "java层调用java空方法，耗时："+costTime+"ms");
        return costTime;
    }

    /**
     * Jni层，反复调用Jni方法
     * @return
     */
    private long jniCallJniMethod(){
        long startTime = System.currentTimeMillis();
        mAdapter.nativeJni2JniVoid();
        long costTime = System.currentTimeMillis() - startTime;
        Log.d(TAG, "jni层调用jni空方法，耗时："+costTime+"ms");
        return costTime;
    }

}
