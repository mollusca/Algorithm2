#include <stdio.h>
#include <stdlib.h>

int N, M;

void Init(int *parent, int N) {
	int i;
	for (i = 0; i < N; i++) {
		parent[i] = -1;
	}
}

int CollapsingFind(int *parent, int i) {
	int r, s;

	for (r = i; parent[r] >= 0; r = parent[r]);

	while (i != r) {
		s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}
void WeightedUnion(int *parent, int i, int j) {
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j]) {
		parent[i] = j;
		parent[j] = temp;
	}
	else {
		parent[j] = i;
		parent[i] = temp;
	}
}

int main() {
	int i, cnt = 0;
	int p, q, weight;
	int *parent;
	int n1, n2;	

	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);

	fscanf(fin, "%d %d", &N, &M);

	parent = (int *)malloc(sizeof(int) * (N + 1));
	Init(parent, N);

	for (i = 1; i < M; i++) {

		fscanf(fin, "%d %d %d", &p, &q, &weight);
		n1 = CollapsingFind(parent, p);
		n2 = CollapsingFind(parent, q);

		if (n1 != n2) {
			WeightedUnion(parent, n1, n2);
			printf("%2d %2d %2d\n", p, q, weight);
			cnt++;
		}
		if (cnt == N - 1)
			break;
	}

	fclose(fin);
	free(parent);
	return 0;
}