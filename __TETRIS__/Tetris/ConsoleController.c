/* ConsoleController.c */
#include "tetris.h"

// Console â ũ�� ����
void ConsoleSize() {
	system("mode con cols=80 lines=30"); 
}

// �ܼ� â ��ũ�ѹ� ����
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

// x, y��ǥ�� Ŀ�� �̵�
void GotoXY(int x, int y) {
	COORD pos = { 2 * x, y }; // ���δ� ��ĭ�� �̵�
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Ŀ�� ǥ�� ����
void RemoveCursor() {
	CONSOLE_CURSOR_INFO curinfo = { 0, };
	curinfo.dwSize = 1;
	curinfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curinfo);
}

// ����� (BETA)
void MusicPlay() {
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// �ܼ� �⺻ ���� 
void SetConsole() {
	ConsoleSize();
	RemoveScrollbar();
	RemoveCursor();
	MusicPlay();
}