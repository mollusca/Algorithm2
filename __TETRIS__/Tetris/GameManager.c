/* GameManager.c */
#include "tetris.h"

void ReadBestScore() {
	FILE *data = fopen("BestScore.txt", "rt");
	if (data == 0)
		bestScore = 0;
	else {
		fscanf(data, "%d", &bestScore);
		fclose(data);
	}
}

void GameoverCheck() {
	// 오버라인을 넘은 블록이 있는지 체크
	for (int y = 0; y < 3; y++) {
		for (int x = 1; x < SIZE_X - 2; x++) {

			// 오버라인을 넘은 블록이 있음?
			if (copyBoard[y][x] == FBLOCK) {
				// 현재 스코어가 베스트 스코어를 이김?
				if (bestScore < yourScore) {
					bestScoreFlag = 1;
					
					FILE *data = fopen("BestScore.txt", "wt");
					// 파일에 에러가 뜨면
					if (data == 0) {
						GotoXY(0, 0);
						printf("데이터 저장에 실패했습니다");
					}
					else {
						fprintf(data, "%d", yourScore);
						fclose(data);
					}

				}
				GameEndDrawer();
				GameOverDrawer(); // 게임 오버 화면을 그림
				ResetGame(); // 게임초기화
			}
		}
	}
	return;
}

void ResetRealBoard() {
	for (int y = 0; y < SIZE_Y; y++)
		for (int x = 0; x < SIZE_X; x++)
			realBoard[y][x] = 10000;
}

void ResetCopyBoard() {
	for (int y = 0; y < SIZE_Y; y++) // 빈 공간
		for (int x = 0; x < SIZE_X; x++)
			copyBoard[y][x] = EMPTY;

	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			// 좌-우 벽 그리기
			if (x == 0 || x == SIZE_X - 1) 
				copyBoard[y][x] = WALL;

			// 하단 벽 그리기
			if (y == SIZE_Y - 1) 
				copyBoard[y][x] = WALL;

			// 게임 오버라인 그리기
			if (y == 2 && x != 0 && x != SIZE_X - 1) 
				copyBoard[y][x] = OVERLINE;
		}
	}
}

void ResetGame() {
	ReadBestScore(); // 베스트 스코어 불러옴
	ResetBlocks(); // 블록 초기화
	ResetRealBoard(); // 실제게임판 초기화
	ResetCopyBoard();
	UIDrawer(); // UI

	holdOn = 0;
	yourScore = 0;
	deleteline_cnt = 0;
	game_level = 1;
	game_speed = 0;

	WriteScore(); // 게임 점수 표시
} 

// 버퍼를 줌
void EndPauseManager() {
	int garbage;

	Sleep(500);
	while (_kbhit())
		_getch();
	garbage = _getch();
} // PAUSE, QUIT 버퍼 비우기

void LevelManager() {
	if (deleteline_cnt < 10) {
		game_level = 1;
		game_speed = 75;
		return;
	}

	else if (deleteline_cnt < 20) {
		game_level = 2;
		game_speed = 45;
		return;
	}

	else if (deleteline_cnt < 30) {
		game_level = 3;
		game_speed = 35;
		return;
	}

	else if (deleteline_cnt < 40) {
		game_level = 4;
		game_speed = 30;
		return;
	}

	else if (deleteline_cnt < 50) {
		game_level = 5;
		game_speed = 25;
		return;
	}

	else if (deleteline_cnt < 60) {
		game_level = 15;
		game_speed = 20;
		return;
	}

	else if (deleteline_cnt < 70) {
		game_level = 10;
		game_speed = 15;
		return;
	}

	else {
		game_level = 5;
		game_speed = 10;
		return;
	}
}

void DeleteScoreManager() {
	if (deleteline_combo == 1)
		yourScore += 50;

	if (deleteline_combo == 2) {
		yourScore += 150;
		GotoXY(13, 26); printf("* %d C O M B O! *", deleteline_combo); Sleep(400);
		GotoXY(13, 26); printf("                 ");
	}

	if (deleteline_combo == 3) {
		yourScore += 300;
		GotoXY(13, 26); printf("* %d C O M B O! *", deleteline_combo); Sleep(400);
		GotoXY(13, 26); printf("                 ");
	}

	if (deleteline_combo == 4) {
		yourScore += 1000;
		GotoXY(13, 26); printf("* %d C O M B O! *", deleteline_combo); Sleep(400);
		GotoXY(13, 26); printf("                 ");
	}
}