/* 피벗을 이용 퀵 소트
* + 피벗을 Randomized하게 설정
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Swap(int *a, int *b) {
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void Partition(int low, int high, int pivotpoint, int *data) {
	int i, j;
	int pivotitem;
//	srand((unsigned)time(NULL));

	j = low;
	pivotitem = data[low];

//	pivotpoint = rand() % (high - low + 1) + low;
//	Swap(&data[*pivotpoint], &data[low]);
//	Partition(low, high, &pivotpoint, data);

	for (i = low + 1; i <= high; i++) {
		if (data[i] < pivotitem) {
			j++;
			Swap(&data[i], &data[j]);
		}
	}
	pivotpoint = j;
	Swap(&data[low], &data[pivotpoint]);
}
/*
void rand_partition(int low, int high, int pivotpoint, int *data) {
	int i;
	srand((unsigned)time(NULL));

	i = rand() % (high - low + 1) + low;
	printf("%d\n", i);

	Swap(&data[low], &data[i]);
	Partition(low, high, pivotpoint, data);
}
*/
void QuickSort(int low, int high, int *data) {
	int pivotpoint = low;

	if (low < high) {
		Partition(low, high, pivotpoint, data);
		QuickSort(low, pivotpoint - 1, data);
		QuickSort(pivotpoint + 1, high, data);
	}
}

void Print(int low, int high, int *data) {
	int i;

	for (i = 0; i <= high; i++)
		printf("%d ", data[i]);
	printf("\n");
}

int main() {
	int arr[] = { 15, 22, 13, 27, 12, 10, 20, 25 };

	QuickSort(0, 7, arr);
	Print(0, 7, arr);

	return 0;
}