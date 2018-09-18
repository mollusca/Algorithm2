#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

// N : 노드 갯수, M : 엣지 갯수
int N, M;

int color[100]; // 방문 여부
int p[100]; // 부모

typedef struct node* nodePointer;
typedef struct node {
	// 목적지
	int num;
	// 가중치
	int weight;
	nodePointer node_next;
} Node;

typedef struct front* frontPointer;
typedef struct front {
	nodePointer next;
	nodePointer last;
} Front;

frontPointer* vertex;

void addEdge(int from, int to, int weight) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));

	temp->num = to;
	temp->weight = weight;
	temp->node_next = NULL;

	if (vertex[from]->next == NULL)
		vertex[from]->next = temp;
	else
		vertex[from]->last->node_next = temp;

	vertex[from]->last = temp;
}

void printList() {
	int i;

	for (i = 1; i <= N; i++) {
		nodePointer Print = vertex[i]->next;

		printf("%2d : ", i);
		while (Print) {
			printf("(%d) ", Print->num);
			//			printf("(%2d, %2d) ", Print->num, Print->weight);
			Print = Print->node_next;
		}
		printf("\n");
	}
}

void DFS_visit(int u) {
	color[u] = GRAY;
	nodePointer temp = vertex[u]->next;

	while (temp) {
		if (color[temp->num] == WHITE) {
			p[temp->num] = u;
			DFS_visit(temp->num);
		}
		temp = temp->node_next;
	}
	color[u] = BLACK;
}

void DFS() {
	int u;
	for (u = 1; u <= N; u++) {
		color[u] = WHITE;
		p[u] = -1; // NIL
	}
	for (u = 1; u <= N; u++)
		if (color[u] == WHITE)
			DFS_visit(u);
}

int main() {
	int i, f, t;
	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d %d", &N, &M);

	vertex = (frontPointer*)malloc(sizeof(Front*) * (N + 1));

	for (i = 1; i <= N; i++) {
		vertex[i] = (frontPointer)malloc(sizeof(Front));
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;
	}
	for (i = 0; i < M; i++) {
		fscanf(fp, "%d %d", &f, &t);
		addEdge(f, t, 0);
	}

	DFS();

	printList();

	// DFS 출력
	printf("\ndfs p[i] : ");
	for (i = 1; i <= N; i++)
		printf("%d ", p[i]);
	printf("\n");

	return 0;
}