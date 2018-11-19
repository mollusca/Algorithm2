/* 12월 11일 화요일 16:30 ~ 18:00 // 장소 IT5 - 제일 큰 강의실 
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
	// leaf의 parent
	while ((index * 2) < N) {
		if (player[tree[index]] >= k)
			index *= 2;
		// 넘치면 brother로
		else
			index = (index / 2) * 2 + 1;
	}
	
	// 구한 leaf = tree[index]
	// 현재 값이 넘칠때 (2^n개라 else경우는 없음)
	if (player[tree[index]] < k) {
		if (index % 2 == 0)
			index++;
		else
			index--;
	}
	// leaf가 홀수 -> 왼쪽
	if (tree[index] % 2 == 1)
		player[tree[index]] -= k;
	else {
		// leaf가 오른쪽일때는 왼쪽에 들어갈수 있는지
		if (player[tree[index] - 1] >= k)
			player[tree[index] - 1] -= k;
		else
			player[tree[index]] -= k;
	}

	// update
	// 홀수
	if ((tree[index] % 2) == 1) {
		// left < right
		if (player[tree[index]] < player[tree[index] + 1])
			// brother 중에서 큰거 선택 / 같은경우는 그냥 왼쪽
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
	// 현재 parent구하기
	parent = (tree[index] + N - 1) / 2;
	tree[parent] = big;

	while (parent != 1) {
		// 현재 parent가 왼쪽일때
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