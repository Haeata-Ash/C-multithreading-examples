#include "dining_philo.h"


struct args {
	sem_t *table_sem;
	int id;
};

void *dine (void *args) {
	struct args *a = (struct args *) args;
	sem_wait(a->table_sem);
	printf("Philo %d is eating\n", a->id );
	sem_post(a->table_sem);
	printf("Philo %d is done eating\n", a->id);
}

int main(void) {
	struct args a[NUM_PHILO];
	pthread_t philos[NUM_PHILO];
	sem_t table_sem;



	// create semaphores
	sem_init(&table_sem, 0, NUM_CHOP/2);

	// create threads
	for (int i = 0; i < NUM_PHILO; i++) {
		a[i].id = i;
		a[i].table_sem = &table_sem;
		pthread_create(philos + i, NULL, dine, a + i);
	}

	// wait for threads to finish
	for (int i = 0; i < NUM_PHILO; i++) {
		pthread_join(philos[i], NULL);
	}

	// destory sem
	sem_destroy(&table_sem);
	return 0;
}
