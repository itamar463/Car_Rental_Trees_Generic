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
} Tree;
typedef struct LinkedNode {
    void *data;
    struct LinkedNode *next;
} LinkedNode;

void *createTree(void *(*init)(), int (*compare)(void *data, void *root), void *(*get)(void *data),
                 void freeData(void *data));

int addNewNode(Tree *tree);
/**/
int removeNode(Tree *tree, void *(*get)(void *data), int (*compare)(void *data, void *root));
void *findNode(Tree *tree,void *(*get)(void *),int (*compare)(void *,void *));
#endif
