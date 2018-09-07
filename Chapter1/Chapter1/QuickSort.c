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

void Print(int low, int high, int *data) {
	int i;

	for (i = 0; i <= high; i++)
		printf("%d ", data[i]);
	printf("\n");
}

void Partition(int low, int high, int *pivotpoint, int *data) {
	int i, j;
	int pivotitem;

	j = low;
	pivotitem = data[low];

	for (i = low + 1; i <= high; i++) {
		if (data[i] < pivotitem) {
			j++;
			Swap(&data[i], &data[j]);
//			Print(low, high, data);
		}
	}
	Swap(&data[j], &data[*pivotpoint]);
	*pivotpoint = j;
}

void QuickSort(int low, int high, int *data) {
	// 피벗포인트는 랜덤해도 여전히 첫번째 
	int pivotpoint = low;

	if (low < high) {
		int i = 0;
		srand((unsigned)time(NULL));

		i = rand() % (high - low + 1) + low;
//		printf("i : %d\n", i);
		// 랜덤한 피벗과 첫번째 데이터를 Swap
		Swap(&data[i], &data[low]);

		// pivotpoint 값을 유지시켜줘야 하므로 주소값으로 전달
		Partition(low, high, &pivotpoint, data);
		QuickSort(low, pivotpoint - 1, data);
		QuickSort(pivotpoint + 1, high, data);
	}
}

int main() {
	int arr[] = { 15, 22, 13, 27, 12, 10, 20, 25 };

	printf("Sorting 전\n");
	Print(0, 7, arr);
	QuickSort(0, 7, arr);
	printf("Sorting 후\n");
	Print(0, 7, arr);

	return 0;
}