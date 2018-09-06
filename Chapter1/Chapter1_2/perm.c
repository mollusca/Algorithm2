/* Recursive Algorithm (Permutation on alphabet) + Quick Sort */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(char *a, char *b) {
	char temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void Partition(int low, int high, int pivotpoint, char *data) {
	int i, j;
	char pivotitem;

	j = low;
	pivotitem = data[low];

	for (i = low + 1; i <= high; i++) {
		if (data[i] < pivotitem) {
			j++;
			Swap(&data[i], &data[j]);
		}
	}
	pivotpoint = j;
	Swap(&data[low], &data[pivotpoint]);
}

void QuickSort(int low, int high, char *data) {
	int pivotpoint = low;

	if (low < high) {
		Partition(low, high, pivotpoint, data);
		QuickSort(low, pivotpoint - 1, data);
		QuickSort(pivotpoint + 1, high, data);
	}
}

void Print(int low, int high, char *data) {
	int i;

	for (i = 0; i <= high; i++)
		printf("%c", data[i]);
	printf("\n");
}

void perm(char *a, int k, int n) {
	int m;
	
	/* 종료조건 */
	if (n <= k) {
		Print(k, n, a);
		return;
	}

	/* 정렬->순열->섞인것 다시정렬 */
	QuickSort(k, n, a);
	perm(a, k + 1, n);
	QuickSort(k + 1, n, a);

	for (m = n; m >= k && a[k] < a[m]; m++) {
		Swap(&a[k], &a[m]);
		perm(a, k + 1, n);
		QuickSort(k + 1, n, a);
	}
}

int main() {
	char *arr = (char *)malloc(sizeof(char) * 100);

	scanf("%s", arr);
	perm(arr, 0, strlen(arr) - 1);

	free(arr);
	return 0;
}