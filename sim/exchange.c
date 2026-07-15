#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "csv.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    float removed[2];
    float added[2];
} ExchangeResult;

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

    bst_delete(bst, res.removed[0]);
    bst_delete(bst, res.removed[1]);

    if (bst_insert(bst, res.added[0]) == -1)
        return -1;
    if (bst_insert(bst, res.added[1]) == -1)
        return -1;

    return 0;
}