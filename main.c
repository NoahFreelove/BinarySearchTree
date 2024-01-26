#include <stdbool.h>
#include <stdio.h>

// Value -> void*
// Node* -> left node, right node, Value
// Comparison func
// Recursive search func


typedef struct TNode TNode;
typedef struct Tree Tree;

struct TNode {
    void* value;
    TNode* left;
    TNode* right;
};

struct Tree {
    TNode* root;
    int (*greater_than)(TNode*, TNode*);
    int (*equal_operator)(TNode*, TNode*);
};

int comp_int(TNode* a, TNode* b) {
    // cast a->value to int
    // cast b->value to int
    if((int)a->value > (int)b->value)
        return 1;
    else if((int)a->value < (int)b->value)
        return 0;
    else
        return -1;
}

TNode* recursive_find(TNode* curr, (*comp_func)(TNode*, TNode*),(*equal_func)(TNode*, TNode*), void* val) {
    // check base case:
    if(curr->left == NULL && curr->right == NULL)
        return NULL;

    if(curr->left == NULL) {
        if (equal_func(curr->right, val)) {
            return curr->right;
        }
        return NULL;
    }
    if(curr->right == NULL) {
        if (equal_func(curr->left, val)) {
            return curr->left;
        }
        return NULL;
    }


    // If left node > right node
    int result = comp_func(curr->left, curr->right);
    if(result == 1) {
        return recursive_find(curr->left, comp_func, equal_func, val);
    }
    if(result == 0){
        return recursive_find(curr->right, comp_func, equal_func, val);
    }
    return NULL;

}

TNode* find_val(Tree* tree, void* val) {
    return recursive_find(tree->root, tree->greater_than, tree->equal_operator, val);
}

int main()
{
    printf("Hello, World!\n");
    return 0;
}
