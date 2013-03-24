package com.example.android_client;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import android.net.ParseException;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.net.ParseException;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class MainActivity extends Activity {
	private Handler mMainHandler, mChildHandler;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		 /*
         * Create the main handler on the main thread so it is bound to the main
         * thread's message queue. 
         */
        mMainHandler = new Handler() {
            
            public void handleMessage(Message msg) {
                
                //Log.i(TAG, "Got an incoming message from the child thread - "  + (String)msg.obj);
                
                /*
                 * Handle the message coming from the child thread.
                 */
               // mTextView.setText(mTextView.getText() + (String)msg.obj + "\n");
            }
        };
        new ChildThread().start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	public void OffLed(View view) {
		new Thread(new Runnable() {
            public void run() {
                 HttpClient httpclient = new DefaultHttpClient();
                    HttpGet httpget2 = new HttpGet("http://home.wangkangle.com/set/low");
                        HttpResponse response2 = null;
                        try {
                            response2 = httpclient.execute(httpget2);
                        } catch (ClientProtocolException e1) {
                            // TODO Auto-generated catch block
                            e1.printStackTrace();
                        } catch (IOException e1) {
                            // TODO Auto-generated catch block
                            e1.printStackTrace();
                        }
                    HttpEntity entity = response2.getEntity();
                    if (entity != null) {
                        long len = entity.getContentLength();
                        /*if (len != -1)*/ {
                            try {
                                    String content_baidu = EntityUtils.toString(entity);
                                    //Log.d(TAG, content_baidu);
                                    
                                } catch (ParseException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                } catch (org.apache.http.ParseException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                } catch (IOException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                }
                        } /*else {
                            // Stream content out
                        }*/
                    }
                    }
            
        }).start();
	}

	public void OnLed(View view) {
		 /*
         * We cannot guarantee that the mChildHandler is created 
         * in the child thread by the time the user clicks the button.
         */
        if (mChildHandler != null) {
            
            /* 
             * Send a message to the child thread.
             */
            Message msg = mChildHandler.obtainMessage();
            msg.obj = mMainHandler.getLooper().getThread().getName() + " says Hello";
            mChildHandler.sendMessage(msg);
            //Log.i(TAG, "Send a message to the child thread - " + (String)msg.obj);
        }
		
		/*
		new Thread(new Runnable() {
            public void run() {
                 HttpClient httpclient = new DefaultHttpClient();
                    HttpGet httpget2 = new HttpGet("http://home.wangkangle.com/set/high");
                        HttpResponse response2 = null;
                        try {
                            response2 = httpclient.execute(httpget2);
                        } catch (ClientProtocolException e1) {
                            // TODO Auto-generated catch block
                            e1.printStackTrace();
                        } catch (IOException e1) {
                            // TODO Auto-generated catch block
                            e1.printStackTrace();
                        }
                    HttpEntity entity = response2.getEntity();
                    if (entity != null) {
                        long len = entity.getContentLength();
                        //if (len != -1) 
                        {
                            try {
                                      String content_baidu = EntityUtils.toString(entity);
                                    //Log.d(TAG, content_baidu);
                                    
                                } catch (ParseException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                } catch (org.apache.http.ParseException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                } catch (IOException e) {
                                    // TODO Auto-generated catch block
                                    e.printStackTrace();
                                }
                        }
                        // else {
                            // Stream content out
                        //}
                    }
                    }
            
        }).start();*/
	}
	
	
    class ChildThread extends Thread {      
        private static final String INNER_TAG = "ChildThread";     
        public void run() {          
            this.setName("child");
            Looper.prepare();
            mChildHandler = new Handler() {          
                public void handleMessage(Message msg) {  
                	String s_msg = (String)msg.obj;
                    Log.i(INNER_TAG, "Got an incoming message from the main thread - " + s_msg);                           
                    try {
                    sleep(100);
                        
                       
                        Message toMain = mMainHandler.obtainMessage();
                        toMain.obj = "This is " + this.getLooper().getThread().getName() + 
                            ".  Did you send me \"" + (String)msg.obj + "\"?";
                        mMainHandler.sendMessage(toMain);
                        Log.i(INNER_TAG, "Send a message to the main thread - " + (String)toMain.obj);
                        
                    } catch (InterruptedException e) {
                      
                        e.printStackTrace();
                    }
                    
                }
            };
            
            Log.i(INNER_TAG, "Child handler is bound to - " + mChildHandler.getLooper().getThread().getName());                   
            Looper.loop();
        }
    }
}
