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

void insert_and_print_arr(BST *bst, float val) {
    bst_insert(bst, val);
    float *arr = bst_to_arr(bst);
    print_arr(arr, bst->size);
    free(arr);
}

void delete_and_print_arr(BST *bst, float val) {
    bst_delete(bst, val);
    float *arr = bst_to_arr(bst);
    print_arr(arr, bst->size);
    free(arr);
}

void delete_root() {
    printf("---------------------\n");
    printf("delete root test\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 67.0);

    delete_and_print_arr(&bst, 67.0);

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_leaf() {
    printf("---------------------\n");
    printf("delete left test\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 67.0);

    insert_and_print_arr(&bst, 69.0);

    delete_and_print_arr(&bst, 69.0);

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_both_children() {
    printf("---------------------\n");
    printf("delete node with both children\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 42.0);
    insert_and_print_arr(&bst, 67.0);
    insert_and_print_arr(&bst, 52.0);
    insert_and_print_arr(&bst, 69.0);
    delete_and_print_arr(&bst, 67.0);

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_left_child() {
    printf("---------------------\n");
    printf("delete node with left child\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 52.0);
    insert_and_print_arr(&bst, 67.0);
    insert_and_print_arr(&bst, 69.0);
    delete_and_print_arr(&bst, 67.0);

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_right_child() {}

int main() {
    delete_root();
    delete_leaf();
    delete_node_with_both_children();
    delete_node_with_left_child();
    return 0;
}