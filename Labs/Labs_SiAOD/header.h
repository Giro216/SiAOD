#include <iostream>
using namespace std;

struct Tree
{
    int data;
    Tree* left = NULL;
    Tree* right = NULL; 
    bool bal;
};

void b2insert(int data, Tree*& p);
int search(const int searchKey, Tree* head);

// Вставка элемента в дерево
//void insert(Tree*& root, int data) {
//    if (root == NULL) {
//        root = new Tree;
//        root->data = data;
//    }
//    else if (data <= root->data) {
//        insert(root->left, data);
//    }
//    else {
//        insert(root->right, data);
//    }
//}

//слева направо
void leftToRight(Tree* root) {
    if (root != NULL) {
        leftToRight(root->left);
        cout << root->data << " ";
        leftToRight(root->right);
    }
}

// сверху вниз
void topDown(Tree* root) {
    if (root == NULL)
        return;

    cout << root->data << " ";
    topDown(root->left);
    topDown(root->right);
}

// снизу вверх
void bottomUp(Tree* root) {
    if (root == NULL)
        return;

    bottomUp(root->left);
    bottomUp(root->right);
    cout << root->data << " ";
}

// Определение размера дерева
int size(Tree* root) {
    if (root == nullptr)
        return 0;

    return size(root->left) + 1 + size(root->right);
}

// Определение контрольной суммы для дерева
int sumTree(Tree* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->data + sumTree(root->left) + sumTree(root->right);
}

// Определение высоты дерева
int heightTree(Tree* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + max(heightTree(root->left), heightTree(root->right));
}

// функция вычисления суммы длин путей от корня до каждой вершины на L-том уровне
int SPD(Tree* root, int L = 1) {
    if (root == nullptr) {
        return 0;
    }

    return L + SPD(root->left, L + 1) + SPD(root->right, L + 1);
}

// Определение средней высоты дерева
float heightMid(Tree* root) {
    float p = (float)(SPD(root) / size(root));
    return (float)(SPD(root)) / size(root);
}

void fillInc(int A[], int N) {
    for (int i = 0; i < N; i++) {
        A[i] = i;
    }
}
void fillrand(int A[], int N) {
    for (int i = 0; i < N; i++) {
        A[i] = rand() % N;
    }
}
void PrintMas(int A[], int N) {
    for (int i = 0; i < N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}

void InsertSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
