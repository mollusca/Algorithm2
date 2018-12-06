#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

// 개복치 구조체
struct fish {
	int r;
	int c;
	// 현재 사이즈
	int size;
	// 몇 마리를 잡아 먹었는지
	int eat;
	// 이동한 시간
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
	// 가장 짧은 시간
	if (a.time <= b.time) {
		// 시간이 같을 경우
		if (a.time == b.time) {
			// y값이 더 작은 순서
			if (a.r <= b.r) {
				// y값이 같다면
				if (a.r == b.r) {
					// x값이 작은 순서
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
	// 이전 개복치의 상태를 저장
	fish ex = { x - 1, y - 1, 2, 0, 0 };
	map[x - 1][y - 1] = 0;
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < N; c++) {
			Data >> map[r][c];
		}
	}
	printMap();

	// 시간 정보
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

			// 4방향으로 검사를 진행
			for (int i = 0; i < 4; i++) {
				int nr = r + dr[i];
				int nc = c + dc[i];
				if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
					// 맵 사이즈가 유효하고 방문하지 않은 지역
					if (!visited[nr][nc]) {
						// 사이즈가 같은 개복치이거나 길인 경우
						if (map[nr][nc] == 0 || map[nr][nc] == size) {
							// 방문 처리
							visited[nr][nc] = 1;
							// 시간만 추가하고 계속 작은 개복치를 찾음
							q.push({ nr, nc, size, eat, time + 1 });
						}
						// 만약 작은 개복치가 있다면
						else if (map[nr][nc] < size) {
							// 방문 처리
							visited[nr][nc] = 1;
							// 잡아 먹은 개복치와 시간을 표시하고 벡터에 따로 저장
							v.push_back({ nr, nc, size, eat + 1, time + 1 });
						}
					}
				}
			}
		}

		// 잡아 먹을수 있는 개복치가 없음
		if (v.size() == 0) {
			break;
		}

		// cmp 조건에 맞춰 정렬
		sort(v.begin(), v.end(), cmp);
		// 먹은 개복치의 숫자가 현재 사이즈와 같다면 사이즈 증가
		if (v[0].size == v[0].eat) {
			v[0].size++;
			v[0].eat = 0;
		}
		// 잡어 먹은 개복치를 지움
		map[v[0].r][v[0].c] = 0;
		// 움직인 시간을 저장
		ans += v[0].time;
		// 시간을 초기화하고 다시 큐에 넣어 이전 과정을 반복
		ex = { v[0].r, v[0].c, v[0].size, v[0].eat, 0 };
	}

	cout << ans << endl;
	return 0;
}