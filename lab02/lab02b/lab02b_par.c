#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "arraylib.h"

int *array;
int *result;
int **matrix;
int lines, columns;

void *par_mat_array(void* thread);

int main(int argc, char *argv[]) {
    long thrd_n;

    if(argc != 3) {
        fprintf(stderr, "Usage: <program> <lines> <columns>\n");
        return 1;
    }

    lines = atoi(argv[1]);
    columns = atoi(argv[2]);

    array = rnd_array_alloc(columns, 100);
    matrix = rnd_matrix_alloc(lines, columns, 100);
    result = (int*) malloc(lines * sizeof(int));

    pthread_t *threads = malloc(lines * sizeof(pthread_t));

    for(thrd_n = 0; thrd_n < lines; thrd_n++) {
        pthread_create(&threads[thrd_n], NULL, par_mat_array, (void*) thrd_n);
    }

    for(thrd_n = 0; thrd_n < lines; thrd_n++) {
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

void *par_mat_array(void* thread) {
    long thread_id = pthread_self();
    long thrd = (long) thread;
    result[thrd] = 0;

    for(int i = 0; i < columns; i++) {
        result[thrd] += matrix[thrd][i] * array[i];
    }

    printf("Parallel: Result[%ld] calculated by Thread %ld\n", thrd, thread_id);
    return NULL;
}

