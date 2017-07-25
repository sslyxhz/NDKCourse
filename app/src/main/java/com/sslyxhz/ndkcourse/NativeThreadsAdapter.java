package com.sslyxhz.ndkcourse;

import android.util.Log;

/**
 * Created by xh.zeng on 2017/7/16.
 */

public class NativeThreadsAdapter {
    public static final String TAG = NativeThreadsAdapter.class.getSimpleName();

    public static String testThreads(){
        NativeThreadsAdapter nativeAdapter = new NativeThreadsAdapter();
        nativeAdapter.callJNIMethodInMainThread();
        StringBuffer results = new StringBuffer();
        results.append("callJNIMethodInMainThread() = "+"\n");
        return results.toString();
    }

    //由JNI中的线程回调
    public static void staticMethodInJava(int i) {
        Log.d(MainActivity.class.getSimpleName(), "**** JNI call staticMethodInJava, Thread id="+Thread.currentThread().getId()+", tid="+android.os.Process.myTid()+", pid="+android.os.Process.myPid());
    }

    public native void setJNIEnv();
    public native void callJNIMethodInMainThread();

    static{
        System.loadLibrary("native-threads");
    }
}
