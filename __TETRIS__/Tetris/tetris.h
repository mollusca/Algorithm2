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

// 키보드 입력 매크로
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32
#define ESC 27

// 게임판 크기
#define SIZE_X 12
#define SIZE_Y 24
#define SIZE_X_ADJ 10
#define SIZE_Y_ADJ 2

#define BONUS 5

#define TRUE 1
#define FALSE 0

int realBoard[SIZE_Y][SIZE_X]; // 실제 게임판
int copyBoard[SIZE_Y][SIZE_X]; // 카피 게임판

int block_typeNow; // 현재블록의 타입
int block_typeNext_1; // 다음 블록 1
int block_typeNext_2; // 다음 블록 2
int block_typeNext_3; // 다음 블록 3
int block_typeHold; // 홀드 블록

int block_X; // 현재 블록의 X 좌표
int block_Y; // 현재 블록의 Y 좌표
int block_rotation; // 블록 회전 값
int blockShuffle[7]; // 블록 종류 랜덤 선택

int blocks[7][4][4][4];

int hardDropOn; // 블록 하드 드랍 체크
int crushOn; // 블록 충돌 체크
int needNewOn; // 새 블록 필요여부 체크
int holdOn; // 홀드 키 체크
int holdChanger; // 홀드 사용 체크

int gameSpeed; // 겜 스피드 조절 값
int bestScore;
int yourScore;
int deleteline_cnt; // 라인 삭제 총 합
int deleteline_combo; // 라인 콤보 삭제
int game_level;
int game_speed; // 게임 스피드 값

int bestScoreFlag;

enum { EMPTY = 0, MBLOCK = 1, OVERLINE = 2, SBLOCK = 3, WALL = 4, FBLOCK = 5, EBLOCK = 6 };

/* ConsoleController.c */
// 콘솔 기본 세팅
void SetConsole();  
// Console 창 크기 조절
void ConsoleSize(); 
// 콘솔 창 스크롤바 삭제
void RemoveScrollbar(); 
// x, y좌표로 커서 이동
void GotoXY(int x, int y);
// 커서 표시 안함
void RemoveCursor();
// 배경음 (BETA)
void MusicPlay(); 

/* GameDrawer.c */
// 게임 판 출력
void PrintGameBoard(); 
// 게임 UI
void UIDrawer(); 
// 홀드 블럭 모양 저장
void HoldBlockDrawer(); 
// 다음 블럭 모양 저장
void NextBlockDrawer(); 
// Pause창 그리기
void PauseDrawer(); 
// Intro창 그리기
void IntroDrawer(); 
// PAUSE, GAMEOVER 상황 때 화면을 잠시 지움
void HideDrawer(); 
// Gameover창 그리기
void GameOverDrawer(); 
void WriteScore();
// 게임 종료 연출
void GameEndDrawer(); 

/* BlockMaker.c */
// 새 블록 맵에 생성
void NewBlockMaker();
// 랜덤 블록 선택
int BlockSelector(); 
// 7종류의 블럭 Shuffle
void BlockShuffler();
// 블록들 초기화
void ResetBlocks(); 
// 다음 블록을 현재 블록으로
void NextBlocksPush();
// 그림자 블록을 생성
void ShadowBlockMaker(); 

/* BlockController.c */
// 키보드로 컨트롤
void KeyboardControl(); 
// 블록 이동, 회전
void BlockMove(int, int, int);
// 블록 고정
void BlockFix();
// 블록 하강, 고정
void BlockDrop(); 

/* BlockDetect.c */
int CrushCheck(int, int, int);
// 라인 체크, 라인 지우기
void LineCheck(); 
// 현재 이동중 블록을 찾아서 지우기
void MblockDeleter(); 
// 그림자 지우기
void ShadowBlockDeleter(); 

/* GameManager.c */
void ReadBestScore();
void GameoverCheck();
void ResetRealBoard();
void ResetCopyBoard();
void ResetGame();
// 버퍼를 줌
void EndPauseManager(); 
void LevelManager();
void DeleteScoreManager();