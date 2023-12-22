#include <stdio.h>
#include <stdlib.h>

typedef struct _NodeBST {
    int data;
    struct _NodeBST *left;
    struct _NodeBST *right;
} NodeBST;

NodeBST *createNode(int data);
void insert(NodeBST **rootRef, int data);
void delete(NodeBST **rootRef, int data);
NodeBST *findMin(NodeBST *root);
void traverse(NodeBST *root);

int main(void){
    
    NodeBST *root = NULL;

    int i, arr[] = {5, 3, 7, 11, 2, 4, 25, 6, 1};

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
        insert(&root, arr[i]);

    printf("Inorder: ");
    traverse(root);

    printf("\n\nDeleting node with both child (3):\n");
    delete(&root, 3);
    traverse(root);

    printf("\n\nDeleting a leaf node (1):\n");
    delete(&root, 1);
    traverse(root);

    printf("\n\nDeleting node with single child (11):\n");
    delete(&root, 11);
    traverse(root);

    return 0;
}

NodeBST *createNode(int data){
    NodeBST *newNode = malloc(sizeof(NodeBST));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->data = data;
    }
    return newNode;
}

void insert(NodeBST **rootRef, int data){
    if (*rootRef == NULL) 
        *rootRef = createNode(data);
    else if (data < (*rootRef)->data)
        insert(&(*rootRef)->left, data);
    else if (data > (*rootRef)->data)
        insert(&(*rootRef)->right, data);
}

void delete(NodeBST **rootRef, int data){
    if (*rootRef == NULL)
        return;

    if (data < (*rootRef)->data)
        delete(&(*rootRef)->left, data);
    else if (data > (*rootRef)->data)
        delete(&(*rootRef)->right, data);
    else {
        if ((*rootRef)->left == NULL) {
            NodeBST *temp = *rootRef;
            *rootRef = (*rootRef)->right;
            free(temp);
        }
        else if ((*rootRef)->right == NULL) {
            NodeBST *temp = *rootRef;
            *rootRef = (*rootRef)->left;
            free(temp);
        }
        else {
            NodeBST *temp = findMin((*rootRef)->right);
            (*rootRef)->data = temp->data;
            delete(&(*rootRef)->right, temp->data);
        }
    }
}

NodeBST *findMin(NodeBST *root){
    if (root == NULL) 
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

void traverse(NodeBST *root){
    if (root == NULL) return;
    traverse(root->left);
    printf("%d ", root->data); //Inorder
    traverse(root->right);
}