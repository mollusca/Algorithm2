#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

typedef struct { 
	int x; 
	int y; 
	int px; 
	int py; 
	int value; 
} heapNode; 

typedef struct { 
	heapNode* heap; 
	int size; 
} PQ; 

void insert(heapNode aNode, heapNode* heap, int size) { 
	int idx; 
	heapNode tmp; 

	idx = size + 1; 
	heap[idx] = aNode; 
	while (heap[idx].value < heap[idx/2].value && idx > 1) { 
		tmp = heap[idx]; 
		heap[idx] = heap[idx/2]; 
		heap[idx/2] = tmp; 
		idx /= 2; 
	} 
} 
void shiftdown(heapNode* heap, int size, int idx) { 
	int cidx; 
	heapNode tmp; 
	for (;;) { 
		cidx = idx*2; 
		if (cidx > size) { 
			break; 
		} 
		if (cidx < size) { 
			if (heap[cidx].value > heap[cidx+1].value) { 
				++cidx; 
			} 
		} 
		
		if (heap[cidx].value < heap[idx].value) { 
			tmp = heap[cidx]; 
			heap[cidx] = heap[idx]; 
			heap[idx] = tmp; 
			idx = cidx; 
		} 
		else { 
			break; 
		} 
	} 
} 
heapNode removeMin(heapNode* heap, int size) { 
	int cidx; 
	heapNode rv = heap[1]; 
	heap[1] = heap[size];
	--size; 
	
	shiftdown(heap, size, 1); 
	return rv; 
} 

void enqueue(heapNode node, PQ *q) { 
	insert(node, q->heap, q->size);
	++q->size;
}

heapNode dequeue(PQ *q) { 
	heapNode rv = removeMin(q->heap, q->size); 
	--q->size;
	return rv;
} 

void initQueue(PQ *q, int n) { 
	q->size = 0;
	q->heap = (heapNode*)malloc(sizeof(heapNode)*(n+1));
}

int **map;
int **visited_map;
int ***path;
int **change;
int N;

PQ q;
int DIR[4][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

void print_path(int x, int y) {
	int px = path[x][y][0];
	int py = path[x][y][1];

	if (px != 0 || py != 0) {
		print_path(px, py);
	}

	printf("%d, %d\n", py + 1, px + 1);
}

void dijikstra() {
	heapNode current;
	current.value = current.x = current.y = 0;
	enqueue(current, &q);

	while (q.size != 0) {
		int i, j, px = 0, py = 0;
		heapNode temp; current = dequeue(&q);

		if (visited_map[current.x][current.y] == 1)
			continue;

		visited_map[current.x][current.y] = 1;
		change[current.x][current.y] = current.value;
		path[current.x][current.y][0] = current.px;
		path[current.x][current.y][1] = current.py;
		for (i = 0; i < 4; ++i) {
			temp.x = current.x + DIR[i][0];
			temp.y = current.y + DIR[i][1];

			if (temp.x < 0 || temp.x >= N || temp.y < 0 || temp.y >= N)
				continue;
			if (visited_map[temp.x][temp.y] == 1)
				continue;
			temp.value = current.value;

			if (map[temp.x][temp.y] == 0)
				temp.value++;
			temp.px = current.x;
			temp.py = current.y;
			enqueue(temp, &q);
		}
	}
}

int main() { 
	FILE *file;
	char file_name[255]; 
	int i,j;
	
	scanf("%s", file_name); 
	file = fopen(file_name, "r"); 
	
	fscanf(file, "%d", &N); 
	initQueue(&q, N * N);
	
	map = (int **)malloc(sizeof(int *) * N); 
	path = (int ***)malloc(sizeof(int **) * N);
	
	visited_map = (int **)malloc(sizeof(int *) * N); 
	change = (int **)malloc(sizeof(int *) * N); 
	
	for(i = 0; i < N; ++i) {
		map[i] = (int *)malloc(sizeof(int) * N); 
		visited_map[i] = (int *)malloc(sizeof(int) * N);
		change[i] = (int *)malloc(sizeof(int) * N);
		path[i] = (int **)malloc(sizeof(int*) * N);
		
		for(j = 0; j < N; ) { 
			char c = fgetc(file); 
			
			if(c != '\n'){ 
				path[i][j] = (int *)malloc(sizeof(int) * 2);
				map[i][j] = c - '0'; 
				visited_map[i][j] = 0; 
				change[i][j] = 0; 
				j++; 
			}
		}
	}
	dijikstra(); 
	
	printf("%d\n", change[N - 1][N - 1]);
	print_path(N - 1, N - 1);
	printf("%d, %d\n", N, N);

	return 0; 
}

