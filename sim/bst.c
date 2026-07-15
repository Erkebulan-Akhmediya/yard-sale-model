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
        node->left = _bst_insert(node->left, val);
    } else {
        node->right = _bst_insert(node->right, val);
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

struct BSTNode *getSuccessor(struct BSTNode *node) {
    struct BSTNode *successor = node->right;
    while (successor != NULL && successor->left != NULL)
        successor = successor->left;
    return successor;
}

struct BSTNode *_bst_delete(struct BSTNode *node, float val) {
    if (node == NULL)
        return node;
    
    if (val > node->val) {
        node->left = _bst_delete(node->left, val);
        return node;
    }

    if (val < node->val) {
        node->right = _bst_delete(node->right, val);
        return node;
    }

    if (node->left == NULL) {
        struct BSTNode *tmp = node->right;
        free(node);
        return tmp;
    }
    
    if (node->right == NULL) {
        struct BSTNode *tmp = node->left;
        free(node);
        return tmp;
    }
    
    struct BSTNode *successor = getSuccessor(node);
    node->val = successor->val;
    node->right = _bst_delete(node->right, successor->val);
    return node;
}

void bst_delete(BST *bst, float val) {
    bst->root = _bst_delete(bst->root, val);
    bst->size--;
}

void _bst_to_arr(Stack *stack, struct BSTNode *node) {
    if (node == NULL)
        return;
    _bst_to_arr(stack, node->left);
    stack_push(stack, node->val);
    _bst_to_arr(stack, node->right);
}

void *bst_to_arr(BST *bst, float *buff) {
    if (bst->root == NULL)
        return NULL;

    Stack stack;
    stack_init(&stack, buff);

    _bst_to_arr(&stack, bst->root);
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
