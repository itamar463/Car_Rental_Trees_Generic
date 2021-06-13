#include "Generic.h"
#include "matam.h"

void *createTree() {
    /*Creat new tree of cars*/
    Tree *tree = (Tree *) checked_malloc(sizeof(Tree));
    tree->root = NULL;
    tree->elementCount = 0;
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


int addNewNode(Tree *tree, void *(*init)(), int (*compare)(void *data, void *root), void *(*get)(void *data)) {

    /* If car is valid add new car to the list*/
    Node *newNode = (Node *) checked_malloc(sizeof(Node));
    newNode->data = (*init)();
    newNode->key = (*get)(newNode->data);
    newNode->left = NULL;
    newNode->right = NULL;
    if (tree->root == NULL) {
        tree->root = newNode;
    } else {
        tree->root = addNodeToTree(tree->root, newNode, compare);
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
            root->left = removeNodeHelper(root->left, detailCheck, elementCounter, compare,freeData);
        } else {
            root->right = removeNodeHelper(root->right, detailCheck, elementCounter, compare,freeData);
        }
        return root;
    } else {
        if ((root->left == NULL) && (root->right == NULL)) {
            freeNode(root,freeData);
            (*elementCounter)--;
            return NULL;
        } else if (root->left == NULL) {
            Node *temp = root->right;
            freeNode(root,freeData);
            (*elementCounter)--;
            return temp;
        } else if (root->right == NULL) {
            Node *temp = root->left;
            freeNode(root,freeData);
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
            *xParent = removeNodeHelper(x, x->key, elementCounter,compare,freeData);
        }
    }
    return root;
}

int removeNode(Tree *tree, void *(*getByScan)(), int (*compare)(void *data, void *root), void freeData(void *data)) {
    /*Delete car by help funcs*/
    int tmpCount = tree->elementCount;
    char* detailCheck = (char *) checked_malloc(sizeof(char )*254);
    detailCheck = (*getByScan)(detailCheck);
    if (tree->root == NULL) {
        printf("Empty tree\n");
        checked_free(detailCheck);
        return 0;
    }

    tree->root = removeNodeHelper(tree->root, detailCheck, &tree->elementCount, compare, freeData);
    if (tmpCount == tree->elementCount) {
        printf("Object doesnt found\n");
    } else printf("Object has been deleted\n");
    checked_free(detailCheck);
    return 1;

}
