
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
