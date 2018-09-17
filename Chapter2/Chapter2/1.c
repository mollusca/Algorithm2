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

	// input.txt첫줄 -> heapSize
	fscanf(fp, "%d", &t);
	heapSize = t;
	
	// 힙 배열 1번부터 저장 (0번째는 쓰지않음)
	while (!feof(fp)) {
		fscanf(fp, "%d", &t);
		cnt++;
		S[i++] = t;

		printf("%2d ", t);
	} printf("[cnt : %d]\n", cnt);

	// 힙 크기보다 큰 배열에 솔팅시 섞이지않도록 쓰레기값입력
	for (i = heapSize + 1; i < 100; i++)
		S[i] = 9999;

	// MakeHeap
	makeheap(heapSize);
	for (i = 1; i <= heapSize; i++)
		temp[i] = S[i];

	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[make heap후]\n");

	// RemoveKey (1번부터 root후 HeapSort배열에 따로 저장)
	removekeys();
	for (i = 1; i <= cnt; i++)
		printf("%2d ", heapSort[i]);
	printf("[heapSort 한 상태]\n");
	
	// root과정에서 heapSize가 줄어듦에따라 기존 Size로 복구
	heapSize = cnt;
	// 기존 힙 백업
	for (i = 1; i <= heapSize; i++)
		S[i] = temp[i];

	// 50 Insert
	insert(50);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[50을 insert한 상태]\n");

	// min값 삭제
	root();
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[min값을 삭제한 상태]\n");

	// 11 Insert
	insert(11);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[11을 insert한 상태]\n");

	// 1 Insert
	insert(1);
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[1을 insert한 상태]\n");

	// min 값 삭제
	root();
	for (i = 1; i <= heapSize; i++)
		printf("%2d ", S[i]);
	printf("[min값을 삭제한 상태]\n");

	return 0;
}