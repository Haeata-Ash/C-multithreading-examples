CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm 

CODE=dancing.c
HEADERS=


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o dance

clean:
	rm -f dance
