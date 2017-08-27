package com.sslyxhz.ndkcourse;

/**
 * Created by xh.zeng on 2017/8/27.
 *
 * 测试调用的耗费时间
 */

public class NativeCostTimeAdapter {
    public static final String TAG = NativeCostTimeAdapter.class.getSimpleName();
    private static final int TEST_TIMES = 100000000;   // 测试次数

    public static String testCostTime(){
        NativeCostTimeAdapter nativeAdapter = new NativeCostTimeAdapter();

        StringBuffer results = new StringBuffer();
        results.append("costTimeJavaGetJniVoid() = " + nativeAdapter.costTimeJava2JniVoid()+"\n");  // 1亿次， 61808 ms
        results.append("costTimeJniGetJavaVoid() = " + nativeAdapter.costTimeJni2JavaVoid()+"\n");  // 1亿次， 121099 ms

        results.append("costTimeJava2JavaVoid() = " + nativeAdapter.costTimeJava2JavaVoid()+"\n");  // 1亿次， 38462 ms
        results.append("costTimeJni2JniVoid() = " + nativeAdapter.costTimeJni2JniVoid()+"\n");      // 1亿次， 995 ms
        return results.toString();
    }

    /**
     * 从Java反复调用Jni方法
     * @return
     */
    private long costTimeJava2JniVoid(){
        long startTime = System.currentTimeMillis();
        for(int i=0; i<TEST_TIMES; ++i){
            nativeJava2JniVoid();
        }
        long costTime = System.currentTimeMillis() - startTime;
        return costTime;
    }

    /**
     * 从Jni反复调用Java方法
     * @return
     */
    private long costTimeJni2JavaVoid(){
        long startTime = System.currentTimeMillis();
        nativeJni2JavaVoid();
        long costTime = System.currentTimeMillis() - startTime;
        return costTime;
    }

    /**
     * Java反复调用Java方法
     * @return
     */
    private long costTimeJava2JavaVoid(){
        long startTime = System.currentTimeMillis();
        for(int i=0; i<TEST_TIMES; ++i){
            java2JavaVoid();
        }
        long costTime = System.currentTimeMillis() - startTime;
        return costTime;
    }

    /**
     * Jni反复调用Jni方法
     * @return
     */
    private long costTimeJni2JniVoid(){
        long startTime = System.currentTimeMillis();
        nativeJni2JniVoid();
        long costTime = System.currentTimeMillis() - startTime;
        return costTime;
    }

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
