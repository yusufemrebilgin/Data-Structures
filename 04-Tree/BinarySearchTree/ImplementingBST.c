#include <stdio.h>
#include <stdlib.h>

typedef struct _NodeBST {
    int data;
    struct _NodeBST *left;
    struct _NodeBST *right;
} NodeBST;

NodeBST *createNode(int data);
NodeBST *insert(NodeBST *root, int data);
NodeBST *delete(NodeBST *root, int data);
NodeBST *search(NodeBST *root, int key);
NodeBST *findMin(NodeBST *root);
NodeBST *findMax(NodeBST *root);
int size(NodeBST *root);
int height(NodeBST *root);
int depth(NodeBST *root, int data);
int sum(NodeBST *root);
void preorder(NodeBST *root);
void inorder(NodeBST *root);
void postorder(NodeBST *root);
void freeTree(NodeBST *root);

int main(void){

    NodeBST *root = NULL;

    int choice = -1;

    while (1) {
        printf("***************************************\n"
               "1.  INSERT\t\t"
               "6.  TRAVERSE\n"
               "2.  DELETE\t\t"
               "7.  TREE SIZE\n"
               "3.  SEARCH\t\t"
               "8.  TREE HEIGHT\n"
               "4.  FIND MIN\t\t"
               "9.  FIND DEPTH\n"
               "5.  FIND MAX\t\t"
               "10. SUM\n"
               "0.  EXIT\n\n"
               "Last choice: %d\n"
               "Enter your new choice: ", choice);

        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case 1: {
                int value;
                printf("Please enter a value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            }
            case 2: {
                int value;
                printf("Enter the value of the node you want to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            }
            case 3: {
                int target;
                printf("Enter the value you are searching for: ");
                scanf("%d", &target);
                if (search(root,target) != NULL)
                    printf("\ntrue\n");
                else
                    printf("\nfalse\n");
                break;
            }
            case 4: {
                NodeBST *min = findMin(root);
                if (min != NULL)
                    printf("Minimum value in the BST is %d\n", min->data);
                break;
            }
            case 5: {
                NodeBST *max = findMax(root);
                if (max != NULL)
                    printf("Maximum value in the BST is %d\n", max->data);
                break;
            }
            case 6: {
                int opt;
                printf("\n1.Preorder\n2.Inorder\n3.Postorder\n\n..");
                scanf("%d", &opt);
                if (opt == 1)
                    printf("\nPreorder:  "), preorder(root);
                else if (opt == 2)
                    printf("\nInorder:   "), inorder(root);
                else if (opt == 3)
                    printf("\nPostorder: "), postorder(root);
                break;
            }
            case 7:
                printf("\nSize of the binary search tree is %d\n", size(root));
                break;
            case 8:
                printf("\nHeight of the binary search tree is %d\n", height(root));
                break;
            case 9: {
                int d;
                printf("Enter the depth value for which you want to find the number of nodes: ");
                scanf("%d", &d);
                printf("\nNumber of nodes at the entered depth: %d\n", depth(root, d));
                break;
            }
            case 10:
                printf("Sum of the BST is %d\n", sum(root));
                break;
            case 0:
                printf("The program has been terminated.");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid option. Please try again..\n");
                freeTree(root);
                break;
        }
        printf("\n");
    }
    
}

NodeBST *createNode(int data){
    NodeBST *newNode = malloc(sizeof(NodeBST));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->data = data;
    }
    return newNode;
}

NodeBST *insert(NodeBST *root, int data){
    NodeBST *newNode = createNode(data);
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!");
        exit(EXIT_FAILURE);
    }

    if (root == NULL)
        return newNode;
    else if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
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
            NodeBST *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            NodeBST *temp = root->left;
            free(root);
            return temp;
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
    return root;
}

NodeBST *search(NodeBST *root, int data){
    if (root == NULL || root->data == data)
        return root;
    return (data < root->data) ? search(root->left, data) : search(root->right, data);
}

NodeBST *findMin(NodeBST *root){
    if (root == NULL) 
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

NodeBST *findMax(NodeBST *root){
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

int size(NodeBST *root){
    return (root == NULL) ? 0 : 1 + size(root->left) + size(root->right);
}

int height(NodeBST *root){
    if (root == NULL)
        return -1;
    else {
        int leftHeight  = height(root->left);
        int rightHeight = height(root->right);
        if (rightHeight > leftHeight)
            return rightHeight + 1;
        else
            return leftHeight + 1;
    }
}

int depth(NodeBST *root, int d){
    if (root == NULL)
        return 0;
    return (d == 0) ? 1 : depth(root->left, d - 1) + depth(root->right, d - 1);
}

int sum(NodeBST *root){
    return (root == NULL) ? 0 : root->data + sum(root->left) + sum(root->right);
}

void preorder(NodeBST *root){
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(NodeBST *root){
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(NodeBST *root){
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void freeTree(NodeBST *root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}