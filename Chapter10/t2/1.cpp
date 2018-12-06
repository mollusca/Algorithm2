#include <iostream>

using namespace std;

int n;
int mazzArr[105][105];
int visited[105][105];
//int clearWall[105][105];

int min(int a, int b, int c, int d)
{
	int minVal = a < b ? a : b;
	minVal = minVal < c ? minVal : c;
	minVal = minVal < d ? minVal : d;

	return minVal;
}

void dfs(int x, int y, int cnt)
{
	if (x >= n || x < 0)
		return;
	if (y >= n || y < 0)
		return;

	if (x >= n && y >= n)
		return;

	//cout << x << " " << y << " " << cnt << endl;

	if (mazzArr[y][x] == 0)
		cnt++;

	if (visited[y][x] == 0 || visited[y][x] > cnt)
	{
		visited[y][x] = cnt;
		dfs(x + 1, y, cnt);
		dfs(x - 1, y, cnt);
		dfs(x, y + 1, cnt);
		dfs(x, y - 1, cnt);
	}
}

int main()
{
	cin >> n;

	char tmp;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> tmp;
			mazzArr[i][j] = tmp - 48;
		}
	}

	dfs(0, 0, 1);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << visited[i][j] << " ";
		}
		cout << endl;
	}

	cout << visited[n - 1][n - 1] << endl;

	return 0;
}