/* BlockMaker.c */
#include "tetris.h"

// [블록종류][회전][세로][가로]
blocks[7][4][4][4] = {
	// J미노(0번 블록)
	{
		0,0,0,0,
		0,1,0,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,1,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,0,1,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,1,1,0
	},
	// L미노(1번 블록)
	{
		0,0,0,0,
		0,0,0,1,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,1,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,1,0,0,

		0,0,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,1,0
	},
	// O미노(2번 블록)
	{
		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0,

		0,0,0,0,
		0,1,1,0,
		0,1,1,0,
		0,0,0,0
	},
	// T미노(3번 블록)
	{
		0,0,0,0,
		0,0,1,0,
		0,1,1,1,
		0,0,0,0,

		0,0,0,0,
		0,0,1,0,
		0,0,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,0,0,
		0,1,1,1,
		0,0,1,0,

		0,0,0,0,
		0,0,1,0,
		0,1,1,0,
		0,0,1,0
	},
	// I미노(4번 블록)
	{
		0,0,0,0,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,

		0,0,1,0,
		0,0,1,0,
		0,0,1,0,
		0,0,1,0,

		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,0,0,
		0,1,0,0,
		0,1,0,0
	},
	// Z미노(5번 블록)
	{
		0,0,0,0,
		0,1,1,0,
		0,0,1,1,
		0,0,0,0,

		0,0,0,1,
		0,0,1,1,
		0,0,1,0,
		0,0,0,0,

		0,1,1,0,
		0,0,1,1,
		0,0,0,0,
		0,0,0,0,

		0,0,1,0,
		0,1,1,0,
		0,1,0,0,
		0,0,0,0
	},
	// S미노(6번 블록)
	{
		0,0,0,0,
		0,0,1,1,
		0,1,1,0,
		0,0,0,0,

		0,0,1,0,
		0,0,1,1,
		0,0,0,1,
		0,0,0,0,

		0,0,1,1,
		0,1,1,0,
		0,0,0,0,
		0,0,0,0,

		0,1,0,0,
		0,1,1,0,
		0,0,1,0,
		0,0,0,0
	}
};

void NewBlockMaker() {
	block_X = (SIZE_X / 2) - 2;
	block_Y = 0;
	block_rotation = 0;

	// 홀드 가능상태일 때 에만
	if (holdOn == 0 || holdOn == 1) 
		NextBlocksPush();
	NextBlockDrawer();

	// 홀드를 사용했을 때만 업데이트
	if (holdOn == 2) 
		HoldBlockDrawer(); // 홀드 블록 그리기

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y][block_X + x] = MBLOCK;
		}
	}
	needNewOn = 0; // 블록필요상태를 다시 변환
}

int BlockSelecter() {
	static int count = 7;

	count++;
	if (count > 6) {
		BlockShuffler(); // 블록 7개를 다시 섞음
		count = 0; //다시 카운트를 0으로 초기화
	}
	return blockShuffle[count];
}

void BlockShuffler() {
	int j, temp;

	for (int i = 0; i < 7; i++)
		blockShuffle[i] = i;

	for (int i = 0; i < 7; i++) {
		j = rand() % 7;

		temp = blockShuffle[i];
		blockShuffle[i] = blockShuffle[j];
		blockShuffle[j] = temp;
	}
}

void ResetBlocks()  {
	block_typeNext_1 = BlockSelecter();
	block_typeNext_2 = BlockSelecter();
	block_typeNext_3 = BlockSelecter();
}

void NextBlocksPush() {
	block_typeNow = block_typeNext_1;
	block_typeNext_1 = block_typeNext_2;
	block_typeNext_2 = block_typeNext_3;
	block_typeNext_3 = BlockSelecter();
}

void ShadowBlockMaker() {
	int shadowblock_Y = 0;

	while (1) {
		// 그림자 블록을 픽스블록과 충돌할때까지 내림
		if (CrushCheck(0, shadowblock_Y, FALSE) == TRUE) 
			++shadowblock_Y;

		// 충돌 한 위치에 그림
		if (CrushCheck(0, shadowblock_Y, FALSE) == FALSE) {
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					if ( blocks[block_typeNow][block_rotation][y][x] == 1
						// 충돌이 일어난 Y에서 -1을뺌
						&& copyBoard[(block_Y - 1) + shadowblock_Y + y][block_X + x] < 1) 
						
						copyBoard[(block_Y - 1) + shadowblock_Y + y][block_X + x] = SBLOCK;
				}
			}
			shadowblock_Y = 0;
			return;
		}
	}
}