/* 12�� 11�� ȭ���� 16:30 ~ 18:00 // ��� IT5 - ���� ū ���ǽ� 
 * First Fit Bin Packing with Max Winner Tree
 * Player Number = 2^n
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// N: # of Player
int N, binCapacity, objSize;

void InitTree(int *tree, int *player) {
	int k, p;

	for (k = 1; k <= N; k += 2) {
		p = (k + N - 1) / 2;
		tree[p] = k;
	}
	for (k = (N - 1) / 2; k > 0; k--)
		tree[k] = tree[k * 2];

	for (k = 1; k <= N; k++)
		player[k] = binCapacity;
}

void binP(int *tree, int *player, int k) {
	int root, index, big, parent;

	index = 1;

	// insert
	// leaf�� parent
	while ((index * 2) < N) {
		if (player[tree[index]] >= k)
			index *= 2;
		// ��ġ�� brother��
		else
			index = (index / 2) * 2 + 1;
	}
	
	// ���� leaf = tree[index]
	// ���� ���� ��ĥ�� (2^n���� else���� ����)
	if (player[tree[index]] < k) {
		if (index % 2 == 0)
			index++;
		else
			index--;
	}
	// leaf�� Ȧ�� -> ����
	if (tree[index] % 2 == 1)
		player[tree[index]] -= k;
	else {
		// leaf�� �������϶��� ���ʿ� ���� �ִ���
		if (player[tree[index] - 1] >= k)
			player[tree[index] - 1] -= k;
		else
			player[tree[index]] -= k;
	}

	// update
	// Ȧ��
	if ((tree[index] % 2) == 1) {
		// left < right
		if (player[tree[index]] < player[tree[index] + 1])
			// brother �߿��� ū�� ���� / �������� �׳� ����
			big = tree[index] + 1;
		else
			big = tree[index];
	}
	else {
		if (player[tree[index] - 1] < player[tree[index]])
			big = tree[index];
		else
			big = tree[index] - 1;
	}
	// ���� parent���ϱ�
	parent = (tree[index] + N - 1) / 2;
	tree[parent] = big;

	while (parent != 1) {
		// ���� parent�� �����϶�
		if (parent % 2 == 0) {
			// left < right
			if (player[tree[parent]] < player[tree[parent + 1]])
				tree[parent / 2] = tree[parent + 1];
			else
				tree[parent / 2] = tree[parent];
		}
		else {
			// left < right
			if (player[tree[parent - 1]] < player[tree[parent]])
				tree[parent / 2] = tree[parent];
			else
				tree[parent / 2] = tree[parent - 1];
		}
		parent /= 2;
	}
}

void PrintTree(int *tree, int*player) {
	int i;

	printf("TREE : ");
	for (i = 1; i < N; i++)
		printf("%d ", tree[i]);

	printf("\nPLAYER : ");
	for (i = 1; i <= N; i++)
		printf("%d ", player[i]);
	printf("\n");
}
int main() {
	int i, k;
	int *tree, *player;
	
	char *filename = (char *)malloc(sizeof(char) * 20);
	scanf("%s", filename);
	strcat(filename, ".txt");
	FILE *fin = fopen(filename, "r");
	free(filename);

	fscanf(fin, "%d %d %d", &binCapacity, &objSize, &N);
	printf("%d %d %d\n", binCapacity, objSize, N);
	
	tree = (int *)malloc(sizeof(int) * N);
	player = (int *)malloc(sizeof(int) * (N + 1));

	InitTree(tree, player);
	PrintTree(tree, player);

	for (i = 1; i <= objSize; i++) {
		fscanf(fin, "%d", &k);

		binP(tree, player, k);
		PrintTree(tree, player);
	}

	free(tree);
	free(player);
	
	fclose(fin);
	return 0;
}