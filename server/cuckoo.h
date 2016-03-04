/*
 * cuckoo hasing
 * author: hdzhang
 * date: 2013.11.20
*/

#ifndef _CUCKOO_H_
#define _CUCKOO_H_

typedef unsigned long (*hashfunc_t)(void *data, void *other); 

#define USED 1
#define FREE 0

#define BUFSIZE 1024

typedef struct Item {

	void *data;
	char flag;
	void *info;
	int access_count;

} Item;

typedef struct HashTable {
	
	Item *items;
	unsigned long  size;
	unsigned long  used;
	float load;
	void (*free_data)(void *ptr);
	void (*free_info)(void *ptr);

} HashTable;

typedef struct HashValue {

	unsigned long hv;
	int func_index;
	int table_index;
	int access_count;

} HashValue;

typedef struct CuckooHash CuckooHash;

typedef int (*findOptPos_t)(CuckooHash *cuckoo_hash, HashValue *hash_value, void *data);

typedef struct CuckooHash {
	
	HashTable **hash_tables;	
	int table_num;	
	hashfunc_t *functions;
	int func_num;
	int max_steps;
	HashValue *hv_arr;
	int opt_pos;
	findOptPos_t  find_opt_pos;
	long long kickout_counter;

} CuckooHash;



/* functions defined as macros */
#define TableSetFreeDataMethod(table, m)  ((table)->free_data = (m))
#define TableSetFreeInfoMethod(table, m)  ((table)->free_data = (m))
#define CuckooSetFindPosMethod(cuckoo, m) ((cuckoo)->find_opt_pos = (m))

/* functions  prototypes */

HashTable *tableCreate(unsigned long size);

void tableRelease(HashTable *table);

HashTable *tableInsert(HashTable *table, unsigned long hv, void *data, void *info);

void tableRemove(HashTable *table, unsigned long hv);

void *tableGetItemData(HashTable *table, unsigned long hv);

void *tableGetItemInfo(HashTable *table, unsigned long hv);

void tableKickOut(HashTable *table, unsigned long hv, void *data, void *info, void **old_data, void **old_info);

CuckooHash *cuckooInit(HashTable **hash_tables, int table_num, hashfunc_t *funcs, int func_num, int max_steps, int opt_pos);

void cuckooDestroy(CuckooHash *cuckoo_hash);

CuckooHash *cuckooInsertItem(CuckooHash *cuckoo_hash, void *data, void *info);

CuckooHash *cuckooInsertFile(CuckooHash *cuckoo_hash, const char * filename);

int cuckooFindPos(CuckooHash *cuckoo_hash, HashValue *hash_value, void *data);

void cuckooReport(CuckooHash *cuckoo_hash);

#define _EVALUATION_

#ifdef _EVALUATION_

double insert_items_time;
double insert_item_time;
double insert_file_time;

#endif


#endif

