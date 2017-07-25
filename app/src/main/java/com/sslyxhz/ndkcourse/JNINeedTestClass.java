package com.sslyxhz.ndkcourse;

import android.util.Log;

/**
 * Created by xh.zeng on 2017/7/17.
 */

public class JNINeedTestClass {

    public void nonStaticMethodInJava(int i){
        Log.d(MainActivity.class.getSimpleName(), "**** JNI call nonStaticMethodInJava, Thread id="+Thread.currentThread().getId()+", tid="+android.os.Process.myTid()+", pid="+android.os.Process.myPid());
    }

}
