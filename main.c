#include <stdio.h>
#include <stdlib.h>

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
    int (*equal_operator)(TNode*, void*);
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

int eq_int(TNode* a, void* b) {
    if(*(int*)a->value == *(int*)b)
        return 1;
    else
        return 0;
}

TNode* recursive_find(TNode* curr, int (*comp_func)(TNode*, TNode*), int (*equal_func)(TNode*, void*), void* val) {
    //printf("ran\n");

    // check in case children but right value
    if(val != NULL) {
        if(curr->value != NULL) {
            if(equal_func(curr, val) == 1) {
                return curr;
            }
        }
    }

    // if no children
    if(curr->left == NULL && curr->right == NULL) {
        if(equal_func(curr, val) == 1) {
            return curr;
        }
        printf("Both null not right value\n");
        return NULL;
    }

    if(curr->left == NULL) {
        return recursive_find(curr->right, comp_func, equal_func, val);
    }
    if(curr->right == NULL) {
        return recursive_find(curr->left, comp_func, equal_func, val);
    }

    // If left node > right node
    const int result = comp_func(curr->left, curr->right);
    if(result == 1) {
        return recursive_find(curr->left, comp_func, equal_func, val);
    }
    if(result == 0){
        return recursive_find(curr->right, comp_func, equal_func, val);
    }

    // Check for equality
    const int equal_result_l = equal_func(curr->left, val);
    const int equal_result_r = equal_func(curr->right, val);
    if(equal_result_l == 1) {
        return curr->left;
    }
    if(equal_result_r == 1) {
        return curr->right;
    }

    printf("no cases reached");

    return NULL;

}

TNode* find_val(Tree* tree, void* val) {
    return recursive_find(tree->root, tree->greater_than, tree->equal_operator, val);
}

TNode* gen_node(void* val) {
    TNode* node = malloc(sizeof(TNode));
    node->value = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_node(TNode* node) {
    free(node->value);
    if(node->left != NULL) {
        free_node(node->left);
        node->left = NULL;
    }
    if(node->right != NULL) {
        free_node(node->right);
        node->right = NULL;
    }
    free(node);
    node = NULL;
}

Tree* gen_tree(TNode* root, int (*greater_than)(TNode*, TNode*), int (*equal_operator)(TNode*, TNode*)) {
    Tree* tree = malloc(sizeof(Tree));
    tree->root = root;
    tree->greater_than = greater_than;
    tree->equal_operator = equal_operator;
    return tree;
}

void free_tree(Tree* tree) {
    if(tree->root != NULL)
        free_node(tree->root);
    tree->root = NULL;
    free(tree);
}

TNode* gen_int_node(int val) {
    int* int_val = malloc(sizeof(int));
    *int_val = val;
    TNode* node = gen_node(int_val);
    return node;
}
int main()
{
    TNode* node = gen_node(NULL);
    Tree* tree = gen_tree(node, comp_int, eq_int);

    TNode* left = gen_int_node(5);
    TNode* right = gen_int_node(6);
    TNode* answer = gen_int_node(7);

    node->left = left;
    node->right = right;
    right->right = answer;

    int* search_val = malloc(sizeof(int));
    *search_val = 6;
    TNode* found = find_val(tree, search_val);

    if(found) {
        printf("Found: %d\n", *(int*)found->value);
    }

    free_tree(tree);
    return 0;
}
