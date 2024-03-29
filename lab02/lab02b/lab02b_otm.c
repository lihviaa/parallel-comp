#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "arraylib.h"

int *array;
int *result;
int **matrix;
int lines, columns;
long num_of_threads;
long seg_per_thread;

void *otm_mat_array(void* thread);

int main(int argc, char *argv[]) {
    long thrd_n;

    if(argc != 4) {
        fprintf(stderr, "Usage: <program> <lines> <columns> <num_of_threads>\n");
        return 1;
    }

    lines = atoi(argv[1]);
    columns = atoi(argv[2]);
    num_of_threads = strtol(argv[3], NULL, 10);

    array = rnd_array_alloc(columns, 100);
    matrix = rnd_matrix_alloc(lines, columns, 100);
    result = (int*) malloc(lines * sizeof(int));

    seg_per_thread = lines/num_of_threads;

    pthread_t *threads = malloc(num_of_threads * sizeof(pthread_t));

    for(thrd_n = 0; thrd_n < num_of_threads; thrd_n++) {
        pthread_create(&threads[thrd_n], NULL, otm_mat_array, (void*) thrd_n);
    }

    for(thrd_n = 0; thrd_n < num_of_threads; thrd_n++) {
        pthread_join(threads[thrd_n], NULL);
    }

    printf("\nParallel execution finished.\n");

    for(int m = 0; m < lines; m++) free(matrix[m]);
    free(matrix);
    free(array);
    free(result);
    free(threads);

    return 0;
}

void *otm_mat_array(void* thread) {
    long thread_id = pthread_self();
    long thrd = (long) thread;
    long offset = thrd * seg_per_thread;

    for(int i = 0; i < seg_per_thread; i++) {
        result[offset + i] = 0;
        for(int j = 0; j < columns; j++) {
            result[offset + i] += matrix[offset + i][j] * array[j];
        }

	printf("Parallel: Result[%ld] calculated by Thread %ld\n", offset + i, thread_id);
    }

    return NULL;
}
