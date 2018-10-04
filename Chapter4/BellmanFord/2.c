#include <stdio.h>
#include <stdio.h>

#define MAX 9999999

int p[1000]; // 방문하는 정비소 번호
int d[1000]; // 총 걸리는 시간
int length[1000]; // 정비소 사이 거리
int r[1000]; // 정비 시간

int maxLen; // 갈 수있는 최대 거리
int N; // 정비소 갯수
int cnt; // 방문 수

void BellmanFord() {
	int i, j;
	int temp; // 달린 거리
	
	for (i = 0; i <= N; i++) {
		temp = 0;
		for (j = i + 1; j <= N; j++) {
			temp += length[j];

			if (temp > maxLen)
				break;
			
			if (d[j] > d[i] + r[j]) {
				d[j] = d[i] + r[j];
				p[j] = i;
			}
		}
	}
}

// 정비소 순서 출력
void Print(int i) {
	if (i == 0 || i == -1)
		return;
	Print(p[i]);

	printf("%d ", i);
}

int main() {
	int i, t = N;
	FILE *fin = fopen("input.txt", "r");

	fscanf(fin, "%d", &maxLen);
	fscanf(fin, "%d", &N);

	// 초기화
	d[0] = 0;
	r[0] = 0;
	p[0] = -1;

	for (i = 1; i <= N; i++)
		d[i] = MAX;
	for (i = 1; i <= N + 1; i++)
		fscanf(fin, "%d", &length[i]);
	for (i = 1; i <= N + 1; i++)
		fscanf(fin, "%d", &r[i]);

	BellmanFord();

	for (i = 0; i <= N; i++)
		printf("%d ", d[i]);
	printf("\n\n");

	printf("%d\n", d[N]);
	
	t = N;
	while (1) {
		t = p[t];
		cnt++;

		if (t == 0 || t == -1)
			break;
	}
	printf("%d\n", cnt);
	
	Print(N);
	printf("\n");

	fclose(fin);
	return 0;
}