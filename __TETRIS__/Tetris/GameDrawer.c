/* GameDrawer.c */
#include "tetris.h"

// ���� �� ���
void PrintGameBoard() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {

			// ���󺸵�� ī�Ǹ� ��, ���� �ٸ��� �����ؼ� ���
			if (copyBoard[y][x] != realBoard[y][x]) {
				realBoard[y][x] = copyBoard[y][x];
				switch (realBoard[y][x]) {

				case EMPTY:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(" ");
					break;

				case MBLOCK:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case OVERLINE:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf(". ");
					break;

				case SBLOCK:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case WALL:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case FBLOCK:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;

				case EBLOCK:
					GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
					printf("��");
					break;
				}
				if (y == 2 && x != 0 && x != SIZE_X - 1 && copyBoard[y][x] == EMPTY)
					//���������� �������� �ٽ� �׸���
					copyBoard[y][x] = OVERLINE; 

			}
		}
	}
}

// ���� UI
void UIDrawer() {
	int x = 2, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

	GotoXY(2 + x, y); printf("[HOLD]"); // Hold ���ĭ
	GotoXY(x, 1 + y); printf("��");
	GotoXY(6 + x, 1 + y); printf("��");
	GotoXY(x, 6 + y); printf("��");
	GotoXY(6 + x, 6 + y); printf("��");

	GotoXY(23 + x, y); printf("[NEXT]"); // 1�� ���ĭ
	GotoXY(21 + x, 1 + y); printf("��");
	GotoXY(27 + x, 1 + y); printf("��");
	GotoXY(21 + x, 6 + y); printf("��");
	GotoXY(27 + x, 6 + y); printf("��");

	GotoXY(21 + x, 7 + y); printf("��"); // 2�� ���ĭ
	GotoXY(27 + x, 7 + y); printf("��");
	GotoXY(21 + x, 11 + y); printf("��");
	GotoXY(27 + x, 11 + y); printf("��");


	GotoXY(21 + x, 12 + y); printf("��"); // 3�� ���ĭ
	GotoXY(27 + x, 12 + y); printf("��");
	GotoXY(21 + x, 15 + y); printf("��");
	GotoXY(27 + x, 15 + y); printf("��");


	GotoXY(21 + x, 17 + y); printf(" [ BESTSCORE ]: ");
	GotoXY(21 + x, 19 + y); printf(" [ YOURSCORE ]: ");
	GotoXY(21 + x, 21 + y); printf(" [   LEVEL   ]: ");
	GotoXY(21 + x, 23 + y); printf(" [  DESTROY  ]: ");

	GotoXY(x + 5, 26 + y); printf("https://github.com/mollusca");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	GotoXY(x - 1, 8 + y); printf(" - HOW TO PLAY -  ");
	GotoXY(x - 1, 10 + y); printf("[����] :    MOVE  ");
	GotoXY(x - 1, 14 + y); printf("[��] :    ROTATE");
	GotoXY(x - 1, 12 + y); printf("[��] : SOFT DROP ");
	GotoXY(x - 1, 16 + y); printf("[SPC] :HARD DROP");
	GotoXY(x - 1, 18 + y); printf("[A] :       HOLD");
	GotoXY(x - 1, 20 + y); printf("[P] :      PAUSE");
	GotoXY(x - 1, 22 + y); printf("[ESC] :     EXIT");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// Ȧ�� �� ��� ����
void HoldBlockDrawer() {
	// Ȧ�带 ��������� ������ ����������
	if (holdOn == 0) 
		return;

	// Ȧ�� ��� �׸���
	for (int y = 0; y < 4; y++)	{
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeHold][0][y][x] == 1) {
				GotoXY(3 + x, 4 + y);
				printf("��");
			}
			else {
				GotoXY(3 + x, 4 + y);
				printf(" ");
			}
		}
	}
}

// ���� �� ��� ����
void NextBlockDrawer() {
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {

			// Next Block_1 �׸���
			if (blocks[block_typeNext_1][0][y][x] == 1) {

				GotoXY(24 + x, 4 + y);
				printf("��");
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				GotoXY(24 + x, 4 + y);
				printf(" ");
			}

			// Next Block_2 �׸���
			if (blocks[block_typeNext_2][0][y][x] == 1) {

				GotoXY(24 + x, 9 + y);
				printf("��");
			}
			else {

				GotoXY(24 + x, 9 + y);
				printf(" ");
			}

			// Next Block_3 �׸���
			if (blocks[block_typeNext_3][0][y][x] == 1) {
				GotoXY(24 + x, 14 + y);
				printf("��");
			}
			else {
				GotoXY(24 + x, 14 + y);
				printf(" ");
			}
		}
	}
}

// Pauseâ �׸���
void PauseDrawer() {
	HideDrawer(); // ���ӳ� ��� �� �����
	GotoXY(13, 14); printf("  [ PAUSE ]  ");
	GotoXY(11, 16); printf("  PRESS ANY BUTTON  ");

	EndPauseManager(); // ���� ����
	NextBlockDrawer();
	HoldBlockDrawer();

	GotoXY(13, 14); printf("                    ");
	GotoXY(11, 16); printf("                    ");

	ResetRealBoard();
}

// Introâ �׸���
void IntroDrawer() {
	int x = 5;
	int y = 2;

	GotoXY(x + 1, y + 0); printf("�١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١�");
	GotoXY(x + 1, y + 2); printf("  ����  ����  ����  ����    ����  ���� \n"); Sleep(20);
	GotoXY(x + 1, y + 3); printf("    ��    ��        ��    ��  ��      ��    ��      \n"); Sleep(20);
	GotoXY(x + 1, y + 4); printf("    ��    ����    ��    ����      ��    ����  \n"); Sleep(20);
	GotoXY(x + 1, y + 5); printf("    ��    ��        ��    ��  ��      ��        ��  \n"); Sleep(20);
	GotoXY(x + 1, y + 6); printf("    ��    ����    ��    ��    ��  ����  ����  \n"); Sleep(20);
	GotoXY(x + 1, y + 8); printf("�ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ١ڡ�");

	GotoXY(x + 1, y + 18); printf("--------------------- HOW_TO_PLAY --------------------");
	GotoXY(x + 1, y + 20); printf("[��] LEFT MOVE  [��] RIGHT MOVE  [SPC] HARD DROP");
	GotoXY(x + 1, y + 22); printf("[��] DOWN MOVE  [��] ROTATE      [A] HOLD");
	GotoXY(x + 1, y + 24); printf("------------------------------------------------------");
	
	GotoXY(x + 2, 26 + y); printf("https://github.com/mollusca");

	while (1) {
		if (_kbhit()) // �Է��� ���� �� ����
			break;
		GotoXY(x + 9, y + 13); printf("  >> PRESS ANY BUTTON << "); Sleep(200);
		GotoXY(x + 9, y + 13); printf("                         "); Sleep(200);
	}
	
	while (_kbhit()) // ���� �����
		_getch();

	system("cls"); // ȭ�� �����
}

// PAUSE, GAMEOVER ��Ȳ �� ȭ���� ��� ����
void HideDrawer() {
	// ���� ���� ������
	for (int y = 0; y < SIZE_Y - 1; y++) {
		for (int x = 1; x < SIZE_X - 1; x++) {
			GotoXY(x + SIZE_X_ADJ, y + SIZE_Y_ADJ);
			printf(" ");
		}
	}

	// Ȧ�� ��� ���� ������
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 6; x++) {
			GotoXY(3 + x, 4 + y);
			printf(" ");
		}
	}

	// 1�� ��� ���� ������
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 6; x++) {
			GotoXY(24 + x, 4 + y);
			printf(" ");
		}
	}

	// 2�� ��� ���� ������
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 6; x++) {
			GotoXY(24 + x, 10 + y);
			printf(" ");
		}
	}

	// 3�� ��� ���� ������
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 6; x++) {
			GotoXY(24 + x, 15 + y);
			printf(" ");
		}
	}
}

// Gameoverâ �׸���
void GameOverDrawer() {
	HideDrawer(); // ���� �� ��� ��� �����

	if (bestScoreFlag == 1)	{
		GotoXY(11, 12); printf(" �١� BestScore �ڡ�");
		bestScoreFlag = 0;
	}

	GotoXY(11, 14); printf("  [   GameOver  ] ");
	GotoXY(11, 16); printf("  PRESS ANY BUTTON ");

	EndPauseManager(); // ���� ����
	GotoXY(12, 12); printf("                     ");

	NextBlockDrawer(); // ������� �ٽ�ǥ��
	HoldBlockDrawer(); // Ȧ���� �ٽ�ǥ��

	GotoXY(11, 14); printf("                   ");
	GotoXY(11, 16); printf("                   ");
}

void WriteScore() {
	GotoXY(31, 19); printf("                   ");
	GotoXY(31, 21); printf("                   ");
	GotoXY(31, 23); printf("                   ");
	GotoXY(31, 25); printf("                   ");

	GotoXY(31, 19); printf("%d", bestScore);
	GotoXY(31, 21); printf("%d", yourScore);
	GotoXY(31, 23); printf("%d", game_level);
	GotoXY(31, 25); printf("%d", deleteline_cnt);
}

// ���� ���� ����
void GameEndDrawer() {
	for (int y = SIZE_Y; y > 0; y--) {
		Sleep(60);
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == FBLOCK)
				copyBoard[y][x] = EBLOCK;
		}
		PrintGameBoard();
		Sleep(20);
	}
	Sleep(200);
}