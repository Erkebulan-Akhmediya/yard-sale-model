#ifndef BST_H
#define BST_H

struct BSTNode {
    float val;
    struct BSTNode *left;
    struct BSTNode *right;
};

typedef struct {
    struct BSTNode *root;
    int size;
} BST;

void bst_init(BST *);
int bst_insert(BST *, float);
int bst_delete(BST *, float);
float *bst_to_arr(BST *);

#endif