/* ConsoleController.c */
#include "tetris.h"

// Console 창 크기 조절
void ConsoleSize() {
	system("mode con cols=80 lines=30"); 
}

// 콘솔 창 스크롤바 삭제
void RemoveScrollbar() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size = {
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

// x, y좌표로 커서 이동
void GotoXY(int x, int y) {
	COORD pos = { 2 * x, y }; // 가로는 두칸씩 이동
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 커서 표시 안함
void RemoveCursor() {
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

// 배경음 (BETA)
void MusicPlay() {
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// 콘솔 기본 세팅 
void SetConsole() {
	ConsoleSize();
	RemoveScrollbar();
	RemoveCursor();
	MusicPlay();
}