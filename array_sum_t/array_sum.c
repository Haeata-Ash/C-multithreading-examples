#include "array_sum.h"



int main(int argc, char **argv) {
	//get length of array and number of threads
	if (argc != 3) {
		return EXIT_FAILURE;
	}


	int arr_len = atoi(argv[ARR_LEN_INDEX]);
	int nthreads = atoi(argv[NTHREADS_INDEX]);
	
	//give array initial values
	int *array = malloc(sizeof(int) * arr_len);
	for (int i = 0; i < arr_len; i++) {
		array[i] = i;
	}
	int test_sum = 0;
	for (int i = 0; i < arr_len; i++) {
		test_sum += array[i];
	}
	printf("The correct sum is %d\n", test_sum);
	
	//create threads array
	pthread_t *threads = malloc(sizeof(pthread_t) * nthreads);
	sum_args *args = malloc(sizeof(sum_args) * nthreads);
	
	int chunk_size = arr_len / nthreads;
	for (int i = 0; i < nthreads; i++) {
		args[i].id = i;
		args[i].range = chunk_range(i, chunk_size, nthreads, arr_len);
		args[i].arr = array + (i * chunk_size);
		args[i].res = 0;

		pthread_create(&threads[i], NULL, &sum_range_t, &args[i]);
	}
	int total_sum = 0;
	for (int i = 0; i < nthreads; i++) {
		pthread_join(threads[i], NULL);
		total_sum += args[i].res;
	}

	free(array);
	free(threads);
	free(args);
	
	printf("The total sum was %d\n", total_sum);
	return EXIT_SUCCESS;
}

void *sum_range_t(void *args) {
	sum_args *s = (sum_args *) args;
	for (int i = 0; i < s->range; i++) {
		s->res += s->arr[i];
	}
}

int chunk_range(int tid, int size, int nthreads, int total_len) {
	int start = tid * size;
	if (tid == nthreads - 1) {
		return total_len - (nthreads - 1) * size;
	} else {
		return size;
	}
}
