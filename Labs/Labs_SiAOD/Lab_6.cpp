#include "header.h"
bool vr = 1;
bool hr = 1;
int i = 0;

int main(){
	srand(time(NULL));
	Tree *head = NULL;
	//int arr[] = { 10,3,1,15,16,14,12,19,13,6,5,18 };
	int arr[100];
	for (int i = 0; i < 100; i++)
	{
		arr[i] = rand()%100000000;
	}

	for (int i = 0; i < 100; i++)
	{
		b2insert(arr[i], head);
	}
	//leftToRight(head);
	cout << "\n";
	//topDown(head);
	cout << "\n";
	cout << heightMid(head) << endl;

}

int search(const int searchKey, Tree* head) {
	Tree* current = head;
	while (current != nullptr) {
		if (searchKey < current->data) {
			current = current->left;
			i++;
		}
		else if (searchKey > current->data) {
			current = current->right;
			i++;
		}
		else {
			return current->data; // Key found.
		}
	}
	return 0;

	//return current->data; // Return a reference to the newly created node's value.
}

void b2insert(int data, Tree *&p)
{
	if (p == NULL)
	{
		p = new Tree;
		p->data = data;
		p->left = p->right = NULL;
		p->bal = 0;
		vr = 1;
	}
	else if (data < p->data)
	{
		b2insert(data, p->left);
		if (vr == 1)
		{
			if (p->bal == 0) // эемент один на странице
			{
				Tree* q = p->left;
				p->left = q->right;
				q->right = p;
				p = q;
				q->bal = 1;
				hr = 1;
				vr = 0;
			}
			else {
				p->bal = 0;
				vr = 1;
				hr = 0;
			}
		}
		else {
			hr = 0;	
		}
	}
	else if (data > p->data)
	{
		b2insert(data, p->right);
		if (vr == 1)
		{
			p->bal = 1;
			hr = 1;
			vr = 0;
		}
		else if (hr == 1)
		{
			if (p->bal == 1)
			{
				Tree* q = p->right;
				p->bal = 0;
				q->bal = 0;
				p->right = q->left;
				q->left = p;
				p = q;
				vr = 1;
				hr = 0;
			}
		}
	}
}