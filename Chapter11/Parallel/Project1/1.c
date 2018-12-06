#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

// thanks to Knuth

using namespace std;


int arr[100][100];
int N;


void d1_row_sort_ab(int x)
{
	int temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = i % 2; j < N - 1; j += 2)
		{
			if (arr[x][j] > arr[x][j + 1])
			{
				temp = arr[x][j];

				arr[x][j] = arr[x][j + 1];
				arr[x][j + 1] = temp;
			}
		}
	}
}

void d1_row_sort_de(int x)
{
	int temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = i % 2; j < N - 1; j += 2)
		{
			if (arr[x][j] < arr[x][j + 1])
			{
				int temp = arr[x][j];

				arr[x][j] = arr[x][j + 1];
				arr[x][j + 1] = temp;
			}
		}
	}
}

void d1_col_sort_ab(int x)
{
	int temp;
	for (int i = 0; i < N; i++)
	{
		for (int j = i % 2; j < N - 1; j += 2)
		{
			if (arr[j][x] > arr[j + 1][x])
			{
				int temp = arr[j][x];

				arr[j][x] = arr[j + 1][x];
				arr[j + 1][x] = temp;
			}
		}
	}
}

void d2_sort_ab()
{
	int log2N = log10(N) / log10(2);

	for (int i = 0; i <= log2N; i++)
	{
		// 이리 저리 이리 저리
		for (int i = 0; i < N; i += 2)
			d1_row_sort_ab(i);
		for (int i = 1; i < N; i += 2)
			d1_row_sort_de(i);

		//열을 오름차순으로
		for (int i = 0; i < N; i++)
			d1_col_sort_ab(i);


	}

	//행 오름차순.
	for (int i = 0; i < N; i++)
		d1_row_sort_ab(i);
}

int main()
{
	fstream Data;
	string fileName;

	//cin >> fileName;

	Data.open("p3.txt");

	Data >> N;


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			Data >> arr[i][j];
	}

	d2_sort_ab();


	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout.width(3);
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	cin >> arr[0][0];
}