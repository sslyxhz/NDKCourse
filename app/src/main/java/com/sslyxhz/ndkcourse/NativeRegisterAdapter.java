package com.sslyxhz.ndkcourse;

/**
 * Created by xh.zeng on 2017/8/2.
 */

public class NativeRegisterAdapter {
    public static final String TAG = NativeOperateAdapter.class.getSimpleName();

    public static String testRegister(){
        NativeRegisterAdapter nativeAdapter = new NativeRegisterAdapter();
        StringBuffer results = new StringBuffer();

        nativeAdapter.testRegisterMethod();

        return results.toString();
    }

    public native void testRegisterMethod();

    static {
        System.loadLibrary("native-register");
    }
}
