#include "prod_cons.h"


void cbuf_init(cbuf_t *cbuf, int size) {
	if (cbuf == NULL)
	cbuf->buf = malloc(size * sizeof(void *));
	cbuf->n = size;
	cbuf->front = 0;
	cbuf->end = 0;
	sem_init(&cbuf->buf_bsem, 0, 1);
	sem_init(&cbuf->free_slots, 0, size);
	sem_init(&cbuf->num_items, 0, 0);
	return;
}

void cbuf_destroy(cbuf_t *cbuf) {
	if (cbuf == NULL) {
		return;
	}
	free(cbuf->buf);
	return;
}

void cbuf_insert_end(cbuf_t *cbuf, void *data) {
	if (cbuf == NULL) {
		return;
	}
	sem_wait(&cbuf->free_slots);
	sem_wait(&cbuf->buf_bsem);
	cbuf->end = ((cbuf->end + 1) % cbuf->n);
	cbuf->buf[cbuf->end] = data;
	sem_post(&cbuf->num_items);
	sem_post(&cbuf->buf_bsem);
}

void *cbuf_consume(cbuf_t *cbuf) {
	if (cbuf == NULL) {
		return NULL;
	}

	sem_wait(&cbuf->num_items);
	sem_wait(&cbuf->buf_bsem);
	void *res = cbuf->buf[cbuf->front];
	cbuf->front = (cbuf->front + 1) % cbuf->n;
	sem_post(&cbuf->free_slots);
	sem_post(&cbuf->buf_bsem);
	return res;
}
