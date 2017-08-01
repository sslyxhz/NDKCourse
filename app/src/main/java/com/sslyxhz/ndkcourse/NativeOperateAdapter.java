package com.sslyxhz.ndkcourse;

import android.util.Log;

/**
 * Created by xh.zeng on 2017/7/16.
 *
 * Native操作，调用上层静态方法和非静态方法
 */

public class NativeOperateAdapter {
    public static final String TAG = NativeOperateAdapter.class.getSimpleName();

    public static String testOperate(){
        NativeOperateAdapter nativeAdapter = new NativeOperateAdapter();
        StringBuffer results = new StringBuffer();
        results.append("nativeCallJavaNonStaticMethod() = " + nativeAdapter.nativeCallJavaNonStaticMethod()+"\n");
        results.append("nativeCallJavaStaticMethod() = " + nativeAdapter.nativeCallJavaStaticMethod()+"\n");
        return results.toString();
    }

    public String javaNonStaticMethod(String param){
        Log.d(TAG, "javaNonStaticMethod, pid = "+ android.os.Process.myPid() + ", tid="+android.os.Process.myTid());
        Log.d(TAG, "javaNonStaticMethod, param = "+param);
        return "OK";
    }

    public static String javaStaticMethod(String param){
        Log.d(TAG, "javaStaticMethod, pid = "+ android.os.Process.myPid() + ", tid="+android.os.Process.myTid());
        Log.d(TAG, "javaStaticMethod, param = "+param);
        return "OK";
    }

    public native int nativeCallJavaNonStaticMethod();
    public native int nativeCallJavaStaticMethod();

    static {
        System.loadLibrary("native-operate");
    }
}
