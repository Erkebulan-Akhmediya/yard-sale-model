#include "bst.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void bst_init(BST *bst) {
    bst->root = NULL;
    bst->size = 0;
}

struct BSTNode *_new_bst_node(float val) {
    struct BSTNode *node = malloc(sizeof(struct BSTNode));
    if (node == NULL)
        return NULL;
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct BSTNode *_bst_insert(struct BSTNode *node, float val) {
    if (node == NULL)
        return _new_bst_node(val);

    if (val > node->val) {
        node->right = _bst_insert(node->right, val);
    } else {
        node->left = _bst_insert(node->left, val);
    }
    return node;
}

void bst_insert(BST *bst, float val) {
    bst->root = _bst_insert(bst->root, val);
    bst->size++;
}

int bst_init_with_arr(BST *bst, float *arr, int arr_size) {
    bst_init(bst);
    for (int i = 0; i < arr_size; i++)
        bst_insert(bst, arr[i]);
    return 0;
}

int _bst_delete(struct BSTNode *node, float val) {
    if (node == NULL)
        return -1;

    struct BSTNode **node_to_delete;
    float val_to_delete;
    if (node->val == val) {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return 1;
        }

        node_to_delete = node->right != NULL ? &(node->right) : &(node->left);
        val_to_delete = (*node_to_delete)->val;
    } else {
        node_to_delete = node->val > val ? &(node->right) : &(node->left);
        val_to_delete = val;
    }

    int res = _bst_delete(*node_to_delete, val_to_delete);
    if (res == 1) {
        *node_to_delete = NULL;
        return 0;
    }
    return res;
}

int bst_delete(BST *bst, float val) {
    if (bst->root == NULL)
        return -1;
    
    int res = _bst_delete(bst->root, val);
    if (res == -1)
        return -1;
    if (res == 1)
        bst->root = NULL;
    bst->size--;
    return 0;
}

void _bst_to_arr(Stack *stack, struct BSTNode *node) {
    if (node->left != NULL)
        _bst_to_arr(stack, node->left);
    
    stack_push(stack, node->val);

    if (node->right != NULL)
        _bst_to_arr(stack, node->right);
}

float *bst_to_arr(BST *bst) {
    if (bst->root == NULL)
        return NULL;

    Stack stack;
    if (stack_init(&stack, bst->size) == -1)
        return NULL;

    _bst_to_arr(&stack, bst->root);
    return stack.arr;
}

int bst_print_arr(BST *bst) {
    float *arr = bst_to_arr(bst);
    if (arr == NULL)
        return -1;

    printf("BST: [");
    for (int i = 0; i < bst->size; i++) {
        printf("%.2f", arr[i]);
        if (i < bst->size-1)
            printf(", ");
    }
    printf("]\n");
    free(arr);
    return 0;
}

void _bst_free(struct BSTNode *node) {
    if (node == NULL)
        return;

    _bst_free(node->left);
    _bst_free(node->right);
    free(node);
}

void bst_free(BST *bst) {
    _bst_free(bst->root);
    bst->root = NULL;
    bst->size = 0;
}
