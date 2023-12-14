#include <stdio.h>
#include <stdlib.h>

typedef struct BSTree {
    int data;
    struct BSTree *left;
    struct BSTree *right;
} BSTree;

BSTree *createNode(int data);
void insert(BSTree **rootRef, int data);
void inorder(BSTree *root);

int main(void){

    int i, arr[] = {15, 5, 7, 11, 35, 48, 12, 33};

    BSTree *root = NULL;

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
        insert(&root, arr[i]);

    inorder(root);    

    return 0;
}

BSTree *createNode(int data){
    BSTree *newNode = malloc(sizeof(BSTree));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->data = data;
        return newNode;
    }
    return NULL;
}

void insert(BSTree **rootRef, int data){
    BSTree *newNode = createNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for the tree node!");
        exit(EXIT_FAILURE);
    }

    if (*rootRef == NULL)
        *rootRef = newNode;
    else if (data < (*rootRef)->data)
        insert(&(*rootRef)->left, data);
    else if (data > (*rootRef)->data)
        insert(&(*rootRef)->right, data);
}

void inorder(BSTree *root){
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
