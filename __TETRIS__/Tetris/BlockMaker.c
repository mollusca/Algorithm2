/* BlockMaker.c */
#include "tetris.h"

// [�������][ȸ��][����][����]
blocks[7][4][4][4] = {
	// J�̳�(0�� ���)
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
	// L�̳�(1�� ���)
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
	// O�̳�(2�� ���)
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
	// T�̳�(3�� ���)
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
	// I�̳�(4�� ���)
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
	// Z�̳�(5�� ���)
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
	// S�̳�(6�� ���)
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

	// Ȧ�� ���ɻ����� �� ����
	if (holdOn == 0 || holdOn == 1) 
		NextBlocksPush();
	NextBlockDrawer();

	// Ȧ�带 ������� ���� ������Ʈ
	if (holdOn == 2) 
		HoldBlockDrawer(); // Ȧ�� ��� �׸���

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (blocks[block_typeNow][block_rotation][y][x] == 1)
				copyBoard[block_Y + y][block_X + x] = MBLOCK;
		}
	}
	needNewOn = 0; // ����ʿ���¸� �ٽ� ��ȯ
}

int BlockSelecter() {
	static int count = 7;

	count++;
	if (count > 6) {
		BlockShuffler(); // ��� 7���� �ٽ� ����
		count = 0; //�ٽ� ī��Ʈ�� 0���� �ʱ�ȭ
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
		// �׸��� ����� �Ƚ���ϰ� �浹�Ҷ����� ����
		if (CrushCheck(0, shadowblock_Y, FALSE) == TRUE) 
			++shadowblock_Y;

		// �浹 �� ��ġ�� �׸�
		if (CrushCheck(0, shadowblock_Y, FALSE) == FALSE) {
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					if ( blocks[block_typeNow][block_rotation][y][x] == 1
						// �浹�� �Ͼ Y���� -1����
						&& copyBoard[(block_Y - 1) + shadowblock_Y + y][block_X + x] < 1) 
						
						copyBoard[(block_Y - 1) + shadowblock_Y + y][block_X + x] = SBLOCK;
				}
			}
			shadowblock_Y = 0;
			return;
		}
	}
}