#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int a[100][100];
int N;

void row_sort_a(int x) {
	int temp, i, j;

	for (i = 0; i < N; i++) {
		for (j = i % 2; j < N - 1; j += 2) {
			if (a[x][j] > a[x][j + 1]) {
				temp = a[x][j];

				a[x][j] = a[x][j + 1];
				a[x][j + 1] = temp;
			}
		}
	}
}

void row_sort_b(int x) {
	int temp, i, j;

	for (i = 0; i < N; i++) {
		for (j = i % 2; j < N - 1; j += 2) {
			if (a[x][j] < a[x][j + 1]) {
				temp = a[x][j];

				a[x][j] = a[x][j + 1];
				a[x][j + 1] = temp;
			}
		}
	}
}
void col_sort(int x) {
	int temp, i, j;

	for (i = 0; i < N; i++) {
		for (j = i % 2; j < N - 1; j += 2) {
			if (a[j][x] > a[j + 1][x]) {
				temp = a[j][x];
				a[j][x] = a[j + 1][x];
				a[j + 1][x] = temp;
			}
		}
	}
}

void sort() {
	int i, j, k, l;
	int log2N = log10(N) / log10(2);

	for (i = 0; i <= log2N; i++) {
		for (j = 0; j < N; j += 2)
			row_sort_a(j);
		for (k = 1; k < N; k += 2)
			row_sort_b(k);
		
		for (l = 0; l < N; l++)
			col_sort(l);
	}
	for (i = 0; i < N; i++)
		row_sort_a(i);
}

int main() {
	int i, j;
	
	char *fileName = (char *)malloc(sizeof(char) * 20);
	scanf("%s", fileName);
	strcat(fileName, ".txt");

	FILE *fin = fopen(fileName, "r");
	free(fileName);

	fscanf(fin, "%d", &N);
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fscanf(fin, "%d", &a[i][j]);
		}
	}
	sort();

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			printf("%3d ", a[i][j]);
		}
		printf("\n");
	}

	fclose(fin);
	return 0;
}