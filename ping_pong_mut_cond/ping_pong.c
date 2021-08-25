//
// Question 4 - Race conditions and condition variables
//

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define EXCHANGES 20

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t alice_box;
static pthread_cond_t bob_box;

// uses semaphores so we don't lose signals

void* alice(void* arg) {

	for (size_t i = 0; i < EXCHANGES; ++i) {
		puts("Alice: Waiting for Bob to signal");

		// Wait for mail
		pthread_cond_wait(&alice_box, &mutex);


		puts("Alice: Got Bob's signal");
		printf("Alice: Got mail (%d) from Bob\n", i);

		// Send mail to Bob
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&bob_box);

	}

	return NULL;
}

void* bob(void* arg) {

	for (size_t i = 0; i < EXCHANGES; ++i) {
		puts("Bob: Waiting for Alice to signal");

		// Wait for mail
		pthread_cond_wait(&bob_box, &mutex);

		puts("Bob: Got Alice's signal");
		printf("Bob: Got mail (%d) from Alice\n", i);

		// Send mail to Alice
		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&alice_box);

	}

	return NULL;
}

int main(void) {

	pthread_cond_init(&alice_box, NULL);
	pthread_cond_init(&bob_box, NULL);

	pthread_t alice_tid;
	pthread_t bob_tid;

	pthread_create(&alice_tid, NULL, alice, NULL);
	pthread_create(&bob_tid, NULL, bob, NULL);

	//start the chain
	pthread_cond_signal(&alice_box);

	pthread_join(alice_tid, NULL);
	pthread_join(bob_tid, NULL);

	pthread_cond_destroy(&alice_box);
	pthread_cond_destroy(&bob_box);

	return 0;
}
