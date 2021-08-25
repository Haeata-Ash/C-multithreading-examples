CC=gcc
CFLAGS=-O0 -Werror=vla -std=gnu11 -g -fsanitize=address -pthread -lrt -lm 

CODE=dining_philo.c
HEADERS=dining_philo.h


correctness: $(CODE) $(HEADERS)
	$(CC) $(CFLAGS) $(CODE) -o philo

clean:
	rm -f philo
