#include <stdio.h>
#include <stdlib.h>

// N : ³ëµå °¹¼ö, M : ¿§Áö °¹¼ö
int N, M; 

typedef struct node* nodePointer;
typedef struct node {
	// ¸ñÀûÁö
	int num;
	// °¡ÁßÄ¡
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
	nodePointer find = vertex[from]->next;

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
		if(i != N)
			printf("%d : ", i);
		while (Print) {
			printf("(%d, %d) ", Print->num, Print->weight);
			Print = Print->node_next;
		}
		printf("\n");
	}
}

int main() {
	int i, f, t, w;
	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d %d", &N, &M);

	vertex = (frontPointer*)malloc(sizeof(Front*) * (N + 1));

	for (i = 0; i <= N; i++)
		vertex[i] = (frontPointer)malloc(sizeof(Front));
	for (i = 1; i <= N; i++) {
		vertex[i]->last = NULL;
		vertex[i]->next = NULL;
	}
	for (i = 0; i < M; i++) {
		fscanf(fp, "%d %d %d", &f, &t, &w);
		addEdge(f, t, w);
	}

	printList();

	return 0;
}