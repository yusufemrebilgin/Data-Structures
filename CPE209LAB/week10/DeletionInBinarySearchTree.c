#include <stdio.h>
#include <stdlib.h>

typedef struct NodeBST {
    int data;
    struct NodeBST *left;
    struct NodeBST *right;
} NodeBST;

NodeBST *createTreeNode(int data);
NodeBST *insert(NodeBST *root, int data);
NodeBST *delete(NodeBST *root, int data);
void traverse(NodeBST *root);

int main(void){

    int i, arr[] = {7, 5, 3, 15, 11, 20, 18, 30};
    
    NodeBST *root = NULL;

    for (i = 0; i < sizeof(arr) / sizeof(*arr); i++)
        root = insert(root, arr[i]);

    traverse(root);

    printf("\n\nDeleting node with both child (20):\n");
    root = delete(root, 20);
    traverse(root);

    printf("\n\nDeleting a leaf node (3):\n");
    root = delete(root, 3);
    traverse(root);

    printf("\n\nDeleting node with single child (5):\n");
    root = delete(root, 5);
    traverse(root);

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

NodeBST *insert(NodeBST *root, int data) {
    NodeBST *newNode = createTreeNode(data);    
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed for the tree node!");
        exit(EXIT_FAILURE);
    }

    if (root == NULL)
        return newNode;
    else if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
}

NodeBST *delete(NodeBST *root, int data){
    if (root == NULL)
        return NULL;
    if (root->data == data) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            NodeBST *tmp = root->right;
            free(root);
            return tmp;
        }
        else if (root->right == NULL) {
            NodeBST *tmp = root->left;
            free(root);
            return tmp;
        }
        else {
            NodeBST *temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;
            temp->left = root->left;
            temp = root->right;
            free(root);
            return temp;
        }
    }
    else if (data < root->data)
        root->left = delete(root->left, data);
    else if (data > root->data)
        root->right = delete(root->right, data);
}

void traverse(NodeBST *root){
    if (root == NULL)
        return;
    traverse(root->left);
    printf("%d ", root->data);
    traverse(root->right);
}