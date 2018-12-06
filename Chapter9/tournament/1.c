#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int N, binCapa, objSize;
int LowExt, S, height;
int offset;
int pos;

double log2(double n) {
	return log10(n) / log10(2.0);
}

void Init(int *tree, int *player) {
	int k, p;

	if (N % 2 == 0) {
		for (k = 1; k <= N; k += 2) {
			if (k <= LowExt)
				p = (k + offset) / 2;
			else
				p = (k - LowExt + N - 1) / 2;

			tree[p] = k;
		}
	}
	else {
		for (k = 1; k <= LowExt; k += 2) {
			p = (k + offset) / 2;
			tree[p] = k;
		}
		for (k = LowExt + 2; k <= N; k += 2) {
			p = (k + offset - N) / 2;
			tree[p] = k;
		}
	}
	
	for (k = (N - 1) / 2; k > 0; k--)
		tree[k] = tree[k * 2];

	for (k = 1; k <= N; k++)
		player[k] = binCapa;
}

void rbt(int *tree, int *player, int idx) {
	while (idx != 1) {
		// 짝수
		if (idx % 2 == 0) {
			// leaf노드
			if (idx >= pos) {
				if (idx > offset) {
					if (player[idx - offset] >= player[idx - offset + 1])
						tree[idx / 2] = idx - offset;
					else
						tree[idx / 2] = idx - offset + 1;
				}
				else {
					if (player[idx - pos + LowExt + 1] >=
						player[idx - pos + LowExt + 2])
						tree[idx / 2] = idx - pos + LowExt + 1;
					else
						tree[idx / 2] = idx - pos + LowExt + 2;
				}
			}
			else {
				if (idx == pos - 1) {
					if (player[tree[idx]] >=
						player[idx - pos + LowExt + 2])
						tree[idx / 2] = tree[idx];
					else
						tree[idx / 2] = idx - pos + LowExt + 2;
				}
				else {
					if (player[tree[idx]] >= player[tree[idx + 1]])
						tree[idx / 2] = tree[idx];
					else
						tree[idx / 2] = tree[idx + 1];
				}
			}
		}
		// 홀수
		else {
			// leaf 노드
			if (idx >= pos) {
				if (idx > offset) {
					if (player[idx - offset - 1] >= player[idx - offset])
						tree[idx / 2] = idx - offset - 1;
					else
						tree[idx / 2] = idx - offset;
				}
				else {
					if (idx == pos) {
						if (player[tree[idx - pos + LowExt]] >=
							player[idx - pos + LowExt + 1])
							tree[idx / 2] = tree[idx - pos + LowExt - 1];
						else
							tree[idx / 2] = idx - pos + LowExt + 1;
					}
					else {
						if (player[idx - pos + LowExt] >=
							player[idx - pos + LowExt + 1])
							tree[idx / 2] = idx - pos + LowExt;
						else
							tree[idx / 2] = idx - pos + LowExt + 1;
					}
				}
			}
			// idx가 pos보다 작을때
			else {
				if (player[tree[idx - 1]] >= player[tree[idx]])
					tree[idx / 2] = tree[idx - 1];
				else
					tree[idx / 2] = tree[idx];
			}
		}
		
		idx /= 2;
	}
}

void binP(int *tree, int *player, int inp) {
	int idx = 1;

	while (1) {
		if (player[tree[idx]] >= inp) {
			// child로
			idx *= 2;

			if (pos <= idx && idx <= offset + LowExt) {
				if (idx <= offset) {
					if (player[idx - pos + LowExt + 1] >= inp)
						player[idx - pos + LowExt + 1] -= inp;
					else {
						player[idx - pos + LowExt + 2] -= inp;
						idx++;
					}
				}
				// LowExt 쪽
				else {
					if (player[idx - offset] >= inp)
						player[idx - offset] -= inp;
					else {
						player[idx - offset + 1] -= inp;
						idx++;
					}
				}
				rbt(tree, player, idx);
				break;
			}
		}
		else {
			idx++;
			if (idx == pos) {
				player[idx - pos + LowExt + 1] -= inp;
				rbt(tree, player, idx);
				break;
			}
		}
	}
}

void PrintTree(int *tree, int *player) {
	int i;
	
	printf("Tree : ");
	for (i = 1; i < N; i++)
		printf("%d ", tree[i]);
	printf("\n");
	printf("Player : ");
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

	height = ceil(log2(N));
	S = pow(2.0, height - 1);

	offset = 2 * S - 1;
	LowExt = 2 * ((N - 1) - (S - 1));
	pos = (offset + LowExt) / 2 + 1;

	printf("%d %d %d %d\n\n", height, S, offset, LowExt);

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