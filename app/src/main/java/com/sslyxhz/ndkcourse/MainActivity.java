package com.sslyxhz.ndkcourse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        NativeTransferAdapter nativeAdapter = new NativeTransferAdapter();

        TextView tv = (TextView) findViewById(R.id.sample_text);
        StringBuffer results = new StringBuffer();
        results.append("int basicTypeDataFromJNI() = "+ nativeAdapter.basicTypeDataFromJNI()+"\n");
        results.append("String basicRefDataFromJNI() = "+ nativeAdapter.basicRefDataFromJNI()+"\n");
        results.append("String[] arrayRefDataFromJNI() = "+ nativeAdapter.arrayRefDataFromJNI()+"\n");
        results.append("RefData customTypeDataFromJNI() = "+ nativeAdapter.customTypeDataFromJNI()+"\n");
        results.append("List listDataFromJNI().get(2) = "+ nativeAdapter.listDataFromJNI().get(2)+"\n");
        tv.setText(results.toString());
    }

}
