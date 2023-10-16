#include "header.h"

// процедура построения идеально сбалансированного дерева поиска
Tree* PBST(int arr[], int L, int R)
{
	if (L > R) {
		return NULL;
	}
	else {
		int m = (L + R) / 2;
		Tree* p = new Tree;
		p->data = arr[m];
		p->left = PBST(arr, L, m - 1);
		p->right = PBST(arr, m + 1, R);
		return p;
	}
}

int main()
{
	srand(time(NULL));
	const int n = 100;
	int arr[n];
	fillInc(arr, n);
	//fillrand(arr, n);
	//InsertSort(arr, n);

	Tree* root = NULL;
	root = PBST(arr, 0, n - 1);

	cout << "leftToRight:" << endl;
	leftToRight(root);

	int sizeTree = size(root);
	cout << "\nsize: " << sizeTree << endl;

	int TotalsumTree = sumTree(root);
	cout << "totalsum: " << TotalsumTree << endl;

	int MaxHeightTree = heightTree(root);
	cout << "height: " << MaxHeightTree << endl;

	float HeightMid = heightMid(root);
	cout << "heightMid: " << HeightMid << endl;
}
