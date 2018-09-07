/* �ǹ��� �̿� �� ��Ʈ
* + �ǹ��� Randomized�ϰ� ����
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
	// �ǹ�����Ʈ�� �����ص� ������ ù��° 
	int pivotpoint = low;

	if (low < high) {
		int i = 0;
		srand((unsigned)time(NULL));

		i = rand() % (high - low + 1) + low;
//		printf("i : %d\n", i);
		// ������ �ǹ��� ù��° �����͸� Swap
		Swap(&data[i], &data[low]);

		// pivotpoint ���� ����������� �ϹǷ� �ּҰ����� ����
		Partition(low, high, &pivotpoint, data);
		QuickSort(low, pivotpoint - 1, data);
		QuickSort(pivotpoint + 1, high, data);
	}
}

int main() {
	int arr[] = { 15, 22, 13, 27, 12, 10, 20, 25 };

	printf("Sorting ��\n");
	Print(0, 7, arr);
	QuickSort(0, 7, arr);
	printf("Sorting ��\n");
	Print(0, 7, arr);

	return 0;
}