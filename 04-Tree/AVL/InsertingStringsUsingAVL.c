#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int height;
    const char *str;
    struct Node *left;
    struct Node *right;
} AVLTreeNode;

AVLTreeNode *createNode(const char *str);
int getMax(int x, int y);
int getHeight(AVLTreeNode *root);
int getBalance(AVLTreeNode *root);
int getSize(AVLTreeNode *root);
int compareStrings(const char *str1, const char *str2);
AVLTreeNode *leftRotate(AVLTreeNode *root);
AVLTreeNode *rightRotate(AVLTreeNode *root);
AVLTreeNode *insert(AVLTreeNode *root, const char *str);
void inorder(AVLTreeNode *root);
void freeTree(AVLTreeNode *root);

int main(void){

    AVLTreeNode *root = NULL;

    const char *names[] = {"Michael", "Jim", "Pam", "Dwight", "Angela",
                            "Stanley", "Kevin", "Kelly", "Ryan", "Toby"};
    
    size_t i;
    size_t size = sizeof(names) / sizeof(*names);

    for (i = 0; i < size; i++)
        root = insert(root, names[i]);

    printf("Inorder Traversal:\n");
    inorder(root);

    return 0;
}

AVLTreeNode *createNode(const char *str){
    AVLTreeNode *newNode = malloc(sizeof(AVLTreeNode));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->height = 0;
        newNode->str = malloc(strlen(str) + 1);
        if (newNode->str != NULL) {
            strcpy((char *)newNode->str, str);
        }
        else {
            fprintf(stderr, "Memory allocation failed for the string!");
            free(newNode);
            exit(EXIT_FAILURE);
        }
    }
    return newNode;
}

int getMax(int x, int y){
    return (x > y) ? x : y;
}

int getHeight(AVLTreeNode *root){
    return (root == NULL) ? -1 : root->height;
}

int getBalance(AVLTreeNode *root){
    return (root == NULL) ? 0 : getHeight(root->left) - getHeight(root->right);
}

int getSize(AVLTreeNode *root){
    return (root == NULL) ? 0 : 1 + getSize(root->left) + getSize(root->right);
}

int compareStrings(const char *str1, const char *str2){
    while (*str1 && *str2) {
        char ch1 = tolower(*str1);
        char ch2 = tolower(*str2);

        if (ch1 < ch2) return -1;
        else if (ch1 > ch2) return 1;

        str1++;
        str2++;
    }

    return (*str1) ? (*str2) ? 1 : -1 : 0;
}

AVLTreeNode *leftRotate(AVLTreeNode *root){
    AVLTreeNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;

    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
    temp->height = getMax(getHeight(temp->left), getHeight(temp->right)) + 1;
    return temp;
}

AVLTreeNode *rightRotate(AVLTreeNode *root){
    AVLTreeNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;

    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;
    temp->height = getMax(getHeight(temp->left), getHeight(temp->right)) + 1;
    return temp;
}

AVLTreeNode *insert(AVLTreeNode *root, const char *str){

    if (root == NULL) {
        AVLTreeNode *newNode = createNode(str);
        // Bellek ayırma işlemi başarısızsa hata mesajı yazdır ve programı sonlandır
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed!");
            exit(EXIT_FAILURE);
        }
        return newNode;
    }
    else if (compareStrings(str, root->str) < 0)
        root->left = insert(root->left, str);
    else if (compareStrings(str, root->str) > 0)
        root->right = insert(root->right, str);

    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalance(root); /* {-1,0,1} dışı değer alırsa düğüm dengesizdir */

    // Left-Left (LL) Rotation
    if (balanceFactor > 1 && compareStrings(str, root->left->str) < 0)
        return rightRotate(root);
    
    // Left-Right (LR) Rotation
    if (balanceFactor > 1 && compareStrings(str, root->left->str) > 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Right (RR) Rotation
    if (balanceFactor < -1 && compareStrings(str, root->right->str) > 0)
        return leftRotate(root);
    
    // Right-Left (RL) Rotation
    if (balanceFactor < -1 && compareStrings(str, root->right->str) < 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorder(AVLTreeNode *root){
    if (root == NULL) return;
    inorder(root->left);
    printf("%s, ", root->str);
    inorder(root->right);
}

void freeTree(AVLTreeNode *root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free((void *)root->str);
    free(root);
}