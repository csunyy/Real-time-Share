 package com.example.socket;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.FilterInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Arrays;
import java.util.Date;
import java.util.Scanner;

import com.example.battery.GetBatteryLevel;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Environment;
import android.os.Handler;
import android.util.Log;
import android.widget.Button;
import android.widget.ImageView;



public class ReceiveFive{
   private static final String HOST = "115.156.209.214";

    private static final int PORT = 31120;
    private Socket socket = null;
    private Handler mHandler = null;
    private boolean stop = true;
    private File fr = null;
    private String uploadFile1="/sdcard/1.jpg";
    private String uploadFile2="/sdcard/2.jpg"; 
    private String uploadFile3="/sdcard/3.jpg"; 
    private String uploadFile4="/sdcard/4.jpg"; 
    private String uploadFile5="/sdcard/5.jpg"; 
    private DataOutputStream dos = null;
    private ImageView imageView = null;
    private DataInputStream dataInput = null;

	public String getSDPath(){ 
	       File sdDir = null; 
	       boolean sdCardExist = Environment.getExternalStorageState()   
	                           .equals(android.os.Environment.MEDIA_MOUNTED);  


	       if   (sdCardExist)    
	       {                               
	         sdDir = Environment.getExternalStorageDirectory();
	      }   
	       return sdDir.toString(); 
	       
	}
    public int receiveFivePhotos(int intBattery) {
    	String spfile = getSDPath() +"/" + "siftPoints.txt";
        fr = new File(spfile);
        for(int ii = 1; ii < 11; ii++){
        	File file = new File(getSDPath()+"/"+ii+".jpg");
      	  if (file.isFile() && file.exists()) {  
      	        file.delete();   
      	    }
        }
            	Runnable downloadRun = new Runnable(){   
			@Override  
				public void run() {   
					try {
						Log.v("123456", Integer.toString(123));
						socket = new Socket(HOST, PORT);
						Log.v("123456", Integer.toString(12322));
						dos = new DataOutputStream(socket.getOutputStream());
						dataInput = new DataInputStream(socket.getInputStream());

						 int dev_tag = 2;
						 int task_tag = 1;
		          		int imagecount = 1;

		          		 String filename = "query.jpg";
		          		 int sLength = filename.getBytes().length;
		          		 
		          		 dos.writeInt(uploadFeatures.BigtoLittle32(dev_tag));
		          		 dos.writeInt(uploadFeatures.BigtoLittle32(task_tag));

		          		 
		          		FileInputStream fisBattery = new FileInputStream(new File(getSDPath()+"/"+"battery.txt"));
		          		int battery = fisBattery.read();
		          		Log.v("battery", Integer.toString(battery));
		          		dos.writeInt(uploadFeatures.BigtoLittle32(battery));
		          		
		          		 dos.writeInt(uploadFeatures.BigtoLittle32(imagecount));
		          		 dos.writeInt(uploadFeatures.BigtoLittle32(sLength));
		          		 
		          		 dos.write(filename.getBytes());

		          		 FileInputStream fis = new FileInputStream(fr);
		          		 BufferedReader bf = new BufferedReader(new InputStreamReader(fis));
		          		 int keypointCount = Integer.parseInt(bf.readLine());
		          		Log.v("kpcount", Integer.toString(keypointCount));
		          		dos.writeInt(uploadFeatures.BigtoLittle32(keypointCount));
		          		 String keypoints = "";

		          		byte[] kpBuffer = new byte[1024];

		          		int j = 0;
		          		 while((keypoints = bf.readLine()) != null){
		          			for(j = 0; j < 1024; j++)
		          					kpBuffer[j] = '#';
		          			byte[] temp = keypoints.getBytes();
		          			for(j = 0; j < keypoints.getBytes().length; j++)
		          				kpBuffer[j] = temp[j]; 
		          			int offset = keypoints.getBytes().length;
		          			for(int i = offset; i < 1024; i++)
			          			kpBuffer[i] = '#';
		          			Log.v("kp",keypoints);
		          			dos.write(kpBuffer);
		          			
		          		 }
		          		 dos.flush();
		          		 fis.close();

		                  Log.v("dev", Integer.toString(uploadFeatures.BigtoLittle32(dataInput.readInt())));
		                  Log.v("task", Integer.toString(uploadFeatures.BigtoLittle32(dataInput.readInt())));
		                  
		                  int count = uploadFeatures.BigtoLittle32(dataInput.readInt());
		                  Log.v("count", Integer.toString(count));
		                  
		                  int len =0;
		                  byte[] nameBuffer = new byte[256];
					      for(int jj = 0; jj < count; jj++){
					        	 int kk = jj + 1;
						          	len = 0;
						          	
						          	while (len < 256) {  
				                   		 len += dataInput.read(nameBuffer, len, 256-len);  
				                   	 }
						          	Log.v("len",Integer.toString(len));
						          	String imageName = new String(nameBuffer);
						          	Log.v("imageName"+kk, imageName);
					        	 
						          	int picSize = dataInput.readInt();
					        	 java.io.FileOutputStream fos = new FileOutputStream(getSDPath()+"/"+kk+".jpg",false);
					        	 
					        	 
			                     Log.v("similarity"+kk, Integer.toString(dataInput.readInt()));
			                     byte[] picdata = new byte[picSize];
			                     int len1 = 0;  
		                    	 while (len1 < picSize) {  
		                    		 len1 += dataInput.read(picdata, len1, picSize - len1);  
		                    	 }
					             fos.write(picdata,0,picSize);  	             
					      }
			             dos.close();
			             dataInput.close();
	                     socket.close();
		          	 } catch (IOException e) {
		          		 e.printStackTrace();
		          	 }

				}
			  }; 
			  new Thread(downloadRun).start();  
			  return 1;
	    }
}
