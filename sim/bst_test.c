#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    BST bst;
    bst_init(&bst);
    bst_insert(&bst, 12.0);
    bst_insert(&bst, 10.0);
    bst_insert(&bst, 15.0);
    float *arr = bst_to_arr(&bst);

    printf("bst.size = %d\n", bst.size);
    for (int i = 0; i < bst.size; i++)
        printf("%.2f ", arr[i]);
    printf("\n");

    free(arr);

    return 0;
}