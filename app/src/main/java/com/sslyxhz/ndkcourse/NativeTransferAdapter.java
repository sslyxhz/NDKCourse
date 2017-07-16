package com.sslyxhz.ndkcourse;

import java.util.List;

/**
 * Created by xh.zeng on 2017/7/16.
 *
 * 参数传递
 */

public class NativeTransferAdapter {

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

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



    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-transfer");
    }
}
