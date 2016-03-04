/*
 *author: hdz
 *date: 2013.5.8
 *
 */

#ifndef _H_HASH
#define _H_HASH

#define FACTOR 1.425

#define OPTIMIZE_ON 1
#define OPTIMIZE_OFF 0

typedef enum LSH_TYPE {E2LSH, HAMMING} LSH_TYPE;


typedef struct LshConfig 
{ 
	float r;
	float w;
	int k;
	int l;
	int size;
	int dimension;
	int offset;
	int max_steps;
	float p;
	LSH_TYPE lsh_type;
	int optimize_kickout;

} LshConfig ;

typedef struct HashFamily
{
	float **a;
	float *b;
	unsigned int *c;

} HashFamily;

typedef struct LshParam {
		
	LshConfig *config;	
	HashFamily *hash_family;
	double *buf; 
	
} LshParam;

typedef struct UniformHashFunction
{
	unsigned int *u;	

} UniformHashFunction;

extern LshParam *global_lsh_param;

LshParam *initLshParam(const char *config_file);

int loadConfigFile(const char* filename, LshConfig *conf);

int initHashFamily(LshConfig *conf, HashFamily *hash_family, UniformHashFunction *uhf,  int num);

int initUniformHashFunction(UniformHashFunction *uhf, LshConfig *conf);

void freeHashFamily(HashFamily *hash_family, int num);

float getUniformRandom(float range_start, float range_end);

float getGaussianRandom();

unsigned int getRandomUns32(unsigned int range_start, unsigned int range_end);

unsigned long computeLsh(void *data, void *other);

void freeHashFamily(HashFamily *hash_family, int num);

void freeLshParam(LshParam *lsh_param);


#endif


