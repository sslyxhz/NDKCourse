package com.sslyxhz.ndkcourse;

import java.util.List;

/**
 * Created by xh.zeng on 2017/7/16.
 *
 * Native参数传递
 */

public class NativeTransferAdapter {

    public static String testTransfer(){
        NativeTransferAdapter nativeAdapter = new NativeTransferAdapter();
        StringBuffer results = new StringBuffer();
        results.append("basicTypeDataFromJNI() = "+ nativeAdapter.basicTypeDataFromJNI()+"\n");
        results.append("basicRefDataFromJNI() = "+ nativeAdapter.basicRefDataFromJNI()+"\n");
        results.append("arrayRefDataFromJNI() = "+ nativeAdapter.arrayRefDataFromJNI()+"\n");
        results.append("customTypeDataFromJNI() = "+ nativeAdapter.customTypeDataFromJNI()+"\n");
        results.append("listDataFromJNI().get(2) = "+ nativeAdapter.listDataFromJNI().get(2)+"\n");
        return results.toString();
    }

    /**
     * 返回基础类型数据
     * @return
     */
    public native int basicTypeDataFromJNI();

    /**
     * 返回基本引用数据
     * @return
     */
    public native String basicRefDataFromJNI();

    /**
     * 返回引用数组
     * @return
     */
    public native String[] arrayRefDataFromJNI();

    /**
     * 返回自定义类型数据
     * @return
     */
    public native RefData customTypeDataFromJNI();

    /**
     * 返回List类型数据
     * @return
     */
    public native List<RefData> listDataFromJNI();


    public native String dealWithParam(String param);

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-transfer");
    }
}
