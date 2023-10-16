#include <iostream>

using namespace std;

struct Tree
{
    int data;
    Tree* left = NULL;
    Tree* right = NULL;
};

// ������� �������� � ������
void insert(Tree*& root, int data) {
    if (root == NULL) {
        root = new Tree;
        root->data = data;
    }
    else if (data <= root->data) {
        insert(root->left, data);
    }
    else {
        insert(root->right, data);
    }
}

//����� �������
void leftToRight(Tree* root) {
    if (root != NULL) {
        leftToRight(root->left);
        cout << root->data << " ";
        leftToRight(root->right);
    }
}

// ������ ����
void topDown(Tree* root) {
    if (root == NULL)
        return;

    cout << root->data << " ";
    topDown(root->left);
    topDown(root->right);
}

// ����� �����
void bottomUp(Tree* root) {
    if (root == NULL)
        return;

    bottomUp(root->left);
    bottomUp(root->right);
    cout << root->data << " ";
}

// ����������� ������� ������
int size(Tree* root) {
    if (root == nullptr)
        return 0;

    return size(root->left) + 1 + size(root->right);
}

// ����������� ����������� ����� ��� ������
int sumTree(Tree* root) {
    if (root == nullptr) {
        return 0;
    }

    return root->data + sumTree(root->left) + sumTree(root->right);
}

// ����������� ������ ������
int heightTree(Tree* root) {
    if (root == nullptr) {
        return 0;
    }

    return 1 + max(heightTree(root->left), heightTree(root->right));
}

// ������� ���������� ����� ���� ����� �� ����� �� ������ ������� �� L-��� ������
int SPD(Tree* root, int L = 1) {
    if (root == nullptr) {
        return 0;
    }

    return L + SPD(root->left, L + 1) + SPD(root->right, L + 1);
}

// ����������� ������� ������ ������
float heightMid(Tree* root) {
    float p = (float)(SPD(root) / size(root));
    cout << p << endl;
    return (float)(SPD(root)) / size(root);
}

int main() {
    Tree* root = NULL;

    insert(root, 4);
    insert(root, 2);
    insert(root, 5);
    insert(root, 1);
    insert(root, 3);
    insert(root, 6);

    int sizeTree = size(root);
    cout << "size: " << sizeTree << endl;

    int TotalsumTree = sumTree(root);
    cout << "totalsum: " << TotalsumTree << endl;

    int MaxHeightTree = heightTree(root);
    cout << "height: " << MaxHeightTree << endl;

    float HeightMid = heightMid(root);
    cout << "heightMid: " << HeightMid << endl;

    cout << "SDP: " << SPD(root) << endl;


    cout << "\n\n";

    cout << "topDown:" << endl;
    topDown(root);

    cout << "\nleftToRight:" << endl;
    leftToRight(root);

    cout << "\nbottomUp:" << endl;
    bottomUp(root);

    return 0;
}