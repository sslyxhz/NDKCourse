package com.sslyxhz.ndkcourse;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);

        StringBuffer showText = new StringBuffer();
        showText.append(NativeTransferAdapter.testTransfer());
        showText.append("\n");
        showText.append(NativeOperateAdapter.testOperate());

        tv.setText(showText.toString());

        NativeThreadsAdapter.testThreads();
    }

}
