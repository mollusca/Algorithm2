#include <stdio.h>
#include <stdlib.h>

int S[100];
int temp[100];
int heapSort[100];
int heapSize;

void siftdown(int i) {
	int siftkey = S[i];
	int parent = i;
	int smallerChild;

	while (2 * parent <= heapSize) {
		if ((2 * parent < heapSize) && (S[2 * parent] < S[2 * parent + 1]))
			smallerChild = 2 * parent;
		else
			smallerChild = 2 * parent + 1;

		if (siftkey > S[smallerChild]) {
			S[parent] = S[smallerChild];
			parent = smallerChild;
		}
		else
			break;
	}
	S[parent] = siftkey;
}

void makeheap(int n) {
	int i;

	heapSize = n;

	for (i = n / 2; i >= 1; i--)
		siftdown(i);
}

int root() {
	int keyout = S[1];
	int i;

	S[1] = S[heapSize];
	heapSize--;
	
	siftdown(1);

	return keyout;
}

void removekeys() {
	int i, cnt = heapSize;

	for (i = 1; i <= cnt; i++)
		heapSort[i] = root();
}

void insert(int data) {
	int child;
	int i;

	heapSize++;
	child = heapSize;

	for (i = heapSize / 2; 1 >= 1; i = i / 2) {
		if (S[i] > data) {
			S[child] = S[i];
			child = i;
		}
		else {
			S[child] = data;
			break;
		}
	}
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	int i = 1;
	int t, cnt = 0;

	// input.txtù�� -> heapSize
	fscanf(fp, "%d", &t);
	heapSize = t;
	
	// �� �迭 1������ ���� (0��°�� ��������)
	while (!feof(fp)) {
		fscanf(fp, "%d", &t);
		cnt++;
		S[i++] = t;

		printf("%2d ", t);
	} printf("[cnt : %d]\n", cnt);

	// �� ũ�⺸�� ū �迭�� ���ý� �������ʵ��� �����Ⱚ�Է�
	for (i = heapSize + 1; i < 100; i++)
		S[i] = 9999;

	// MakeHeap
	makeheap(heapSize);
	for (i = 1; i <= heapSize; i++)
		temp[i] = S[i];

	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[make heap��]\n");

	// RemoveKey (1������ root�� HeapSort�迭�� ���� ����)
	removekeys();
	for (i = 1; i <= cnt; i++)
		printf("%2d ", heapSort[i]);
	printf("[heapSort �� ����]\n");
	
	// root�������� heapSize�� �پ�꿡���� ���� Size�� ����
	heapSize = cnt;
	// ���� �� ���
	for (i = 1; i <= heapSize; i++)
		S[i] = temp[i];

	// 50 Insert
	insert(50);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[50�� insert�� ����]\n");

	// min�� ����
	root();
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[min���� ������ ����]\n");

	// 11 Insert
	insert(11);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[11�� insert�� ����]\n");

	// 1 Insert
	insert(1);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[1�� insert�� ����]\n");

	// min �� ����
	root();
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[min���� ������ ����]\n");

	return 0;
}