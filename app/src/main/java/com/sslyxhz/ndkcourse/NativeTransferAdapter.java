package com.sslyxhz.ndkcourse;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Created by xh.zeng on 2017/7/16.
 *
 * Native参数传递
 */
public class NativeTransferAdapter {


    /**
     * 基础形态，传递int类型
     * @param param
     * @return
     */
    public native int getIntData(int param);

    /**
     * 传递二维数组类型
     * @param param
     * @return
     */
    public native int[][] getIntByteArraysData(int[][] param);

    /**
     * 传递字节类型
     * @param param
     * @return
     */
    public native byte getByteData(byte param);

    /**
     * 传递字节数组类型
     * @param param
     * @return
     */
    public native byte[] getByteArrayData(byte[] param);

    /**
     * 传递字符串
     * @param param
     * @return
     */
    public native String getStringData(String param);

    /**
     * 传递自定义类型
     * @param param
     * @return
     */
    public native RefData getRefData(RefData param);

    /**
     * 传递List数据
     * @param param
     * @return
     */
    public native List<String> getListData(List<String> param);

    /**
     * 传递Set数据
     * @param param
     * @return
     */
    public native Set<String> getSetData(Set<String> param);

    /**
     * 传递Map数据
     * @param param
     * @return
     */
    public native Map<String, String> getMapData(Map<String, String> param);


    static {
        System.loadLibrary("native-transfer");
    }
}
