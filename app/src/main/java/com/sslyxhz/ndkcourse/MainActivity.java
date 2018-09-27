package com.sslyxhz.ndkcourse;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.sslyxhz.ndkcourse.test.NativeCostTimeTester;
import com.sslyxhz.ndkcourse.test.NativeTransferTester;

public class MainActivity extends AppCompatActivity {

    TextView tv;
    StringBuffer showText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv = (TextView) findViewById(R.id.sample_text);

        new Thread(new Runnable() {
            @Override
            public void run() {
                showText = new StringBuffer();
//                showText.append(NativeTransferAdapter.testTransfer());
//                showText.append("\n");
//
//                showText.append(NativeOperateAdapter.testOperate());
//                showText.append("\n");

//                showText.append(NativeCostTimeAdapter.testCostTime());
//                showText.append("\n");

                showText(showText.toString().trim());

//                NativeThreadsAdapter.testThreads();
//
//                NativeRegisterAdapter.testRegister();


                NativeCostTimeTester costTimeTester = new NativeCostTimeTester();
                costTimeTester.testAll();

                NativeTransferTester transferTester = new NativeTransferTester();
                transferTester.testAll();
            }
        }).start();


    }

    private void showText(final String text){
        tv.post(new Runnable() {

            @Override
            public void run() {
                tv.setText(text);
            }
        });
    }

}
