#include "bst.h"
#include "stack.h"
#include <stdlib.h>

struct BSTNode {
    float val;
    struct BSTNode *left;
    struct BSTNode *right;
};

void bst_init(BST *bst) {
    bst->root = NULL;
    bst->size = 0;
}

int _bst_insert(struct BSTNode *node, float val) {
    if (val > node->val) {
        if (node->left != NULL)
            return _bst_insert(node->left, val);
        node->left = malloc(sizeof(struct BSTNode));
        if (node->left == NULL)
            return -1;
        node->left->val = val;
        node->left->left = NULL;
        node->left->right = NULL;
    } else {
        if (node->right != NULL)
            return _bst_insert(node->right, val);
        node->right = malloc(sizeof(struct BSTNode));
        if (node->right == NULL)
            return -1;
        node->right->val = val;
        node->right->left = NULL;
        node->right->right = NULL;
    }
    return 0;
}

int bst_insert(BST *bst, float val) {
    if (bst->root == NULL) {
        bst->root = malloc(sizeof(struct BSTNode));
        if (bst->root == NULL)
            return -1;
        bst->root->val = val;
        bst->root->left = NULL;
        bst->root->right = NULL;
        bst->size++;
        return 0;
    }
    if (_bst_insert(bst->root, val) == -1)
        return -1;
    bst->size++;
    return 0;
}

int _bst_delete(struct BSTNode *node, float val) {
    if (node == NULL)
        return -1;

    if (node->val == val) {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            node = NULL;
            return 1;
        }

        struct BSTNode *node_to_delete;
        float val_to_delete;

        if (node->right != NULL) {
            node->val = node->right->val;
            int res = _bst_delete(node->right, node->right->val);
            if (res == 1) {
                node->right = NULL;
                return 0;
            }
            return res;
        }
        if (node->left != NULL) {
            node->val = node->left->val;
            int res = _bst_delete(node->left, node->left->val);
            if (res == 1) {
                node->left = NULL;
                return 0;
            }
            return res;
        }

        int res = _bst_delete(node_to_delete, val_to_delete);
        if (res == 1) {
            node_to_delete = NULL;
            return 0;
        }
        return res;
    }
    if (val > node->val) {
        int res = _bst_delete(node->left, val);
        if (res == 1) {
            node->left = NULL;
            return 0;
        }
        return res;
    } else {
        int res = _bst_delete(node->right, val);
        if (res == 0) {
            node->right = NULL;
            return 0;
        }
        return res;
    }
}

int bst_delete(BST *bst, float val) {
    if (bst->root == NULL)
        return -1;
    
    if (_bst_delete(bst->root, val) == -1)
        return -1;
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
