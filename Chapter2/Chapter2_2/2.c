#include <stdio.h>
#include <stdlib.h>

typedef struct node* NodePointer;
typedef struct node {
	int vertex;
	int weight;
	NodePointer next;
} Node;

typedef struct graph* GraphPointer;
typedef struct graph {
	int numV;
	NodePointer* adjLists;
} Graph;

NodePointer createNode(int v, int w) {
	NodePointer newNode = (NodePointer)malloc(sizeof(Node));

	newNode->vertex = v;
	newNode->weight = w;
	newNode->next = NULL;

	return newNode;
}

GraphPointer createGraph(int v) {
	int i;
	GraphPointer graph = (GraphPointer)malloc(sizeof(Graph));
	
	graph->numV = v;
	graph->adjLists = (NodePointer *)malloc(sizeof(NodePointer) * v);

	for (i = 0; i < v; i++)
		graph->adjLists[i] = NULL;

	return graph;
}

void addEdge(GraphPointer graph, int f, int t, int w) {
	NodePointer newNode = createNode(t, w);

	newNode->next = graph->adjLists[f];

	graph->adjLists[f] = newNode;
}

void printgraph(GraphPointer graph) {
	int v;

	for (v = 1; v < graph->numV; v++) {
		NodePointer temp = graph->adjLists[v];
		
		while (temp) {
			printf("(%d %d) ", temp->vertex, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
}

int main() {
	// n : Á¤Á¡ÀÇ °¹¼ö / m : °¡ÁßÄ¡ °¹¼ö
	int n, m, i;
	// f : from / t : to / w : weight
	int f, t, w;

	FILE *fp;
	fp = fopen("input.txt", "r");
	
	fscanf(fp, "%d %d", &n, &m);

	GraphPointer graph = createGraph(n);

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d %d", &f, &t, &w);
		addEdge(graph, f, t, w);
	}
	printgraph(graph);
	return 0;
}