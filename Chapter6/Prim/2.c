// MST_PRIM ALGORITHM 
/* 새로운애가 더좋으면 교체/ 아빠도 바까주기 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 99999999
#define FALSE 0
#define TRUE 1

typedef struct node* nodePointer;
typedef struct node {
	int num;
	int price;

	nodePointer next;
} Node;

typedef struct front* frontPointer;
typedef struct front {
	nodePointer next;
	nodePointer last;
} Front;

int N, M; // N: 노드갯수, M: 엣지갯수
int heapSize;
int p[1000]; // 부모
int d[1000]; // index값에 해당하는 노드와 연결된 값
int flag[1000];

frontPointer *vertex;
Node S[1000];
Node heapSort[1000];

void insertList(int from, int to, int price) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));
	nodePointer find = vertex[from]->next;

	temp->num = to;
	temp->next = NULL;
	temp->price = price;

	if (vertex[from]->next == NULL)
		vertex[from]->next = temp;

	else
		vertex[from]->last->next = temp;

	vertex[from]->last = temp;
}

void printList() {
	int i;

	for (i = 0; i <= N; i++) {
		nodePointer Print = vertex[i]->next;

		printf("%d : ", i);

		while (Print) {
			printf("(%d, %d) ", Print->num, Print->price);
			Print = Print->next;
		}
		printf("\n");
	}
}


void siftdown(int i) {
	Node siftkey = S[i];
	int parent = i;
	int smallerChild;

	while (2 * parent <= heapSize) {
		if ((2 * parent < heapSize) && (S[2 * parent].price < S[2 * parent + 1].price))
			smallerChild = 2 * parent;
		else
			smallerChild = 2 * parent + 1;

		if (siftkey.price > S[smallerChild].price) {
			S[parent] = S[smallerChild];
			parent = smallerChild;
		}
		else
			break;
	}
	S[parent] = siftkey;
}
/*
void makeheap(int n) {
	int i;

	for (i = n / 2; i >= 1; i--)
		siftdown(i);
}
*/
Node root() {
	Node keyout = S[1];
	int i;

	S[1] = S[heapSize];
	heapSize--;

	siftdown(1);

	return keyout;
}

void insertHeap(Node addNode) {
	heapSize++;
	int child = heapSize;
	int i;

	if (heapSize == 1)
		S[heapSize] = addNode;

	else {
		for (i = heapSize / 2; i >= 1; i = i / 2) {
			if (S[i].price > addNode.price) {
				S[child] = S[i];
				child = i;
			}
		}
		S[child] = addNode;
	}
}

void MST_PRIM(int r, int w) {
	int cnt = 0, v, i;

	for (i = 0; i < 1000; i++) {
		d[i] = MAX;
		flag[i] = FALSE;
	}

	d[r] = 0;
	p[r] = -1;

	Node temp;
	temp.num = 1;
	temp.price = 0;
	insertHeap(temp);

	while (heapSize > 0) {
		if (cnt == N - 1)
			break;
		Node u = root();

		if (flag[u.num] == FALSE) {
			nodePointer find = vertex[u.num]->next;

			while (find != NULL) {
				v = find->num;

				// 아빠도 교체
				if (flag[v] == FALSE && find->price < d[v]) {
					p[v] = u.num;
					d[v] = find->price;

					Node temp;
					temp.num = v;
					temp.price = d[v];
					insertHeap(temp);
				}
				find = find->next;
			}

			flag[u.num] = TRUE;
			cnt++;

			for (i = 1; i <= heapSize; i++)
				printf("%d ", S[i].price);
			printf("\n");

		}
	}
}
int main() {
	int i, from, to, price, sum = 0;

	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);

	fscanf(fin, "%d %d", &N, &M);

	vertex = (frontPointer *)malloc(sizeof(frontPointer) * (N + 1));
	for (i = 0; i <= N; i++) {
		vertex[i] = (frontPointer)malloc(sizeof(Front));
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;
	}
	for (i = 0; i <= M; i++) {
		fscanf(fin, "%d %d %d", &from, &to, &price);
		insertList(from, to, price);
		insertList(to, from, price);
	}
	printList();
	printf("\n");

	MST_PRIM(1, 0);

	printf("\nnearest : ");
	for (i = 2; i <= N; i++)
		printf("%d ", p[i]);

	for (i = 1; i <= N; i++)
		sum += d[i];
	printf("\nweight 합 : %d\np : ", sum);
	for (i = 1; i <= N; i++)
		printf("%d ", p[i]);
	printf("\n");

	fclose(fin);
	return 0;
}