#include "matam.h"
#include <stdio.h>
#include <string.h>
#ifndef CAR_PROJECT_BY_TREES_GENERIC_H
#define CAR_PROJECT_BY_TREES_GENERIC_H

typedef struct Node {
    char * key;
    void * data;
    struct Node* left;
    struct Node* right;
} Node;
typedef struct Tree {
    Node* root;
    int elementCount;
} Tree;

void *createTree();
int addNewNode(Tree* tree,void*(*init)(),int (*keyCompare)(void * data, void * root),void * (*getKey)(void * data));
int removeNode(Tree *tree, void *(*get)(void *data), int (*compare)(void *data, void *root), void freeData(void *data));
#endif
