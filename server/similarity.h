/*
 * the similarity function
 * author: zhenhua
 * date: 2015.1
*/


#ifndef _SIMI_H
#define _SIMI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nest.h"
#include "net_headers.h"

#define NAME_LENGTH 30
#define TOPK_SIMILARITY_IMAGE 100

#define SIMILARITY_MAX_NUM 99999999
#define SQ_DIST_RATIO_THR  0.64 

#define KEYPOINT_DISTANCE_THRES 30000

#define NEAR_HAMMING_DIFFERT_THRES 1
#define NEAR_HAMMING_DISTANCE_THRES 7
#define NEAR_HAMMING_MEDIAN 85

typedef struct ImageSimilarity{
	char image_name[NAME_LENGTH];
	float image_dis;
}ImageSimilarity;

typedef struct ImageGroups{
	int size;
	int count;
	ImageSimilarity *simi;
}ImageGroups;

int imageComp(const void *a, const void *b);

int calResultScope(ImageGroups **groups, NNResult *res, float *cur_query_keypoint, int dimension);

inline int comuputeNearHammingDistance(float *point1, float *point2, int dimension);

inline float computeDistance(float *point1, float *point2, int dimension);

void copyPoint(float *dst, float *src, int dimension);

int calKeypointSimilarity(ImageGroups **groups, int dimension, float **query_keypoints, int query_keypoints_count);

ImageGroups *groupsCreate(void *para);

#endif






