package com.sslyxhz.ndkcourse.test;

import android.util.Log;

import com.sslyxhz.ndkcourse.NativeTransferAdapter;
import com.sslyxhz.ndkcourse.RefData;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class NativeTransferTester {
    private static final String TAG = NativeTransferTester.class.getSimpleName();

    private NativeTransferAdapter mAdapter;

    public NativeTransferTester(){
        mAdapter = new NativeTransferAdapter();
    }

    public void testAll(){
        testGetIntData();

        testGetIntByteArraysData();

        testGetByteData();

        testGetByteArrayData();

        testGetStringData();

        testGetRefData();

        testGetListData();

        testGetSetData();

        testGetMapData();
    }

    private void testGetIntData(){
        int param = 1;
        int result = mAdapter.getIntData(param);
        Log.d(TAG, "testGetIntData, param:"+param+", result:"+result);
    }

    private void testGetIntByteArraysData(){
        int[][] param = new int[][]{{1,2},{3,4}};
        int[][] result = mAdapter.getIntByteArraysData(param);
        Log.d(TAG, "testGetIntByteArraysData, param:"+param+", result:"+result);
    }

    private void testGetByteData(){
        byte param = 'a';
        byte result = mAdapter.getByteData(param);
        Log.d(TAG, "testGetByteData, param:"+param+", result:"+result);
    }

    private void testGetByteArrayData(){
        byte[] param = new byte[]{'a', 'b', 'c'};
        byte[] result = mAdapter.getByteArrayData(param);
        Log.d(TAG, "testGetByteArrayData, param:"+param+", result:"+result);
    }

    private void testGetStringData(){
        String param = "Hey!";
        String result = mAdapter.getStringData(param);
        Log.d(TAG, "testGetStringData, param:"+param+", result:"+result);
    }

    private void testGetRefData(){
        RefData param = new RefData(1, "haha");
        RefData result = mAdapter.getRefData(param);
        Log.d(TAG, "testGetRefData, param:"+param +", result:"+result);
    }

    private void testGetListData(){
        List<String> param = new ArrayList<>();
        param.add("TestItem1");
        param.add("TestItem2");
        List<String> result = mAdapter.getListData(param);

    }

    private void testGetSetData(){
        Set<String> param = new HashSet<>();
        param.add("TestItem1");
        param.add("TestItem2");
        Set<String> result = mAdapter.getSetData(param);
    }

    private void testGetMapData(){
        Map<String, String> param = new HashMap<>();
        param.put("TestKey1", "TestItem1");
        param.put("TestKey2", "TestItem2");
        Map<String, String> result = mAdapter.getMapData(param);

        Set<String> keyset = param.keySet();
        Iterator<String> iterator = keyset.iterator();
    }
}
