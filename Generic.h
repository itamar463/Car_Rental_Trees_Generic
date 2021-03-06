#include "matam.h"
#include <stdio.h>
#include <string.h>

#ifndef CAR_PROJECT_BY_TREES_GENERIC_H
#define CAR_PROJECT_BY_TREES_GENERIC_H

typedef struct Node {
    char *key;
    void *data;
    struct Node *left;
    struct Node *right;
} Node;
typedef struct Tree {
    Node *root;
    int elementCount;

    void *(*init)();

    int (*compare)(void *, void *);

    void *(*get)(void *);

    void (*freeData)(void *);

    void (*printTree)(void *);
} Tree;
typedef struct LinkedNode {
    void *data;
    struct LinkedNode *next;
} LinkedNode;

void *createTree(void *(*init)(), int (*compare)(void *data, void *root), void *(*get)(void *data),
                 void freeData(void *data), void (*printTree)(void *));

int addNewNode(Tree *tree);

void freeTree(Tree *tree);

void printTree(Node *node, void (*print)(void *Node));

int removeNode(Tree *tree, void * detailCheck, int (*compare)(void *data, void *root));

void *findNode(Tree *tree, void * dataCheck, int (*compare)(void *, void *));

double averageKey(Node *temp, double (*get)(void *), int counter);

void *treeToArray(Tree *tree, void *(*getArray)(void *));

#endif
