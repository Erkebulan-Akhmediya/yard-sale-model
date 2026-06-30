#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void print_arr(float *arr, int size) {
    printf("bst.size = %d\n", size);
    for (int i = 0; i < size; i++)
        printf("%.2f ", arr[i]);
    printf("\n");
    printf("\n");
}

int main() {
    BST bst;
    bst_init(&bst);

    bst_insert(&bst, 12.0);

    float *arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_insert(&bst, 10.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_insert(&bst, 67.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_insert(&bst, 15.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_delete(&bst, 67.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_delete(&bst, 10.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_insert(&bst, 12.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_insert(&bst, 13.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_delete(&bst, 15.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_delete(&bst, 12.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    bst_delete(&bst, 13.0);

    arr = bst_to_arr(&bst);
    print_arr(arr, bst.size);
    free(arr);

    return 0;
}