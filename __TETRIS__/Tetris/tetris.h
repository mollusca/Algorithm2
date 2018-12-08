#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include <time.h>
#include <stdlib.h>

#pragma comment(lib, "winmm.lib")
#include "Digitalv.h"
#define SOUND_FILE_NAME "A:\\Algorithm2\\Algorithm2\\__TETRIS__\\Tetris\\Data\\TetrisBGM.wav"

// Ű���� �Է� ��ũ��
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define ESC 27

// ������ ũ��
#define SIZE_X 12
#define SIZE_Y 24
#define SIZE_X_ADJ 10
#define SIZE_Y_ADJ 2

#define BONUS 5

#define TRUE 1
#define FALSE 0

int realBoard[SIZE_Y][SIZE_X]; // ���� ������
int copyBoard[SIZE_Y][SIZE_X]; // ī�� ������

int block_typeNow; // �������� Ÿ��
int block_typeNext_1; // ���� ��� 1
int block_typeNext_2; // ���� ��� 2
int block_typeNext_3; // ���� ��� 3
int block_typeHold; // Ȧ�� ���

int block_X; // ���� ����� X ��ǥ
int block_Y; // ���� ����� Y ��ǥ
int block_rotation; // ��� ȸ�� ��
int blockShuffle[7]; // ��� ���� ���� ����

int blocks[7][4][4][4];

int hardDropOn; // ��� �ϵ� ��� üũ
int crushOn; // ��� �浹 üũ
int needNewOn; // �� ��� �ʿ俩�� üũ
int holdOn; // Ȧ�� Ű üũ
int holdChanger; // Ȧ�� ��� üũ

int gameSpeed; // �� ���ǵ� ���� ��
int bestScore;
int yourScore;
int deleteline_cnt; // ���� ���� �� ��
int deleteline_combo; // ���� �޺� ����
int game_level;
int game_speed; // ���� ���ǵ� ��

int bestScoreFlag;

enum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5, EBLOCK = 6 };

/* ConsoleController.c */
// �ܼ� �⺻ ����
void SetConsole();  
// Console â ũ�� ����
void ConsoleSize(); 
// �ܼ� â ��ũ�ѹ� ����
void RemoveScrollbar(); 
// x, y��ǥ�� Ŀ�� �̵�
void GotoXY(int x, int y);
// Ŀ�� ǥ�� ����
void RemoveCursor();
// ����� (BETA)
void MusicPlay(); 

/* GameDrawer.c */
// ���� �� ���
void PrintGameBoard(); 
// ���� UI
void UIDrawer(); 
// Ȧ�� �� ��� ����
void HoldBlockDrawer(); 
// ���� �� ��� ����
void NextBlockDrawer(); 
// Pauseâ �׸���
void PauseDrawer(); 
// Introâ �׸���
void IntroDrawer(); 
// PAUSE, GAMEOVER ��Ȳ �� ȭ���� ��� ����
void HideDrawer(); 
// Gameoverâ �׸���
void GameOverDrawer(); 
void WriteScore();
// ���� ���� ����
void GameEndDrawer(); 

/* BlockMaker.c */
// �� ��� �ʿ� ����
void NewBlockMaker();
// ���� ��� ����
int BlockSelector(); 
// 7������ �� Shuffle
void BlockShuffler();
// ��ϵ� �ʱ�ȭ
void ResetBlocks(); 
// ���� ����� ���� �������
void NextBlocksPush();
// �׸��� ����� ����
void ShadowBlockMaker(); 

/* BlockController.c */
// Ű����� ��Ʈ��
void KeyboardControl(); 
// ��� �̵�, ȸ��
void BlockMove(int, int, int);
// ��� ����
void BlockFix();
// ��� �ϰ�, ����
void BlockDrop(); 

/* BlockDetect.c */
int CrushCheck(int, int, int);
// ���� üũ, ���� �����
void LineCheck(); 
// ���� �̵��� ����� ã�Ƽ� �����
void MblockDeleter(); 
// �׸��� �����
void ShadowBlockDeleter(); 

/* GameManager.c */
void ReadBestScore();
void GameoverCheck();
void ResetRealBoard();
void ResetCopyBoard();
void ResetGame();
// ���۸� ��
void EndPauseManager(); 
void LevelManager();
void DeleteScoreManager();