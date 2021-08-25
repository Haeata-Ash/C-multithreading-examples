#ifndef PROD_CONS_H
#define PROD_CONS_H
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct cbuf_t {
	void **buf; // array of void pointers
	int n; //max slots
	int front;
	int end;
	sem_t buf_bsem;
	sem_t free_slots;
	sem_t num_items;
} cbuf_t;

void cbuf_init(cbuf_t *cbuf, int size);

void cbuf_destroy(cbuf_t *cbuf);

void cbuf_insert_end(cbuf_t *cbuf, void *data);

void *cbuf_consume(cbuf_t *cbuf);
#endif
