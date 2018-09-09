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

    public static String testTransfer(){
        NativeTransferAdapter nativeAdapter = new NativeTransferAdapter();
        StringBuffer results = new StringBuffer();

        results.append("getIntData() = "+ nativeAdapter.getIntData(233)+"\n");

        results.append("getIntByteArraysData().length = "+ nativeAdapter.getIntByteArraysData(new int[][]{{1,2},{3,4}}).length+"\n");

        results.append("getByteData() = "+ nativeAdapter.getByteData((byte) 'a')+"\n");

        results.append("getByteArrayData().length = "+ nativeAdapter.getByteArrayData(new byte[]{'a', 'b', 'c'}).length+"\n");

        results.append("getStringData() = "+ nativeAdapter.getStringData("HelloWorld")+"\n");

        results.append("getArrayRefData().length = "+ nativeAdapter.getArrayRefData().length+"\n");

        results.append("getRefData() = "+ nativeAdapter.getRefData()+"\n");

        results.append("getListData().get(2) = "+ nativeAdapter.getListData().get(2)+"\n");

        results.append("getSetData().size() = "+ nativeAdapter.getSetData().size()+"\n");

        results.append("getMapData().size() = "+ nativeAdapter.getMapData().size()+"\n");

        return results.toString();
    }

    public native int getIntData(int param);

    public native int[][] getIntByteArraysData(int[][] param);

    public native byte getByteData(byte param);

    public native byte[] getByteArrayData(byte[] param);

    public native String getStringData(String param);

    public native String[] getArrayRefData();

    public native RefData getRefData();

    public native List<RefData> getListData();

    public native Set<RefData> getSetData();

    public native Map<RefData, Long> getMapData();

    public native String passBasicTypeData(String param);

    public native String passCustomTypeData(RefData param);

    public native String passSetData(Set<RefData> param);

    public native String passMapData(Map<RefData, Long> param);

    static {
        System.loadLibrary("native-transfer");
    }
}
