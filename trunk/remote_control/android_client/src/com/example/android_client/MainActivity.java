package com.example.android_client;

import java.io.IOException;
import java.net.SocketTimeoutException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

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
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;
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
import android.app.ProgressDialog;
import android.content.Intent;
import android.graphics.PorterDuff;
import android.support.v4.app.NavUtils;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ProgressBar;
import android.widget.TextView;

import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.conn.ConnectTimeoutException;
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
	private static final String requestIp= "http://home.wangkangle.com:8000/";
	private Handler mMainHandler, mRequestHandler, mBeatHandler;
	private OnButton onButton = null;
	private OffButton offButton = null;
	private ProgressDialog mypDialog = null;
	private RequestThread requestThread;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		onButton = new OnButton(
				(android.widget.Button) findViewById(R.id.button1));
		offButton = new OffButton(
				(android.widget.Button) findViewById(R.id.button2));

		mMainHandler = new Handler() {
			public void handleMessage(Message msg) {
				String callback_msg = (String) msg.obj;
				mypDialog.hide();
				if (callback_msg.equals("high")) {
					onButton.setColor(GREEN);
					offButton.setColor(WHITE);
				} else if (callback_msg.equals("low")) {
					offButton.setColor(GREEN);
					onButton.setColor(WHITE);
				}
			}
		};
		requestThread = new RequestThread();
		requestThread.start();
		Beat beat = new Beat();

		mypDialog = new ProgressDialog(this);
		// 实例化
		mypDialog.setProgressStyle(ProgressDialog.STYLE_SPINNER);
		// 设置进度条风格，风格为圆形，旋转的
		mypDialog.setTitle("");
		// 设置ProgressDialog 标题
		mypDialog.setMessage(getResources().getString(R.string.second));
		// 设置ProgressDialog 提示信息
		mypDialog.setIcon(R.drawable.ic_launcher);
		// 设置ProgressDialog 标题图标
		// mypDialog.setButton("Google",this);
		// 设置ProgressDialog 的一个Button
		mypDialog.setIndeterminate(false);
		// 设置ProgressDialog 的进度条是否不明确
		mypDialog.setCancelable(true);
		// 设置ProgressDialog 是否可以按退回按键取消
		mypDialog.show();
		// 让ProgressDialog显示
	}

	protected void onPause() {
		super.onPause();
		requestThread.sending_enable = false;
		Log.i("PI", "Be paused");
	}
	
	
	protected void onResume() {
		super.onResume();
		requestThread.sending_enable = true;
		Log.i("PI", "Be resumed");
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
 
	public void OffLed(View view) {	
		mypDialog.show();
		offButton.clicked("set/low");
		Log.i("EVENT", "Offled clicked");
	}

	public void OnLed(View view) {	
		mypDialog.show();
		onButton.clicked("set/high");
		Log.i("EVENT", "Onled clicked");
	}

	class Button {
		protected android.widget.Button button_view = null;
		public Button(android.widget.Button button) {
			button_view = button;
		}
		public void clicked(String value) {
			Message msg = mRequestHandler.obtainMessage();
			msg.obj = value;
			mRequestHandler.sendMessage(msg);
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
		private boolean sending_enable = true;
		public void run() {
			this.setName("child");
			Looper.prepare();
			mRequestHandler = new Handler() {
				public void handleMessage(Message msg) {
					if (sending_enable) {
						String value = (String) msg.obj;
						httpget = new HttpGet(requestIp + value);
						try {
							/*
							 * HttpParams httpParameters = new
							 * BasicHttpParams(); int timeoutConnection = 3000;
							 * HttpConnectionParams.setConnectionTimeout
							 * (httpParameters, timeoutConnection);
							 * 
							 * int timeoutSocket = 5000;
							 * HttpConnectionParams.setSoTimeout(httpParameters,
							 * timeoutSocket);
							 * 
							 * DefaultHttpClient httpClient = new
							 * DefaultHttpClient(httpParameters);
							 */
							response = httpclient.execute(httpget);
							Log.i("REQUEST", requestIp + value);
						} catch (ClientProtocolException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (ConnectTimeoutException e1) {
							Log.i("Exception", "ConnectTimeoutException");
						} catch (SocketTimeoutException e1) {
							Log.i("Exception", "SocketTimeoutException");
						} catch (IOException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}

						HttpEntity entity = response.getEntity();
						if (entity != null) {
							long len = entity.getContentLength();
							{
								try {
									String contents = EntityUtils
											.toString(entity);
									Message toMain = mMainHandler
											.obtainMessage();
									toMain.obj = contents;
									mMainHandler.sendMessage(toMain);

								} catch (ParseException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								} catch (org.apache.http.ParseException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								} catch (ConnectTimeoutException e1) {
									Log.i("Exception",
											"ConnectTimeoutException");
								} catch (SocketTimeoutException e1) {
									Log.i("Exception", "SocketTimeoutException");
								} catch (IOException e) {
									// TODO Auto-generated catch block
									e.printStackTrace();
								}
							}
						}
					}
				}

			};
			Looper.loop();
		}
	}
	
	class Beat {
		public  Beat() {
			Timer timer = new Timer();  
			timer.scheduleAtFixedRate(new TimerTask(){  
			   public void run()  
			   {  
				   Message msg = mRequestHandler.obtainMessage();
				   msg.obj = "get/";
				   mRequestHandler.sendMessage(msg);
			   }  
			},  new Date(), 3000);
		}
	}

}
