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

import android.R.integer;
import android.net.ParseException;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Intent;
import android.graphics.PorterDuff;
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
import android.widget.Button;
//import android.R;

public class MainActivity extends Activity {
	private static final int WHITE = 0xFFFFFFFF;
	private static final int GREEN = 0xFF00FF00;
	private Handler mMainHandler, mChildHandler;
	private OnButton onButton = null;
	private OffButton offButton = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.activity_main);
		
		onButton = new OnButton((android.widget.Button) findViewById(R.id.button1));
		offButton = new OffButton((android.widget.Button) findViewById(R.id.button2));
		mMainHandler = new Handler() {
			public void handleMessage(Message msg) {
				String[] callback_msg = ((String) msg.obj).split(":");
				if (callback_msg[0].equals("high")) {
					onButton.setColor(GREEN);
					offButton.setColor(WHITE);
				} else if(callback_msg[0].equals("low")) {
					offButton.setColor(GREEN);
					onButton.setColor(WHITE);					
				}				
			}
		};
		new RequestThread().start();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
 
	public void OffLed(View view) {
		offButton.clicked("low");
	}

	public void OnLed(View view) {
		onButton.clicked("high");
	}

	class Button {
		protected android.widget.Button button_view = null;
		public Button(android.widget.Button button) {
			button_view = button;
		}
		public void clicked(String value) {
			Message msg = mChildHandler.obtainMessage();
			msg.obj = value;
			mChildHandler.sendMessage(msg);
		}
		public void setColor(int color){
			this.button_view.getBackground().setColorFilter(color, PorterDuff.Mode.MULTIPLY);
		}
	}

	class OnButton extends Button {
		public OnButton(android.widget.Button button) {
			super(button);
		}
		
		
		
	}

	class OffButton extends Button {
		public OffButton(android.widget.Button button) {
			super(button);
		}
	}

	class RequestThread extends Thread {
		private static final String INNER_TAG = "ChildThread";
		private HttpClient httpclient = new DefaultHttpClient();
		private HttpGet httpget = null;
		private HttpResponse response = null;

		public void run() {
			this.setName("child");
			Looper.prepare();
			mChildHandler = new Handler() {
				public void handleMessage(Message msg) {
					String s_msg = (String) msg.obj;
					if (s_msg.equals("high")) {
						httpget = new HttpGet(
								"http://home.wangkangle.com/set/high");
					} else if (s_msg.equals("low")) {
						httpget = new HttpGet(
								"http://home.wangkangle.com/set/low");
					}

					try {
						response = httpclient.execute(httpget);
					} catch (ClientProtocolException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					} catch (IOException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}

					HttpEntity entity = response.getEntity();
					if (entity != null) {
						long len = entity.getContentLength();
						{
							try {
								String contents = EntityUtils.toString(entity);
								Message toMain = mMainHandler.obtainMessage();
		                        toMain.obj = s_msg + ":" + contents;
		                        mMainHandler.sendMessage(toMain);
								
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
					}

				}

			};
			Looper.loop();
		}
	}
}
