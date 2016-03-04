/*
 * reponse functions for the server 
 * author: zhenhua
 * date: 2015.1
*/


#ifndef NET_UTILITY_PHONE_H_
#define NET_UTILITY_PHONE_H_

#include "nest.h"
#include "similarity.h"
#include "net_wrap.h"
#include "net_headers.h"

char *revstr(char *str, size_t len);

int getImagenameWithoutPath(char *old_name, char *new_name);

int getFileSize(char *fileName);

int sendImageToNet(int conn_fd, char *image_name, int image_size);

int reponseWithDevice(Nest *nest, int dimension, int sock_fd, int dev_tag);

bool judgeImageUploadOrNot(int battery, ImageGroups *iGroups, int query_keypoints_count);

int responseDeviceForUpload(Nest *nest, int dimension, int sock_fd, int dev_tag, int task_tag);

int writeMessageForUpload(int sock_fd, int dev_tag, int task_tag, int uploadCount, int *imageName);

int recvImageFromDeviceForUpload(int sock_fd, int dev_tag, int task_tag);

int writeImageToFile(int sock_fd, char *image_name, int image_size, int dev_tag, int task_tag);

int responseDeviceForQuery(Nest *nest, int dimension, int sock_fd, int dev_tag, int task_tag);

int writeMessageForQuery(int sock_fd, int dev_tag, int task_tag, int battery, ImageGroups *iGroups);

#endif
