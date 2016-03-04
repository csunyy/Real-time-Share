package com.example.clientdesign;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;


import android.widget.Button;

public class MainActivity extends Activity {
	public static final String SEARCH_ACTION = "com.example.clientdesign.SEARCH_ACTION";
	public static final String UPLOAD_ACTION = "com.example.clientdesign.UPLOAD_ACTION";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.activity_main);
		Button searchButton = (Button)findViewById(R.id.button1);
		Button uploadButton = (Button)findViewById(R.id.button2);
		
		searchButton.setOnClickListener(new OnClickListener(){
			public void onClick(View v){
				Intent intent = new Intent();
				intent.setAction(SEARCH_ACTION);
				startActivity(intent);
				
			}
		});
		uploadButton.setOnClickListener(new OnClickListener(){
			public void onClick(View v){
				Intent intent = new Intent();
				finish();
				intent.setAction(UPLOAD_ACTION);
				startActivity(intent);
				
			}
		});
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	 public boolean onKeyDown(int keyCode, KeyEvent event)  
	    {  
	        if (keyCode == KeyEvent.KEYCODE_BACK )  
	        {   
	            AlertDialog isExit = new AlertDialog.Builder(this).create();    
	            isExit.setTitle("System Prompt");  
	            isExit.setMessage("Exit Confirmation");   
	            isExit.setButton("Confirm", listener);  
	            isExit.setButton2("Concel", listener);   
	            isExit.show();  
	        }  
	        return false;     
	    }  
	    DialogInterface.OnClickListener listener = new DialogInterface.OnClickListener()  
	    {  
	        public void onClick(DialogInterface dialog, int which)  
	        {  
	            switch (which)  
	            {  
	            case AlertDialog.BUTTON_POSITIVE: 
	                finish();  
	                android.os.Process.killProcess(android.os.Process.myPid());
	                break;  
	            case AlertDialog.BUTTON_NEGATIVE:  
	                break;  
	            default:  
	                break;  
	            }  
	        }  
	    };    

}
