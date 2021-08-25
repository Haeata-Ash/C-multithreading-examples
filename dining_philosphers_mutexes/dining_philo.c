#include "dining_philo.h"


struct args {
	pthread_mutex_t *chopsticks;
	int id;
};

void *dine (void *args) {
	struct args *a = (struct args *) args;
	
	if (a->id == NUM_PHILO - 1) {
		pthread_mutex_lock(a->chopsticks);
		pthread_mutex_lock(a->chopsticks + a->id);

	} else {
		pthread_mutex_lock(a->chopsticks + a->id);
		pthread_mutex_lock(a->chopsticks + a->id + 1);
	}
	printf("Philo %d is eating\n", a->id);
	
	if (a->id == NUM_PHILO - 1) {
		pthread_mutex_unlock(a->chopsticks);
		pthread_mutex_unlock(a->chopsticks + a->id);
	} else {
		pthread_mutex_unlock(a->chopsticks + a->id);
		pthread_mutex_unlock(a->chopsticks + a->id + 1);
	}
	
	
}

int main(void) {
	struct args a[NUM_PHILO];
	pthread_t philos[NUM_PHILO];

	pthread_mutex_t chopsticks[NUM_CHOP];


	// create mutexes
	for (int i = 0; i < NUM_CHOP; i++) {
		pthread_mutex_init(chopsticks + i, NULL);
	}

	// create threads
	for (int i = 0; i < NUM_PHILO; i++) {
		a[i].id = i;
		a[i].chopsticks = chopsticks;
		pthread_create(philos + i, NULL, dine, a + i);
	}

	// wait for threads to finish
	for (int i = 0; i < NUM_PHILO; i++) {
		pthread_join(philos[i], NULL);
	}

	// destory mutexes
	for (int i = 0; i < NUM_PHILO; i++) {
		pthread_mutex_destroy(chopsticks + i);
	}

	return 0;
}
