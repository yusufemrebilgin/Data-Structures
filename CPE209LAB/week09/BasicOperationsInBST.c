#include <stdio.h>
#include <stdlib.h>

typedef struct NodeBST {
    int data;
    struct NodeBST *left;
    struct NodeBST *right;
} NodeBST;

NodeBST *createTreeNode(int data);
void insert(NodeBST **rootRef, int data);
void traverse(NodeBST *root);
int size(NodeBST *root);
NodeBST *search(NodeBST *root, int data);

int main(void){

    int i, arr[] = {7, 5, 3, 15, 11, 20, 18, 30};
    
    NodeBST *root = NULL;

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
        insert(&root, arr[i]);

    
    printf("Inorder: ");
    traverse(root);
    
    printf("\nSize of the binary search tree is %d\n", size(root));

    if (search(root, 5))
        printf("true\n");
    else
        printf("false\n");

    return 0;
}

NodeBST *createTreeNode(int data) {
    NodeBST *newNode = malloc(sizeof(NodeBST));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->data = data;
    }
    return newNode;
}

void insert(NodeBST **rootRef, int data) {
    NodeBST *newNode = createTreeNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }

    if (*rootRef == NULL)
        *rootRef = newNode;
    else if (data < (*rootRef)->data)
        insert(&(*rootRef)->left, data);
    else if (data > (*rootRef)->data)
        insert(&(*rootRef)->right, data);
}

void traverse(NodeBST *root){
    if (root == NULL)
        return;
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
}

int size(NodeBST *root){
    return (root == NULL) ? 0 : 1 + size(root->left) + size(root->right);
}

NodeBST *search(NodeBST *root, int data){
    if (root == NULL || root->data == data)
        return root;
    return (data < root->data) ? search(root->left, data) : search(root->right, data);
}