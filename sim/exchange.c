#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "csv.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

    float *pre_arr = bst_to_arr(bst);
    if (bst_delete(bst, res.removed[0]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        if (pre_arr != NULL) {
            printf("BST before exchange: ");
            print_arr(pre_arr, bst->size);
            free(pre_arr);
        }
        return -1;
    }
    if (bst_delete(bst, res.removed[1]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        if (pre_arr != NULL) {
            printf("BST before exchange: ");
            print_arr(pre_arr, bst->size);
            free(pre_arr);
        }
        return -1;
    }
    if (bst_insert(bst, res.added[0]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        if (pre_arr != NULL) {
            printf("BST before exchange: ");
            print_arr(pre_arr, bst->size);
            free(pre_arr);
        }
        return -1;
    }
    if (bst_insert(bst, res.added[1]) == -1) {
        fprintf(stderr, "failed to delete %.2f from the BST\n", res.removed[0]);
        fprintf(
            stderr, 
            "exchange result: removed: [%.2f, %.2f], added: [%.2f, %.2f]\n", 
            res.removed[0], 
            res.removed[1], 
            res.added[0], 
            res.added[1]
        );
        if (pre_arr != NULL) {
            printf("BST before exchange: ");
            print_arr(pre_arr, bst->size);
            free(pre_arr);
        }
        return -1;
    }

    return 0;
}