package com.example.bluetooth_test;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.app.Application;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.UUID;

public class MainActivity extends AppCompatActivity {
    static final int REQUEST_ENABLE_BT = 10;
    int mPariedDeviceCount = 0;
    Set<BluetoothDevice>mDevices;
    BluetoothAdapter mBluetoothAdapter;
    BluetoothDevice mRemoteDevie;
    BluetoothSocket mSocket = null;
    OutputStream mOutputStream =null;
    InputStream mInputStream = null;
    String mStrDelimiter="\n";
    char mCharDelimiter='\n';
    Thread mWorkerThread=null;
    byte[]readBuffer;
    int readBufferPosition;
    EditText mEditReceive, mEditSend;
    Button mButtonSend;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEditReceive = (EditText) findViewById(R.id.receiveString);
        mEditSend = (EditText) findViewById(R.id.sendString);
        mButtonSend = (Button) findViewById(R.id.sendButton);

        mButtonSend.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendData(mEditSend.getText().toString());
                mEditSend.setText("");
            }
        });
        checkBluetooth();
    }
    BluetoothDevice getDeviceFromBondedList(String name){
        BluetoothDevice selectedDevice = null;
        for(BluetoothDevice deivce : mDevices){
            if(name.equals(deivce.getName())){
                selectedDevice=deivce;
                break;
            }
        }
        return selectedDevice;
    }

    void sendData(String msg) {
        msg += mStrDelimiter;
        try {
            mOutputStream.write(msg.getBytes());
        } catch (Exception e) {
            Toast.makeText(getApplicationContext(), "????????? ????????? ????????? ??????", Toast.LENGTH_LONG).show();
            finish();
        }
    }

    void connectToSelectedDevice(String selectedDeviceName){
        mRemoteDevie = getDeviceFromBondedList(selectedDeviceName);
        UUID uuid=java.util.UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
        try {
            mSocket = mRemoteDevie.createRfcommSocketToServiceRecord(uuid);
            mSocket.connect();
            mOutputStream = mSocket.getOutputStream();
            mInputStream = mSocket.getInputStream();
            beginListenForData();
        }
        catch(Exception e) {
            Toast.makeText(getApplicationContext(),"???????????? ?????? ??? ????????? ??????????????????.",Toast.LENGTH_LONG).show();
            finish();
        }
    }

    void beginListenForData() {
        final Handler handler = new Handler();
        readBufferPosition = 0;
        readBuffer = new byte[1024];
        mWorkerThread = new Thread(new Runnable() {

            @Override
            public void run() {
                while (!Thread.currentThread().isInterrupted()) {
                    try {
                        int byteAvailable = mInputStream.available();
                        if (byteAvailable > 0) {
                            byte[] packetBytes = new byte[byteAvailable];
                            mInputStream.read(packetBytes);
                            for (int i = 0; i < byteAvailable; i++) {
                                byte b = packetBytes[i];
                                if (b == mCharDelimiter) {
                                    byte[] encodedBytes = new byte[readBufferPosition];
                                    System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
                                    final String data = new String(encodedBytes, "US-ASCII");
                                    readBufferPosition = 0;
                                    handler.post(new Runnable() {

                                        @Override
                                        public void run() {
                                            mEditReceive.setText(mEditReceive.getText().toString() + data + mStrDelimiter);
                                        }
                                    });
                                } else {
                                    readBuffer[readBufferPosition++] = b;
                                }
                            }
                        }
                    } catch (Exception e) {
                        Toast.makeText(getApplicationContext(), "????????? ?????? ??? ????????? ?????? ????????????.", Toast.LENGTH_LONG).show();
                        finish();
                    }
                }
            }
        });
    }
    void selectDevice() {
        mDevices = mBluetoothAdapter.getBondedDevices();
        mPariedDeviceCount = mDevices.size();
        if (mPariedDeviceCount == 0) {
            Toast.makeText(getApplicationContext(), "???????????? ????????? ????????????.", Toast.LENGTH_LONG).show();
            finish();
        }
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("???????????? ?????? ??????");
        List<String> listItems = new ArrayList<String>();
        for (BluetoothDevice device : mDevices) {
            listItems.add(device.getName());
        }
        listItems.add("??????");
        final CharSequence[] items = listItems.toArray(new CharSequence[listItems.size()]);
        listItems.toArray(new CharSequence[listItems.size()]);
        builder.setItems(items, new DialogInterface.OnClickListener() {

            @Override
            public void onClick(DialogInterface dialog, int item) {
                if (item == mPariedDeviceCount) {
                    Toast.makeText(getApplicationContext(), "????????? ????????? ???????????? ???????????????.", Toast.LENGTH_LONG).show();
                    finish();
                } else {
                    connectToSelectedDevice(items[item].toString());
                }
            }
        });
        builder.setCancelable(false);
        AlertDialog alert = builder.create();
        alert.show();
    }

    void checkBluetooth() {
        mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if(mBluetoothAdapter ==null){
            Toast.makeText(getApplicationContext(),"????????? ??????????????? ???????????? ????????????.", Toast.LENGTH_LONG).show();
            finish();
        }
        else {
            if(!mBluetoothAdapter.isEnabled()) {
                Toast.makeText(getApplicationContext(), "?????? ??????????????? ????????? ???????????????.", Toast.LENGTH_LONG).show();
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
            }
            else{
                selectDevice();
            }
        }
    }

    @Override
    protected void onDestroy() {
        try{
            mWorkerThread.interrupt();
            mInputStream.close();
            mSocket.close();
        }
        catch(Exception e){
        }
        super.onDestroy();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data){
        switch(requestCode) {
            case REQUEST_ENABLE_BT:
                if(resultCode == RESULT_OK) {
                    selectDevice();
                }
                else if(resultCode==RESULT_CANCELED){
                    Toast.makeText(getApplicationContext(),"??????????????? ????????? ??? ?????? ??????????????? ???????????????", Toast.LENGTH_LONG).show();
                    finish();
                }
                break;
        }
        super.onActivityResult(requestCode,resultCode,data);
    }
}




