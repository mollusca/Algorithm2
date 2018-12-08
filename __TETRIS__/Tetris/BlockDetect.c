/* BlockDetect.c */
#include "tetris.h"

int CrushCheck(int blockX_ODJ, int blockY_ODJ, int blockR_ODJ) {
	int temp_blockRotation; // �ӽ� �����̼� �׽�Ʈ ��
	
	temp_blockRotation = block_rotation + blockR_ODJ;

	// ȸ�� ����Ǽ� 3��
	if (temp_blockRotation > 3)
		temp_blockRotation = 0;

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][temp_blockRotation][y][x] == 1
				&& copyBoard[block_Y + blockY_ODJ + y][block_X + blockX_ODJ + x] > 3)
				return FALSE;
		}
	}
	return TRUE;
}

// ���� üũ, ���� �����
void LineCheck() {
	int k;
	deleteline_combo = 0;
	int block_lineCheck;

	// Y �������� �̵�
	for (int y = SIZE_Y - 2; y > 2;) {
		block_lineCheck = 0;
		// X �������� �̵�
		for (int x = 1; x < SIZE_X - 1; x++) {
			// fix�� ���� ������ �� ����
			if (copyBoard[y][x] == FBLOCK)
				block_lineCheck++;
		}
		if (block_lineCheck == SIZE_X - 2) {
			for (k = y; k > 1; k--) {
				for (int l = 1; l < SIZE_X - 1; l++) {
					if (copyBoard[k - 1][l] != OVERLINE)
						copyBoard[k][l] = copyBoard[k - 1][l];

					if (copyBoard[k - 1][l] == OVERLINE)
						copyBoard[k][l] = EMPTY;
				}
			}
			deleteline_cnt++;
			deleteline_combo++;
		}
		else
			y--;
	}
	// ���� ������ ����ȹ��
	DeleteScoreManager();
}

// ���� �̵��� ����� ã�Ƽ� �����
void MblockDeleter() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == MBLOCK)
				copyBoard[y][x] = EMPTY;
		}
	}
}

// �׸��� �����
void ShadowBlockDeleter() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == SBLOCK)
				copyBoard[y][x] = EMPTY;
		}
	}
}