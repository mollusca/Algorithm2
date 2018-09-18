#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct node* nodePointer;
typedef struct node {
	// 목적지
	int num;
	// 가중치
	int price;

	int height;
	int weight_top;
	int size;

	nodePointer node_next;
} Node;

typedef struct front* frontPointer;
typedef struct front {
	nodePointer next;
	nodePointer last;

	int size;
	int height;
	int weight;
} Front;

frontPointer* vertex;
nodePointer head = NULL;
// N : 노드 갯수
int N;

int color[1000]; // 방문 여부
int p[1000]; // 부모
int bottom[1000], height[1000], weight[1000];

int topo[1000], cnt_topo;
int before[1000];
int dp[1000];

int blockNum;

void addEdge(int from, int to, int weight_) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));

	temp->num = to;
	temp->node_next = NULL;
	temp->price = weight_;

	temp->height = weight_;
	temp->weight_top = weight[to];
	temp->size = bottom[to];

	if (from == 0) {
		temp->height = 0;
		temp->size = 0;
		temp->price = 0;
	}
	if (from == N + 1) {
		temp->height = 0;
		temp->size = 0;
		temp->price = 0;
	}

	if (vertex[from]->next == NULL)
		vertex[from]->next = temp;
	else
		vertex[from]->last->node_next = temp;

	vertex[from]->last = temp;
}

void printList() {
	int i;

	for (i = 0; i <= N + 1; i++) {
		nodePointer Print = vertex[i]->next;

		printf("%d : ", i);

		while (Print) {
			printf("(%d, %d) ", Print->num, Print->weight_top);
			Print = Print->node_next;
		}
		printf("\n");
	}
}

void insertLink(int data) {
	nodePointer temp = (nodePointer)malloc(sizeof(Node));

	temp->num = data;
	temp->node_next = NULL;

	if (head == NULL)
		head = temp;
	else {
		temp->node_next = head;
		head = temp;
	}
}

void PrintLinked() {
	nodePointer find = head;

	while (find) {
		printf("%d ", find->num);
		find = find->node_next;
	}
	printf("\n");
}

void doTopo() {
	nodePointer find = head;
	while (find) {
		topo[cnt_topo++] = find->num;
		before[find->num] = cnt_topo - 1;
		find = find->node_next;
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

	insertLink(u);
}

void DFS() {
	int u;
	for (u = 0; u <= N; u++) {
		color[u] = WHITE;
		p[u] = -1; // NIL
	}
	for (u = 0; u <= N; u++)
		if (color[u] == WHITE)
			DFS_visit(u);
}

void topologiSort() {
	int i, j;
	
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			if (bottom[i] > bottom[j] && weight[i] > weight[j]) {
				addEdge(i, j, height[j]);
			}
		}
	}
}

int main() {
	int i, j, x;
	FILE *fp = fopen("input3.txt", "r");
	FILE *fout = fopen("output.txt", "w");

	fscanf(fp, "%d", &N);

	vertex = (frontPointer*)malloc(sizeof(Front*) * (N + 2));

	for (i = 0; i <= N + 1; i++)
		vertex[i] = (frontPointer)malloc(sizeof(Front));

	dp[0] = 0;
	for (i = 1; i <= N + 1; i++)
	{
		dp[i] = -987654321;
	}

	for (i = 1; i <= N + 1; i++)
		fscanf(fp, "%d %d %d", &bottom[i], &height[i], &weight[i]);

	for (i = 0; i <= N + 1; i++) {
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;

		vertex[i]->size = bottom[i];
		vertex[i]->height = height[i];
		vertex[i]->weight = weight[i];
		
		color[i] = WHITE;
		p[i] = -1;
	}
	vertex[0]->size = 99999;
	vertex[0]->height = 0;
	vertex[0]->weight = 99999;

	topologiSort();

	for (i = 1; i <= N; i++) {
		addEdge(0, i, height[i]);
		addEdge(i, N + 1, 0);
	}

	DFS();
	PrintLinked();
	printf("\n");
//	printList();

	doTopo();

	for (i = 0; i <= N; i++) {
		frontPointer left = vertex[topo[i]];

		for (j = i + 1; j <= N + 1; j++) {
			frontPointer right = vertex[topo[j]];

			if ((left->weight > right->weight) && (left->size > right->size)) {
				if (dp[j] < dp[i] + right->height) {
					dp[j] = dp[i] + right->height;
					p[topo[j]] = topo[i];
				}
			}
		}
	}

	x = N + 1;

	while (p[x] != 0) {
		blockNum++;
		x = p[x];
	}
	x = N + 1;

	fprintf(fout, "\n블럭갯수 : %d \n", blockNum);

	while (p[x] != 0) {
		fprintf(fout, "%d\n", p[x]);
		x = p[x];
	}

/*
	for (i = 0; i <= N + 1; i++) {
		printf("%d ", dp[i]);
	}
	printf("\n");

	printf("%d \n", dp[N + 1]);
*/
	fclose(fp);
	fclose(fout);

	return 0;
}