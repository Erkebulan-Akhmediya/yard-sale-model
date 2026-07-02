#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void print_arr(float *arr, int size) {
    printf("bst.size = %d\n", size);
    printf("[");
    for (int i = 0; i < size; i++)
        printf("%.2f ", arr[i]);
    printf("]");
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
    printf("delete root test\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 67.0); // root
    delete_and_print_arr(&bst, 67.0); // delete root

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_leaf() {
    printf("delete left test\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 67.0); // root
    insert_and_print_arr(&bst, 69.0); // root->right
    delete_and_print_arr(&bst, 69.0); // delete root->right

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_both_children() {
    printf("delete node with both children\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 42.0); // root
    insert_and_print_arr(&bst, 67.0); // root->right
    insert_and_print_arr(&bst, 52.0); // root->right->left
    insert_and_print_arr(&bst, 69.0); // root->right->right
    delete_and_print_arr(&bst, 67.0); // delete root->right

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_right_child() {
    printf("delete node with right child\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 52.0); // root
    insert_and_print_arr(&bst, 67.0); // root->right
    insert_and_print_arr(&bst, 69.0); // root->right->right
    delete_and_print_arr(&bst, 67.0); // delete root->right

    bst_free(&bst);
    printf("---------------------\n");
}

void delete_node_with_left_child() {
    printf("delete node with left child\n");
    BST bst;
    bst_init(&bst);

    insert_and_print_arr(&bst, 52.0); // root
    insert_and_print_arr(&bst, 67.0); // root->right
    insert_and_print_arr(&bst, 61.0); // root->right->left
    delete_and_print_arr(&bst, 67.0); // delete root->right

    bst_free(&bst);
    printf("---------------------\n");
}

int main() {
    delete_root();
    delete_leaf();
    delete_node_with_both_children();
    delete_node_with_right_child();
    delete_node_with_left_child();
    return 0;
}