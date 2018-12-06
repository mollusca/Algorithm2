#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N, binCapa, objSize;

void Init(int *tree, int *player) {
	int k, p;

	for (k = 1; k <= N; k += 2) {
		p = (k + N - 1) / 2;
		tree[p] = k;
	}
	for (k = (N - 1) / 2; k > 0; k--)
		tree[k] = tree[k * 2];

	for (k = 1; k <= N; k++)
		player[k] = binCapa;
}

void binP(int *tree, int *player, int inp) {
	int idx = 1;

	// root부터
	while (1) {
		// leaf
		if ((N / 2 <= idx) && (idx <= N - 1)) {
			if (player[(idx - N / 2) * 2 + 1] >= inp)
				player[(idx - N / 2) * 2 + 1] -= inp;
			else if (player[(idx - N / 2) * 2 + 2] >= inp)
				player[(idx - N / 2) * 2 + 2] -= inp;
			// leaf 둘다 input보다 작으면 다음 bin
			else {
				idx++;
				continue;
			}

			// 왼쪽 child가 크거나 같으면
			if (player[(idx - N / 2) * 2 + 1] >= player[(idx - N / 2) * 2 + 2])
				// left
				tree[idx] = (idx - N / 2) * 2 + 1;
			else
				// right
				tree[idx] = (idx - N / 2) * 2 + 2;

			idx /= 2;

			while (idx != 0) {
				// 왼쪽 child player가 오른쪽 child보다 크면 나를 왼쪽 child값으로
				if (player[tree[idx * 2]] >= player[tree[idx * 2 + 1]])
					tree[idx] = tree[idx * 2];
				else
					tree[idx] = tree[idx * 2 + 1];

				idx /= 2;
			}

			break;
		}

		if (player[tree[idx]] >= inp)
			idx = idx * 2;
		else
			idx = idx * 2 + 1;
	}
}

void PrintTree(int *tree, int *player) {
	int i;
	printf("Tree : ");
	for (i = 1; i < N; i++)
		printf("%d ", tree[i]);

	printf("\nPlayer : ");
	for (i = 1; i <= N; i++)
		printf("%d ", player[i]);
	printf("\n");
}

int main() {
	int *tree, *player;
	int i, inp;
	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);

	// binCapacity input갯수 player갯수 순으로 input
	fscanf(fin, "%d %d %d", &binCapa, &objSize, &N);
	printf("%d %d %d\n", binCapa, objSize, N);

	// tree갯수는 무조건 player갯수보다 1개 작다.
	tree = (int *)malloc(sizeof(int) * N);
	player = (int *)malloc(sizeof(int) * (N + 1));

	Init(tree, player);
	PrintTree(tree, player);

	for (i = 0; i < objSize; i++) {
		fscanf(fin, "%d", &inp);

		binP(tree, player, inp);

		PrintTree(tree, player);
	}

	free(tree);
	free(player);

	fclose(fin);
	return 0;
}