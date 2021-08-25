#ifndef ARRAY_SUM_H
#define ARRAY_SUM_H

#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN_INDEX 1
#define NTHREADS_INDEX 2

typedef struct sum_args {
	int id;
	int range;
	int *arr;
	long res;
} sum_args;

void *sum_range_t(void *args);

int chunk_range(int tid, int size, int total_threads, int total_len);
#endif
