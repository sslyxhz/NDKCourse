package com.sslyxhz.ndkcourse;

/**
 * Created by xh.zeng on 2017/7/16.
 */

public class RefData {

    private int id;
    private String name;

    public RefData(){}

    public RefData(int id, String name){
        this.id = id;
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "(id = "+id+"; name = "+name+")";
    }
}
