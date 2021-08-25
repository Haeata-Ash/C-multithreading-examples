CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm

CODE=array_sum.c
HEADERS=array_sum.h


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o msort

clean:
	rm -f msort
