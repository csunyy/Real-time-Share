package com.example.andsifttest1;

import java.io.Serializable;

public class ImageFeature implements Comparable<ImageFeature>, Serializable{

	private static final long serialVersionUID = -6498123789358412224L;
	private float[] descriptor;
    private float orientation;
    private float scale;

    
    public ImageFeature()
    {
        
    }
    
    public ImageFeature(double[] desc)
    {
        descriptor=new float[desc.length];
        for (int i=0;i<desc.length;i++)
        {
            descriptor[i]=(float)desc[i];
        }
    }
    
    
    public ImageFeature(float[] desc)
    {
        descriptor=desc;
    }
    public float[] getDescriptor() {
        return descriptor;
    }

    public void setDescriptor(float[] descriptor) {
        this.descriptor = descriptor;
    }

    public float getOrientation() {
        return orientation;
    }

    public void setOrientation(float orientation) {
        this.orientation = orientation;
    }

    public float getScale() {
        return scale;
    }

    public void setScale(float scale) {
        this.scale = scale;
    }

    
    public double distance(ImageFeature img)
    {
        float diff=0;
        double dsq = 0;
	float[] descr1=this.descriptor;
        float[] descr2=img.descriptor;
        
	int  d=this.descriptor.length;
        
	for(int i = 0; i < d; i++ )
	{
		diff = descr1[i] - descr2[i];
		dsq += diff*diff;
	}
	return dsq;
    }

    public int compareTo(ImageFeature o) {
        return scale < o.scale ? 1 : scale == o.scale ? 0 : -1;
    }  
}
