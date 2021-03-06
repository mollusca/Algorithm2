#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int N;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0 , -1 };
int map[11][11];
int visited[11][11];

Fish q[100];

int cmp(Fish a, Fish b) {
	// 제일 짧은시간
	if (a.time <= b.time) {
		if (a.time == b.time) {
			if (a.r <= b.r) {
				if(a.r == b.r) {
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
		q[]

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
	
	
	fclose(fin);
	return 0;
}