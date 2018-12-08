/* BlockController.c */
#include "tetris.h"

// 키보드로 컨트롤
void KeyboardControl() {
	int key;
	
	if (_kbhit()) {
		key = _getch();

		//방향키
		if (key == 224) {
			key = _getch();

			switch (key) {
			case LEFT: //왼쪽 이동
				if (CrushCheck(-1, 0, FALSE) == TRUE)
					BlockMove(-1, 0, FALSE);
				break;

			case RIGHT: // 오른쪽 이동
				if (CrushCheck(1, 0, FALSE) == TRUE)
					BlockMove(1, 0, FALSE);
				break;

			case UP: // 기본 회전(왼쪽)
				for (int rotatemove_y = 0;; rotatemove_y--) {
					for (int rotatemove_x = 0; rotatemove_x < 3; rotatemove_x++) {
						for (int n = 0; n < 2; n++) {
							rotatemove_x *= -1;

							if (CrushCheck(rotatemove_x, rotatemove_y, TRUE) == TRUE) {
								BlockMove(rotatemove_x, rotatemove_y, TRUE);
								return;
							}
						}
					}
				}

			case DOWN: // 소프트 드롭
				if (CrushCheck(0, 1, FALSE) == TRUE)
					BlockMove(0, 1, FALSE);
				break;

			}
		}
		else {
			switch (key) {
			case SPACE: // 하드 드롭
				hardDropOn = 1;
				while (crushOn != 1)
					BlockDrop();
				break;

			case 'A': // 홀드
			case 'a':
				// 홀드된거 없을 때
				if (holdOn == 0) {
					block_typeHold = block_typeNow; // 현재블록 홀드블록에 저장
					NextBlocksPush(); // 다음블록 1칸씩 밀어줌
					needNewOn = 1;
					MblockDeleter(); // 현재 나와있는 무브 블록을 지워줌
					holdOn = 2;
					holdChanger = 1;
					break;
				}
				// 홀드 된 거 있을때
				if (holdOn == 1) {
					int block_typeTemp;
					block_typeTemp = block_typeHold; // 홀드 블록과 현재블록 교체
					block_typeHold = block_typeNow;
					block_typeNow = block_typeTemp;

					needNewOn = 1; // 블록 필요상태로 변경
					MblockDeleter(); // 현재 나와있는 무브 블록을 지워줌
					holdOn = 2; // 홀드 사용 불가능 상태로 변경
					holdChanger = 1;
					break;
				}
				else
					break; 
				break;

			case 'P': // 퍼즈
			case 'p':
				PauseDrawer();
				break;

			case ESC: //ESC 클릭
				system("cls");
				GotoXY(14, 10); printf("** TETRIS TERMINATED **\n\n\n\n\n\n\n\n\n\n\n\n\n");
				exit(0); //게임종료 
			}
		}
	}
}

// 블록 이동, 회전
void BlockMove(int inputX, int inputY, int rotateCheck) {
	// 원래 있던 값 지우기
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y][block_X + x] = EMPTY;
		}
	}

	// 블록 회전 체크
	if (rotateCheck == TRUE) {
		block_rotation++;
		// 회전 경우의 수는 3개임
		if (block_rotation > 3)
			block_rotation = 0;
	}

	// 값 다시 넣기
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;
		}
	}

	block_X += inputX;
	block_Y += inputY;
}

// 블록 고정
void BlockFix() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == MBLOCK)
				copyBoard[y][x] = FBLOCK;
		}
	}
	crushOn = 0; // 충돌 체크 끄기
	needNewOn = 1; // 새로운 블록 필요 플래그 켜기
	yourScore += BONUS; // 점수 획득
	WriteScore(); // 게임 점수를 표시

	if (holdOn == 2) // 홀드키가 사용 불가 상태라면
		holdOn = 1; // 사용가능 상태로 변경
	return;
}

// 블록 하강
void BlockDrop() {
	// 충돌 판정이 켜져 있지만 충돌하지 않음
	if (crushOn == 1 && CrushCheck(0, 1, FALSE) == TRUE) 
		crushOn = 0;

	// 충돌 판정이 켜져있고, 충돌됨
	if (crushOn == 1 && CrushCheck(0, 1, FALSE) == FALSE) 
		BlockFix(); // 블록을 고정시킨다.

	if (CrushCheck(0, 1, FALSE) == TRUE)
		BlockMove(0, 1, FALSE);

	if (CrushCheck(0, 1, FALSE) == FALSE)
		crushOn = 1;
}
