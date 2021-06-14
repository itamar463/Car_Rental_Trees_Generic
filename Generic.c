#include "Generic.h"
#include "matam.h"

void *createTree(void *(*init)(), int (*compare)(void *data, void *root), void *(*get)(void *data),
                 void freeData(void *data)) {
    /*Creat new tree of cars*/
    Tree *tree = (Tree *) checked_malloc(sizeof(Tree));
    tree->root = NULL;
    tree->elementCount = 0;
    tree->init = init;
    tree->get = get;
    tree->compare = compare;
    tree->freeData = freeData;
    return tree;
}

Node *addNodeToTree(Node *root, Node *newNode, int(*compare)(void *data, void *root)) {
    /* Add new car to the tree*/
    if (root == NULL) {
        return newNode;
    } else {
        if (root->right == NULL || root->left == NULL) {
            if ((*compare)(newNode->data, root) <= 0) {
                root->left = addNodeToTree(root->left, newNode, compare);
            } else {
                root->right = addNodeToTree(root->right, newNode, compare);
            }
        } else {
            if ((*compare)(newNode->data, root) <= 0) {
                addNodeToTree(root->left, newNode, compare);
            } else {
                addNodeToTree(root->right, newNode, compare);
            }
        }
    }
    return root;
}


int addNewNode(Tree *tree) {

    /* If car is valid add new car to the list*/
    Node *newNode = (Node *) checked_malloc(sizeof(Node));
    newNode->data = tree->init();
    newNode->key = tree->get(newNode->data);
    newNode->left = NULL;
    newNode->right = NULL;
    if (tree->root == NULL) {
        tree->root = newNode;
    } else {
        tree->root = addNodeToTree(tree->root, newNode, tree->compare);
    }
    tree->elementCount++;
    return 1;
}

void freeNode(Node *root, void freeData(void *data)) {
    freeData(root->data);
    checked_free(root->data);
    checked_free(root);
}

Node *removeNodeHelper(Node *root, char *detailCheck, int *elementCounter, int (*compare)(void *data, void *root),
                       void freeData(void *data)) {
    /*Check for the given car to delete and replace his position if needed*/
    if (root == NULL) {
        return NULL;
    }
    if (((*compare)(detailCheck, root->data) != 0)) {
        if (((*compare)(detailCheck, root->data) < 0)) {
            root->left = removeNodeHelper(root->left, detailCheck, elementCounter, compare, freeData);
        } else {
            root->right = removeNodeHelper(root->right, detailCheck, elementCounter, compare, freeData);
        }
        return root;
    } else {
        if ((root->left == NULL) && (root->right == NULL)) {
            freeNode(root, freeData);
            (*elementCounter)--;
            return NULL;
        } else if (root->left == NULL) {
            Node *temp = root->right;
            freeNode(root, freeData);
            (*elementCounter)--;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            freeNode(root, freeData);
            (*elementCounter)--;
            return temp;
        } else {
            Node *x = root->right;
            void *tempData = root->data;
            char *tempKey = root->key;
            Node **xParent = &(root->right);
            while (x->left) {
                xParent = &(x->left);
                x = x->left;
            }
            root->key = x->key;
            root->data = x->data;
            x->key = tempKey;
            x->data = tempData;
            *xParent = removeNodeHelper(x, x->key, elementCounter, compare, freeData);
        }
    }
    return root;
}

int removeNode(Tree *tree, void *(*get)(void *), int (*compare)(void *data, void *root)) {
    /*Delete car by help funcs*/
    int tmpCount = tree->elementCount;
    char *detailCheck = (char *) checked_malloc(sizeof(char) * 254);
    detailCheck = (*get)(detailCheck);
    if (tree->root == NULL) {
        printf("Empty tree\n");
        checked_free(detailCheck);
        return 0;
    }

    tree->root = removeNodeHelper(tree->root, detailCheck, &tree->elementCount, compare, tree->freeData);
    if (tmpCount == tree->elementCount) {
        printf("Object doesnt found\n");
    } else printf("Object has been deleted\n");
    checked_free(detailCheck);
    return 1;

}

/*
LinkedNode *findNodeHelper(Node *root, LinkedNode **head, void * dataCheck, int (*compare)(void *, void *)) {
    finding client by Id and create linked list
    if ((root) == NULL) {
        return NULL;
    }
    findNodeHelper(root->left, head, get);
    if (compare(root->data,dataCheck) == 0) {
        (*head) = addToListC(head, root->data);
    }
    findNodeHelper(root->right, head, idCheck);
    return (*head);
}

void *findNode(Tree *tree, void *(*get)(void *), int (*compare)(void *, void *)) {
    find object and return linked list by ID or by date

    LinkedNode *head = NULL;
    if (tree->root == NULL) {
        printf("No objects\n");
        return NULL;
    }
    head = findNodeHelper(tree->root, &head, get, compare);
    return head;
}
*/

/**/
