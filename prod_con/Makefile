CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm 

CODE=prod_cons.c
HEADERS=prod_cons.h


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o prod_con 

clean:
	rm -f prod_con
