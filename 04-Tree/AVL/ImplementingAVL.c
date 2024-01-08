#include <stdio.h>  
#include <stdlib.h>

typedef struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} AVLTreeNode;

AVLTreeNode *createNode(int data);
int getMax(int x, int y);
int getHeight(AVLTreeNode *root);
int getBalance(AVLTreeNode *root);
int getSize(AVLTreeNode *root);
AVLTreeNode *leftRotate(AVLTreeNode *root);
AVLTreeNode *rightRotate(AVLTreeNode *root);
AVLTreeNode *insert(AVLTreeNode *root, int data);
AVLTreeNode *delete(AVLTreeNode *root, int data);
void preorder(AVLTreeNode *root);
void inorder(AVLTreeNode *root);
void postorder(AVLTreeNode *root);
AVLTreeNode *search(AVLTreeNode *root, int data);
AVLTreeNode *findMin(AVLTreeNode *root);
AVLTreeNode *findMax(AVLTreeNode *root);
void freeTree(AVLTreeNode *root);

enum Menu { EXIT, INSERT, DELETE, TRAVERSE, SIZE, HEIGHT, SEARCH, FIND_MIN, FIND_MAX };

int main(void){

    AVLTreeNode *root = NULL;

    int choice = -1;
    while (1) {
        printf("****************************************\n"
               "1. INSERT\t\t"
               "5. TREE HEIGHT\n"
               "2. DELETE\t\t"
               "6. SEARCH\n"
               "3. TRAVERSE\t\t"
               "7. FIND MIN\n"
               "4. TREE SIZE\t\t"
               "8. FIND MAX\n"   
               "0. EXIT\n\n"
               "Last choice: %d\n"
               "Enter your new choice: ", choice);
        
        scanf("%d", &choice);
        printf("\n");

        switch (choice) {
            case INSERT: {
                int value;
                printf("Please enter a new value: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            }
            case DELETE: { 
                int value;
                printf("Enter the value of the node you want to delete: ");
                scanf("%d", &value);
                root = delete(root, value);
                break;
            }
            case TRAVERSE: {
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
            case SIZE:
                printf("\nSize of the AVL tree is %d\n", getSize(root));
                break;
            case HEIGHT:
                printf("\nHeight of a AVL Tree is %d\n", getHeight(root));
                break;
            case SEARCH: {
                int target;
                printf("Enter the value you are searching for: ");
                scanf("%d", &target);
                if (search(root,target) != NULL)
                    printf("\ntrue\n");
                else
                    printf("\nfalse\n");
                break;
            }
            case FIND_MIN: {
                AVLTreeNode *min = findMin(root);
                if (min != NULL)
                    printf("Minimum value in the AVL tree is %d\n", min->data);
                break;
            }
            case FIND_MAX: {
                AVLTreeNode *max = findMax(root);
                if (max != NULL)
                    printf("Maximum value in the AVL tree is %d\n", max->data);
                break;
            }
            case EXIT:
                printf("The program has been terminated.");
                freeTree(root);
                return EXIT_SUCCESS;
            default:
                printf("Invalid option. Please try again..");
                break;
        }
        printf("\n");
    }

    return 0;
}

AVLTreeNode *createNode(int data){
    AVLTreeNode *newNode = malloc(sizeof(AVLTreeNode));
    if (newNode != NULL) {
        newNode->left = newNode->right = NULL;
        newNode->data = data;
        newNode->height = 0;
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

AVLTreeNode *insert(AVLTreeNode *root, int data){
   
    if (root == NULL) {
        AVLTreeNode *newNode = createNode(data);
        // Bellek ayırma işlemi başarısızsa hata mesajı yazdır ve programı sonlandır
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed!");
            exit(EXIT_FAILURE);
        }
        return newNode;
    }
    else if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;

    int balanceFactor = getBalance(root); /* {-1,0,1} dışı değer alırsa düğüm dengesizdir */

    // Left-Left (LL) Rotation
    if (balanceFactor > 1 && data < root->left->data)
        return rightRotate(root);
    
    // Left-Right (LR) Rotation
    if (balanceFactor > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // Right-Right (RR) Rotation
    if (balanceFactor < -1 && data > root->right->data)
        return leftRotate(root);

    // Right-Left (RL) Rotation
    if (balanceFactor < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }


    return root;
}

AVLTreeNode *delete(AVLTreeNode *root, int data){
    if (root == NULL)
        return NULL;
    
    if (root->data == data) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        else if (root->left == NULL) {
            AVLTreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            AVLTreeNode *temp = root->left;
            free(root);
            return temp;
        }
        else {
            AVLTreeNode *temp = root->right;
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

    root->height = getMax(getHeight(root->left), getHeight(root->right)) + 1;

    if (root == NULL)
        return root;

    int balanceFactor = getBalance(root);

    if (balanceFactor > 1 && getBalance(root->left) >= 0) //LL
        return rightRotate(root);
    
    if (balanceFactor > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root);
        return rightRotate(root);
    }

    if (balanceFactor < -1 && getBalance(root->right) < 0)
        return leftRotate(root);

    if (balanceFactor < -1 && getBalance(root->right) >= 0) {
        root->right = rightRotate(root);
        return leftRotate(root);
    }

    return root;    
}

void preorder(AVLTreeNode *root){
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(AVLTreeNode *root){
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(AVLTreeNode *root){
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

AVLTreeNode *search(AVLTreeNode *root, int data){
    if (root == NULL || root->data == data)
        return root;
    return (data < root->data) ? search(root->left, data) : search(root->right, data);
}

AVLTreeNode *findMin(AVLTreeNode *root){
    if (root == NULL)
        return NULL;
    while (root->left != NULL)
        root = root->left;
    return root;
}

AVLTreeNode *findMax(AVLTreeNode *root){
    if (root == NULL)
        return NULL;
    while (root->right != NULL)
        root = root->right;
    return root;
}

void freeTree(AVLTreeNode *root){
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}