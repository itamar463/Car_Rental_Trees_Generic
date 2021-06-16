#include "Generic.h"


void *createTree(void *(*init)(), int (*compare)(void *, void *), void *(*get)(void *),
                 void freeData(void *),void (*printTree)(void* )) {
    /*Creat new tree of cars*/
    Tree *tree = (Tree *) checked_malloc(sizeof(Tree));
    tree->root = NULL;
    tree->elementCount = 0;
    tree->init = init;
    tree->get = get;
    tree->compare = compare;
    tree->freeData = freeData;
    tree->printTree = printTree;
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


LinkedNode *addToList(LinkedNode **head, void* data) {
    /*CREATE CLIENT LIST AND CLIENT STRUCT AND ADD TO THE LINKED LIST */
    LinkedNode *new;
    new = (LinkedNode *) checked_malloc(sizeof(LinkedNode));
    new->data = data;
    new->next = (*head);
    (*head) = new;
    return (*head);
}



LinkedNode *findNodeHelper(Node *root, LinkedNode **head, void * dataCheck, int (*compare)(void *, void *)) {
   /* finding client by Id and create linked list*/
    if ((root) == NULL) {
        return NULL;
    }
    findNodeHelper(root->left, head, dataCheck,compare);
    if (compare(dataCheck,root->data) == 0) {
        (*head) = addToList(head, root->data);
    }
    findNodeHelper(root->right, head, dataCheck,compare);
    return (*head);
}

void *findNode(Tree *tree, void *dataCheck, int (*compare)(void *, void *)) {
    /*find object and return linked list by ID or by date*/
    LinkedNode *head = NULL;

    if (tree->root == NULL) {
        printf("No objects\n");
        return NULL;
    }
    head = findNodeHelper(tree->root, &head, dataCheck,compare);
    return head;
}

double averageKey(Node *temp,double (*get)(void *), int counter) {
    /*Generic func - Return the average of all sum of keys , get help by specific func to key*/
    double sumRight;
    double sumLeft;
    if (temp == NULL) {
        return 0;
    }
    sumLeft = averageKey(temp->left,get ,counter);
    sumRight = averageKey(temp->right,get ,counter);
    return sumLeft + sumRight + (get(temp->data)) / counter;
}



void printTree(Node * node, void (*print)(void* Node)){
    /*Generic func to print tree , get help by specific func to each tree*/
    Node *tmp = node;
    if(tmp->data == NULL){
        return;
    }
    printTree(tmp->left , print);
    print(tmp->data);
    printTree(node->right , print);

}


void freeTreeHelper(Node *node , void (*freeData)(void *) ){
    /*Help generic func freeTree to delete tree by help from specific freeData func*/
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
    /*Generic func to remove all the tree get help from freeTreeHelper func*/
    freeTreeHelper(tree->root , tree->freeData);
    tree->elementCount = 0;
    tree->root = NULL;

}
void  treeToArrayHelper(Node* root,void ** array, int* counter,int size){
    /*Help func to convert tree to array*/
    if(root == NULL || (*counter)==size){
        return ;
    }
    treeToArrayHelper(root->left,array,counter,size);
    treeToArrayHelper(root->right,array,counter,size);
    array[(*counter)] = root->data;
    (*counter)++;

}

void *treeToArray(Tree* tree,void *(*get)(void *)){
    /*Generic func to convert tree to array*/
    int counter = 0;
    void ** treeArray = get(tree);
    treeToArrayHelper(tree->root,treeArray,&counter,tree->elementCount);
    return treeArray ;
}
