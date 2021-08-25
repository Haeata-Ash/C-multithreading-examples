CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm 

CODE=ping_pong.c
HEADERS=


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o pp

clean:
	rm -f pp
