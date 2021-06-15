#include "matam.h"
#include <stdio.h>
#include <string.h>

#ifndef CAR_PROJECT_BY_TREES_GENERIC_H
#define CAR_PROJECT_BY_TREES_GENERIC_H
void *findNode(Tree *tree, void * dataCheck, int (*compare)(void *, void *));
int removeNode(Tree *tree, void * detailCheck, int (*compare)(void *data, void *root));
#endif






/* change the given parameter detailCheck instead of the function get*/
Node *removeNodeHelper(Node *root, void *detailCheck, int *elementCounter, int (*compare)(void *data, void *root),
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

int removeNode(Tree *tree, void * detailCheck, int (*compare)(void *data, void *root)) {
    /*Delete object by help funcs*/
    int tmpCount = tree->elementCount;
    if (tree->root == NULL) {
        printf("Empty tree\n");
        return 0;
    }

    tree->root = removeNodeHelper(tree->root, detailCheck, &tree->elementCount, compare, tree->freeData);
    if (tmpCount == tree->elementCount) {
        return 0;
    }
    return 1;

}
/* as well here*/
LinkedNode *findNodeHelper(Node *root, LinkedNode **head, void * dataCheck, int (*compare)(void *, void *)) {
    /* finding client by Id and create linked list*/
    if ((root) == NULL) {
        return NULL;
    }
    findNodeHelper(root->left, head, dataCheck,compare);
    if (compare(root->data,dataCheck) == 0) {
        (*head) = addToList(head, root->data);
    }
    findNodeHelper(root->right, head, dataCheck,compare);
    return (*head);
}

void *findNode(Tree *tree, void * dataCheck, int (*compare)(void *, void *)) {
    /*find object and return linked list by ID or by date*/
    LinkedNode *head = NULL;

    if (tree->root == NULL) {
        printf("No objects\n");
        return NULL;
    }
    head = findNodeHelper(tree->root, &head, dataCheck,compare);
    return head;
}


/*from Car example connection between general func removeNode*/
int deleteCar(Tree *carTree) {
    int check;
    char licenseNumberCheck[LICENSE_NUM_LEN * 4];
    printf("Enter license number of car to be deleted: \n");
    scanf("%s", licenseNumberCheck);
    if (valid_digit_check(licenseNumberCheck) == 0 || check_equal_size(licenseNumberCheck, LICENSE_NUM_LEN) == 0) {
        printf("License number is not valid\n");
        return 0;
    }
    check = removeNode(carTree, licenseNumberCheck, licenseNumberCompare);
    if (check == 0) {
        printf("Car doesn't found\n");
    } else{
        printf("Car has been deleted\n");
    }
    return check;
}


/**/
