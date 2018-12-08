/* BlockDetect.c */
#include "tetris.h"

int CrushCheck(int blockX_ODJ, int blockY_ODJ, int blockR_ODJ) {
	int temp_blockRotation; // 임시 로테이션 테스트 값
	
	temp_blockRotation = block_rotation + blockR_ODJ;

	// 회전 경우의수 3번
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

// 라인 체크, 라인 지우기
void LineCheck() {
	int k;
	deleteline_combo = 0;
	int block_lineCheck;

	// Y 방향으로 이동
	for (int y = SIZE_Y - 2; y > 2;) {
		block_lineCheck = 0;
		// X 방향으로 이동
		for (int x = 1; x < SIZE_X - 1; x++) {
			// fix된 블럭이 있으면 값 증가
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
	// 라인 삭제로 점수획득
	DeleteScoreManager();
}

// 현재 이동중 블록을 찾아서 지우기
void MblockDeleter() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == MBLOCK)
				copyBoard[y][x] = EMPTY;
		}
	}
}

// 그림자 지우기
void ShadowBlockDeleter() {
	for (int y = 0; y < SIZE_Y; y++) {
		for (int x = 0; x < SIZE_X; x++) {
			if (copyBoard[y][x] == SBLOCK)
				copyBoard[y][x] = EMPTY;
		}
	}
}