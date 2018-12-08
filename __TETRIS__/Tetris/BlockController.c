/* BlockController.c */
#include "tetris.h"

// Ű����� ��Ʈ��
void KeyboardControl() {
	int key;
	
	if (_kbhit()) {
		key = _getch();

		//����Ű
		if (key == 224) {
			key = _getch();

			switch (key) {
			case LEFT: //���� �̵�
				if (CrushCheck(-1, 0, FALSE) == TRUE)
					BlockMove(-1, 0, FALSE);
				break;

			case RIGHT: // ������ �̵�
				if (CrushCheck(1, 0, FALSE) == TRUE)
					BlockMove(1, 0, FALSE);
				break;

			case UP: // �⺻ ȸ��(����)
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

			case DOWN: // ����Ʈ ���
				if (CrushCheck(0, 1, FALSE) == TRUE)
					BlockMove(0, 1, FALSE);
				break;

			}
		}
		else {
			switch (key) {
			case SPACE: // �ϵ� ���
				hardDropOn = 1;
				while (crushOn != 1)
					BlockDrop();
				break;

			case 'A': // Ȧ��
			case 'a':
				// Ȧ��Ȱ� ���� ��
				if (holdOn == 0) {
					block_typeHold = block_typeNow; // ������ Ȧ���Ͽ� ����
					NextBlocksPush(); // ������� 1ĭ�� �о���
					needNewOn = 1;
					MblockDeleter(); // ���� �����ִ� ���� ����� ������
					holdOn = 2;
					holdChanger = 1;
					break;
				}
				// Ȧ�� �� �� ������
				if (holdOn == 1) {
					int block_typeTemp;
					block_typeTemp = block_typeHold; // Ȧ�� ��ϰ� ������ ��ü
					block_typeHold = block_typeNow;
					block_typeNow = block_typeTemp;

					needNewOn = 1; // ��� �ʿ���·� ����
					MblockDeleter(); // ���� �����ִ� ���� ����� ������
					holdOn = 2; // Ȧ�� ��� �Ұ��� ���·� ����
					holdChanger = 1;
					break;
				}
				else
					break; 
				break;

			case 'P': // ����
			case 'p':
				PauseDrawer();
				break;

			case ESC: //ESC Ŭ��
				system("cls");
				GotoXY(14, 10); printf("** TETRIS TERMINATED **\n\n\n\n\n\n\n\n\n\n\n\n\n");
				exit(0); //�������� 
			}
		}
	}
}

// ��� �̵�, ȸ��
void BlockMove(int inputX, int inputY, int rotateCheck) {
	// ���� �ִ� �� �����
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y][block_X + x] = EMPTY;
		}
	}

	// ��� ȸ�� üũ
	if (rotateCheck == TRUE) {
		block_rotation++;
		// ȸ�� ����� ���� 3����
		if (block_rotation > 3)
			block_rotation = 0;
	}

	// �� �ٽ� �ֱ�
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y + inputY][block_X + x + inputX] = MBLOCK;
		}
	}

	block_X += inputX;
	block_Y += inputY;
}

// ��� ����
void BlockFix() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == MBLOCK)
				copyBoard[y][x] = FBLOCK;
		}
	}
	crushOn = 0; // �浹 üũ ����
	needNewOn = 1; // ���ο� ��� �ʿ� �÷��� �ѱ�
	yourScore += BONUS; // ���� ȹ��
	WriteScore(); // ���� ������ ǥ��

	if (holdOn == 2) // Ȧ��Ű�� ��� �Ұ� ���¶��
		holdOn = 1; // ��밡�� ���·� ����
	return;
}

// ��� �ϰ�
void BlockDrop() {
	// �浹 ������ ���� ������ �浹���� ����
	if (crushOn == 1 && CrushCheck(0, 1, FALSE) == TRUE) 
		crushOn = 0;

	// �浹 ������ �����ְ�, �浹��
	if (crushOn == 1 && CrushCheck(0, 1, FALSE) == FALSE) 
		BlockFix(); // ����� ������Ų��.

	if (CrushCheck(0, 1, FALSE) == TRUE)
		BlockMove(0, 1, FALSE);

	if (CrushCheck(0, 1, FALSE) == FALSE)
		crushOn = 1;
}
