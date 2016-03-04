/*
 *author: hdz
 *date: 
 *
 */

#ifndef _LSH_CUCKOO_H_
#define _LSH_CUCKOO_H_

#include "cuckoo.h"
#include "lsh.h"

typedef struct NNResult {
	int num;
	void **data;
	void **info;
} NNResult;

typedef CuckooHash Nest; 

long skip_counter;

#define NestGetDimension(nest) (global_lsh_param->config->dimension)

#define NestSetFindPosMethod(nest, m) ((nest)->find_opt_pos = (m))
#define NestSetHashMethods(nest, m) ((nest)->functions = (m))

int initNestParam(const char *config_file);

HashTable **hashTablesCreate(void (*free_data)(void *ptr), void (*free_info)(void *ptr));

Nest *nestCreate(HashTable **hash_tables);

Nest *nestInsertItem(Nest *nest, void *data, void *info);

Nest *nestRemoveItem(Nest *nest, void *data, int (*match)(void *data, void *ptr));

int nestInsertFile(Nest *nest, const char *file_name);

int nestFindOptPos(Nest *nest, HashValue *hash_value, void *data);

void nestReport(Nest *nest);

NNResult *nestGetNN(Nest *nest, void *data);

void *nestGetItem(Nest *nest, void *data, int (*match)(void *data, void *ptr));

void freeNestParam();

void nestDestroy(Nest *nest);

void freeNNResult(NNResult *res);

#endif
