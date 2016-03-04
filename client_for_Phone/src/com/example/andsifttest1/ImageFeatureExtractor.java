package com.example.andsifttest1;



import java.util.List;

import android.graphics.Bitmap;

public interface ImageFeatureExtractor {
    public List<ImageFeature> getFeatures(Bitmap img);
}

