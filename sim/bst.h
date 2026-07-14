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
int bst_init_with_arr(BST *, float *, int);
void bst_insert(BST *, float);
void bst_delete(BST *, float);
void bst_free(BST *);
float *bst_to_arr(BST *);
int bst_print_arr(BST *);

#endif