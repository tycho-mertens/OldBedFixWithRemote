package com.example.myapplication;

import android.annotation.SuppressLint;
import android.graphics.Color;
import android.os.Bundle;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;

import com.example.myapplication.databinding.ActivityMainBinding;
import org.apache.commons.net.telnet.TelnetClient;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.concurrent.TimeUnit;

public class MainActivity extends AppCompatActivity {

    private ActivityMainBinding binding;
    private Telnet telnet;

    private Button headUp;
    private Button headDown;
    private Button legsUp;
    private Button legsDown;
    private Button bothUp;
    private Button bothDown;

    @SuppressLint({"ClickableViewAccessibility", "SetTextI18n"})
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        headUp = findViewById(R.id.headUp);
        headDown = findViewById(R.id.headDown);
        legsUp = findViewById(R.id.legsUp);
        legsDown = findViewById(R.id.legsDown);
        bothUp = findViewById(R.id.bothUp);
        bothDown = findViewById(R.id.bothDown);

        TextView connectionText = findViewById(R.id.connectionTxt);

        button(headUp, "headUp");
        button(headDown, "headDown");

        button(legsUp, "legsUp");
        button(legsDown, "legsDown");

        button(bothUp, "bothUp");
        button(bothDown, "bothDown");

        telnet = new Telnet("10.0.0.102", 7700, connectionText);

        if(!telnet.isConnected())
            disableAllBtns();
    }


    @SuppressLint("ClickableViewAccessibility")
    public void button(Button b, String methodName) {
        b.setOnTouchListener((v, event) -> {
            switch(event.getAction()){
                case MotionEvent.ACTION_DOWN:
                    telnet.sendCmd("CMD " + methodName + " 1");
                    break;
                case MotionEvent.ACTION_UP:
                case MotionEvent.ACTION_CANCEL:
                    telnet.sendCmd("CMD " + methodName + " 0");
            }
            return false;
        });
    }

    public void disableAllBtns(){
        headUp.setEnabled(false);
        headDown.setEnabled(false);
        legsUp.setEnabled(false);
        legsDown.setEnabled(false);
        bothUp.setEnabled(false);
        bothDown.setEnabled(false);
    }

    public void enableAllBtns(){
        headUp.setEnabled(true);
        headDown.setEnabled(true);
        legsUp.setEnabled(true);
        legsDown.setEnabled(true);
        bothUp.setEnabled(true);
        bothDown.setEnabled(true);

    }

    public static class Telnet {
        public TelnetClient client;
        boolean isConnected = false;
        boolean failed = false;

        @SuppressLint("SetTextI18n")
        public Telnet(String ip, int port, TextView connectionTxt) {
            Thread t = new Thread(() -> {
                try {
                    client = new TelnetClient();
                    client.connect(ip, port);
                    isConnected = true;

                    connectionTxt.setText("CONNECTED");
                    connectionTxt.setTextColor(Color.GREEN);
                } catch (IOException e) {
                    connectionTxt.setText("ERROR");
                    connectionTxt.setTextColor(Color.RED);
                    e.printStackTrace();
                    failed = true;
                }
            });
            t.start();
            while (!isConnected)
                if(failed)return;

            sendCmd("MSG hello");
        }

        public boolean isConnected() {
            return isConnected;
        }

        public void sendCmd(String cmd) {
            new Thread(() -> {
                try {
                    String cmdT = cmd + "\r\n";
                    client.getOutputStream().write(cmdT.getBytes(StandardCharsets.UTF_8));
                    client.getOutputStream().flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }).start();
        }
    }
}
