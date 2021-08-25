CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm 

CODE=matrix_multi.c
HEADERS=


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o mm

clean:
	rm -f mm
