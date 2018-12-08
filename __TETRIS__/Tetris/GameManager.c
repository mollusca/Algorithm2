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
	// ���������� ���� ����� �ִ��� üũ
	for (int y = 0; y < 3; y++) {
		for (int x = 1; x < SIZE_X - 2; x++) {

			// ���������� ���� ����� ����?
			if (copyBoard[y][x] == FBLOCK) {
				// ���� ���ھ ����Ʈ ���ھ �̱�?
				if (bestScore < yourScore) {
					bestScoreFlag = 1;
					
					FILE *data = fopen("BestScore.txt", "wt");
					// ���Ͽ� ������ �߸�
					if (data == 0) {
						GotoXY(0, 0);
						printf("������ ���忡 �����߽��ϴ�");
					}
					else {
						fprintf(data, "%d", yourScore);
						fclose(data);
					}

				}
				GameEndDrawer();
				GameOverDrawer(); // ���� ���� ȭ���� �׸�
				ResetGame(); // �����ʱ�ȭ
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
	for (int y = 0; y < SIZE_Y; y++) // �� ����
		for (int x = 0; x < SIZE_X; x++)
			copyBoard[y][x] = EMPTY;

	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			// ��-�� �� �׸���
			if (x == 0 || x == SIZE_X - 1) 
				copyBoard[y][x] = WALL;

			// �ϴ� �� �׸���
			if (y == SIZE_Y - 1) 
				copyBoard[y][x] = WALL;

			// ���� �������� �׸���
			if (y == 2 && x != 0 && x != SIZE_X - 1) 
				copyBoard[y][x] = OVERLINE;
		}
	}
}

void ResetGame() {
	ReadBestScore(); // ����Ʈ ���ھ� �ҷ���
	ResetBlocks(); // ��� �ʱ�ȭ
	ResetRealBoard(); // ���������� �ʱ�ȭ
	ResetCopyBoard();
	UIDrawer(); // UI

	holdOn = 0;
	yourScore = 0;
	deleteline_cnt = 0;
	game_level = 1;
	game_speed = 0;

	WriteScore(); // ���� ���� ǥ��
} 

// ���۸� ��
void EndPauseManager() {
	int garbage;

	Sleep(500);
	while (_kbhit())
		_getch();
	garbage = _getch();
} // PAUSE, QUIT ���� ����

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