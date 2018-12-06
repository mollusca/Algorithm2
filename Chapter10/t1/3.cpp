#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

#define TRUE 1
#define FALSE 0

typedef struct fish *fishPointer;
typedef struct fish {
	int r; // y
	int c; // x

	int size;
	int eat;
	int time;
	fishPointer next;
} Fish;

typedef struct queue *queuePointer;
typedef struct queue {
	fishPointer front;
	fishPointer tail;
}Queue;

void QueueInit(queuePointer root) {
	root->front = NULL;
	root->tail = NULL;
}

int isEmpty(queuePointer root) {
	if (root->front == NULL)
		return TRUE;
	return FALSE;
}

void enQueue(queuePointer root, Fish ex) {
	fishPointer newNode = (fishPointer)malloc(sizeof(Fish));

	newNode->next = NULL;
	newNode->r = ex.r;
	newNode->c = ex.c;
	newNode->size = ex.size;
	newNode->eat = ex.eat;
	newNode->time = ex.time;

	if (isEmpty(root)) {
		root->front = newNode;
		root->tail = newNode;
	}
	else {
		root->tail->next = newNode;
		root->tail = newNode;
	}
}

Fish deQueue(queuePointer root) {
	fishPointer dequeue_node;
	Fish output;

	if (isEmpty(root)) {
		printf("Queue is Empty \n");
		exit(-1);
	}
	dequeue_node = root->front;
	output.r = dequeue_node->r;
	output.c = dequeue_node->c;
	output.size = dequeue_node->size;
	output.eat = dequeue_node->eat;
	output.time = dequeue_node->time;

	// 마지막 한개의 노드가 dequeue가 될때.
	if (root->front->next == NULL) {
		root->front = NULL;
		root->tail = NULL;

		free(dequeue_node);
		return output;
	}
	root->front = dequeue_node->next;

	free(dequeue_node);

	return output;
}

int getFront(queuePointer root) {
	return root->front->time;
}

int N;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0 , -1 };
int map[11][11];
int visited[11][11];

Queue q;
std::vector<fish> v;

int cmp(Fish a, Fish b) {
	// 제일 짧은시간
	if (a.time <= b.time) {
		if (a.time == b.time) {
			if (a.r <= b.r) {
				if (a.r == b.r) {
					if (a.c < b.c) {
						return TRUE;
					}
					return FALSE;
				}
				return TRUE;
			}
			return FALSE;
		}
		return TRUE;
	}
	return FALSE;
}

void printMap() {
	int r, c;
	for (r = 0; r < N; r++) {
		for (c = 0; c < N; c++) {
			printf("%d ", map[r][c]);
		}
		printf("\n");
	}
}
Fish setting(int r, int c, int size, int eat, int time) {
	Fish f;
	f.r = r;
	f.c = c;
	f.size = size;
	f.eat = eat;
	f.time = time;

	return f;
}

int main() {
	int r, c, i;

	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);
	fscanf(fin, "%d", &N);

	Fish ex;
	for (r = 0; r < N; r++) {
		for (c = 0; c < N; c++) {
			fscanf(fin, "%d", &(map[r][c]));

			if (map[r][c] == 9) {
				map[r][c] = 0;
				ex.r = r;
				ex.c = c;
				ex.size = 2;
				ex.eat = 0;
				ex.time = 0;
			}
		}
	}
	printMap();

	// 시간
	int ans = 0;
	while (1) {
		v.clear();
		memset(visited, 0, sizeof(visited));
		visited[ex.r][ex.c] = 1;
		enQueue(&q, ex);

		while (!isEmpty(&q)) {
			Fish pop = deQueue(&q);

			for (i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];

				if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
					if (!visited[nr][nc]) {
						if (map[nr][nc] == 0 || map[nr][nc] == pop.size) {
							visited[nr][nc] = 1;
							Fish inp = setting(nr, nc, pop.size, pop.eat, pop.time + 1);
							enQueue(&q, inp);
						}
						else if (map[nr][nc] < pop.size) {
							visited[nr][nc] = 1;

						}
					}
				}
			}
		}
		if (v.size() == 0) {
			break;
		}

		sort(v.begin(), v.end(), cmp);

		if (v[0].size == v[0].eat) {
			v[0].size++;
			v[0].eat = 0;
		}

		map[v[0].r][v[0].c] = 0;
		ans += v[0].time;
		ex = setting(v[0].r, v[0].c, v[0].size, v[0].eat, 0);
	}

	printf("%d\n", ans);
	fclose(fin);
	return 0;
}