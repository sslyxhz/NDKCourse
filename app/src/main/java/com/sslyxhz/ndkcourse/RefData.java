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
    public boolean equals(Object obj) {
        if(this == obj){
            return true;
        }
        if(obj == null || obj.getClass() != getClass()) {
            return false;
        }
        final RefData otherData = (RefData) obj;
        if(this.id != otherData.id){
            return false;
        }
        if(this.name != null && this.name.equals(otherData.name)){
            return true;
        }
        if(this.name == null && otherData.name == null){
            return true;
        }
        return false;
    }

    @Override
    public int hashCode() {
        int result =0;
        return result * 31 + id;
    }

    @Override
    public String toString() {
        return "(id = "+id+"; name = "+name+")";
    }
}
