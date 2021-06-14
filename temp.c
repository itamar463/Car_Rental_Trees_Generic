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
    void (*printTree)(void* node);
} Tree;
typedef struct LinkedNode {
    void *data;
    struct LinkedNode *next;
} LinkedNode;

void *createTree(void *(*init)(), int (*compare)(void *data, void *root), void *(*get)(void *data),
                 void freeData(void *data) ,void (*printTree)(void* node) );

int addNewNode(Tree *tree);
/**/
int removeNode(Tree *tree, void *(*get)(void *data), int (*compare)(void *data, void *root));
void *findNode(Tree *tree,void *(*get)(void *),int (*compare)(void *,void *));

void freeTree(Tree* tree );
void printTree(Node* node, void (*print)(void* Node));

#endif








void printTree(Node * node, void (*print)(void* Node)){
    Node *tmp = node;
    if(tmp == NULL){
        return;
    }
    printTree(tmp->left , print);
    print(tmp->data);
    printTree(node->right , print);

}


void freeTreeHelper(Node *node , void (*freeData)(void *) ){
    if (node == NULL) return;
    else {Node *tmp = node;
        /* first delete both subtrees */
        freeTreeHelper( tmp->left, freeData);
        freeTreeHelper(tmp->right , freeData);
        /* then delete the node */
        freeData(tmp->data);
        checked_free(tmp->data);
        checked_free(tmp);}
}

void freeTree(Tree* tree ){
    freeTreeHelper(tree->root , tree->freeData);
    tree->elementCount = 0;
    tree->root = NULL;

}

/**/
