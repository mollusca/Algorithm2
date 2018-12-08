/* Main.c */
#include "tetris.h"

int main() {
	SetConsole();
	srand((unsigned)time(NULL));

	IntroDrawer();
	system("cls");

	ResetGame();
	NewBlockMaker();

	while (1) {
		LevelManager();
		
		if (holdChanger == 1)
			holdChanger = 0;

		for (int i = 0; i < 6; i++) {
			KeyboardControl();

			if (holdChanger == 1)
				break;

			ShadowBlockMaker();
			PrintGameBoard();
			Sleep(game_speed);

			if (hardDropOn == 1) {
				hardDropOn = 0;
				break;
			}

			ShadowBlockDeleter();
			// 충돌했어도 잠시동안 rotation할수있는 기회줌
			if (crushOn == 1 && CrushCheck(0, 1, FALSE) == FALSE)
				Sleep(50);
		}
		if (holdChanger == 0)
			BlockDrop();

		LineCheck();
		GameoverCheck();

		if (needNewOn == 1)
			NewBlockMaker();
	}
}