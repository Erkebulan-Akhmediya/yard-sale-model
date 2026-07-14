#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "csv.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int iteration = 0;

typedef struct {
    float removed[2];
    float added[2];
} ExchangeResult;

void print_arr(float *arr, int size) {
    printf("[");
    for (int i = 2; i < size; i++) {
        printf("%.2f", arr[i]);
        if (i < size-1)
            printf(", ");
    }
    printf("]\n");
}

void random_pair(int *i, int *j, int max) {
    *i = rand() % max;
    *j = rand() % max;
    if (*i == *j)
        random_pair(i, j, max);
}

bool coin_flip() {
    return rand() % 2 == 1;
}

void log_err(ExchangeResult res, float *log_arr, int log_arr_size) {
    fprintf(
        stderr, 
        "values to be removed: [%.2f, %.2f], values to be added: [%.2f, %.2f]\n", 
        res.removed[0], 
        res.removed[1], 
        res.added[0], 
        res.added[1]
    );
    if (log_arr != NULL) {
        printf("BST before operation: ");
        print_arr(log_arr, log_arr_size);
        free(log_arr);
    }
}

int exchange(float *arr, BST *bst) {
    int i, j;
    random_pair(&i, &j, bst->size);
    float amount = MIN(arr[i], arr[j]) * 0.1;
    ExchangeResult res;
    res.removed[0] = arr[i];
    res.removed[1] = arr[j];
    if (coin_flip()) {
        arr[i] += amount;
        arr[j] -= amount;
    } else {
        arr[j] += amount;
        arr[i] -= amount;
    }
    res.added[0] = arr[i];
    res.added[1] = arr[j];
    
    if (!csv)
        return 0;

    bst_delete(bst, res.removed[0]);
    bst_delete(bst, res.removed[1]);

    bst_insert(bst, res.added[0]);
    bst_insert(bst, res.added[1]);

    iteration++;
    return 0;
}