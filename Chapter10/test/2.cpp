#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

// ����ġ ����ü
struct fish {
	int r;
	int c;
	// ���� ������
	int size;
	// �� ������ ��� �Ծ�����
	int eat;
	// �̵��� �ð�
	int time;
};

int N;
int dr[4] = { -1, 0, 1, 0 };
int dc[4] = { 0, 1, 0, -1 };
int map[11][11];
int visited[11][11];

queue<fish> q;
vector<fish> v;

bool cmp(fish a, fish b) {
	// ���� ª�� �ð�
	if (a.time <= b.time) {
		// �ð��� ���� ���
		if (a.time == b.time) {
			// y���� �� ���� ����
			if (a.r <= b.r) {
				// y���� ���ٸ�
				if (a.r == b.r) {
					// x���� ���� ����
					if (a.c < b.c) {
						return true;
					}
					return false;
				}
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

void printMap() {
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			cout << map[r][c] << " ";
		}
		cout << endl;
	}
}

int main() {
	ifstream Data;
	char *fileName = (char *)malloc(sizeof(char) * 20);

	cin >> fileName;
	strcat(fileName, ".txt");
	Data.open(fileName);

	Data >> N;
	int x, y;
	Data >> x >> y;
	// ���� ����ġ�� ���¸� ����
	fish ex = { x - 1, y - 1, 2, 0, 0 };
	map[x - 1][y - 1] = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			Data >> map[r][c];
		}
	}
	printMap();

	// �ð� ����
	int ans = 0;
	while (1) {
		v.clear();
		memset(visited, 0, sizeof(visited));
		visited[ex.r][ex.c] = 1;
		q.push(ex);

		while (!q.empty()) {
			int r = q.front().r;
			int c = q.front().c;
			int size = q.front().size;
			int eat = q.front().eat;
			int time = q.front().time;
			q.pop();

			// 4�������� �˻縦 ����
			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
					// �� ����� ��ȿ�ϰ� �湮���� ���� ����
					if (!visited[nr][nc]) {
						// ����� ���� ����ġ�̰ų� ���� ���
						if (map[nr][nc] == 0 || map[nr][nc] == size) {
							// �湮 ó��
							visited[nr][nc] = 1;
							// �ð��� �߰��ϰ� ��� ���� ����ġ�� ã��
							q.push({ nr, nc, size, eat, time + 1 });
						}
						// ���� ���� ����ġ�� �ִٸ�
						else if (map[nr][nc] < size) {
							// �湮 ó��
							visited[nr][nc] = 1;
							// ��� ���� ����ġ�� �ð��� ǥ���ϰ� ���Ϳ� ���� ����
							v.push_back({ nr, nc, size, eat + 1, time + 1 });
						}
					}
				}
			}
		}

		// ��� ������ �ִ� ����ġ�� ����
		if (v.size() == 0) {
			break;
		}

		// cmp ���ǿ� ���� ����
		sort(v.begin(), v.end(), cmp);
		// ���� ����ġ�� ���ڰ� ���� ������� ���ٸ� ������ ����
		if (v[0].size == v[0].eat) {
			v[0].size++;
			v[0].eat = 0;
		}
		// ��� ���� ����ġ�� ����
		map[v[0].r][v[0].c] = 0;
		// ������ �ð��� ����
		ans += v[0].time;
		// �ð��� �ʱ�ȭ�ϰ� �ٽ� ť�� �־� ���� ������ �ݺ�
		ex = { v[0].r, v[0].c, v[0].size, v[0].eat, 0 };
	}

	cout << ans << endl;
	return 0;
}