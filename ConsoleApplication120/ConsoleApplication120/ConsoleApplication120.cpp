#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

#define INIT_POS 1
const int Mapanswer[4][4] = { {1, 6, 1, 8},
								{6, 2, 5, 4},
								{7, 2, 5, 4},
								{8, 3, 3, 7} };
void SetConsole()
{
	system("mode con:cols=65 lines=10");
	system("title 두 번째 프로젝트.");
}
struct Pos {
	int x;
	int y;
};
enum KEYBOARD {
	IS_ARROW = 224,
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	SPACE = 32,
};
enum COLOR {
	GREEN = 10,
	MINT,
	RED,
	PINK,
	YELLOW,
	WHITE,
};
void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = 2*x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
int Getkey()
{
	if (_kbhit() != 0) {
		return _getch();
	}
	return 0;
}
class Mygame {
private:
	Pos player;
	Pos flipcard[3];
	char QuestionMap[4][4];
	int matchCardCount;
	int flipCardCount;
	int totalflipCardCount;
public:
	void startgame()
	{
		INIT();
		DrawBack();
		int key = 0;
		while (true)
		{
			key = Getkey();
			if (key == KEYBOARD::IS_ARROW) {
				MovePos();
			}
			if (key == KEYBOARD::SPACE) {
				FlipCard();
			}
			DrawMain();
			Sleep(100);
			CheckCard();
		}
	}
	void INIT()
	{
		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				QuestionMap[y][x] = '?';
			}
		}
		player.x = 0;
		player.y = 0;
		flipCardCount = 0;
		matchCardCount = 0;
		totalflipCardCount = 0;
	}
	void FlipCard()
	{
		if (QuestionMap[player.y][player.x] != '?') return;
		if (flipCardCount > 2) return;
		flipcard[flipCardCount].y = player.y;
		flipcard[flipCardCount].x = player.x;
		QuestionMap[player.y][player.x] = Mapanswer[player.y][player.x]+'0';
		++flipCardCount;
	}
	void MovePos()
	{
		gotoxy(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2)+1);
		printf("  ");
		switch (_getch()) {
		case KEYBOARD::LEFT:
			--player.x;
			if (player.x <= 0) {
				player.x = 0;
			}
			break;
		case KEYBOARD::RIGHT:
			++player.x;
			if (player.x >= 3) {
				player.x = 3;
			}
			break;
		case KEYBOARD::DOWN:
			++player.y;
			if (player.y >= 3) {
				player.y = 3;
			}
			break;
		case KEYBOARD::UP:
			--player.y;
			if (player.y <= 0) {
				player.y = 0;
			}
			break;
		}
	}
	void DrawMain()
	{
		SetTextColor(WHITE);
		char c = '\0';
		for (int y = 0; y < 4; y++) {
			gotoxy(INIT_POS, INIT_POS + (2 * y));
			for (int x = 0; x < 4; x++) {
				c = QuestionMap[y][x];
				if (c != '?') {
					SetTextColor(GREEN);
				}
				printf("[%c]   ", c);
				SetTextColor(WHITE);
			}
		}
		gotoxy(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2)+1);
		printf(" ^");
		gotoxy(14, 1);
		printf("Count : %d", totalflipCardCount);

	}
	void CheckCard()
	{
		if (flipCardCount == 2) {
			char c = '?';
			if (Mapanswer[flipcard[0].y][flipcard[0].x] == Mapanswer[flipcard[1].y][flipcard[1].x])
			{
				c = Mapanswer[flipcard[0].y][flipcard[0].x]+'0';
				++matchCardCount;
			}
			else {
				Sleep(500);
			}
			QuestionMap[flipcard[0].y][flipcard[0].x] = c;
			QuestionMap[flipcard[1].y][flipcard[1].x] = c;
			flipCardCount = 0;
			++totalflipCardCount;
			if (matchCardCount >= 8) {
				DrawGameClear();
				Sleep(2000);
				system("cls");
				INIT();
				DrawBack();
			}
		}
	}
	void DrawBack()
	{
		SetTextColor(WHITE);
		gotoxy(14, 6);
		cout << "두 번째 프로젝트 최종안";
		gotoxy(14, 7);
		cout << "_by. ";
		SetTextColor(PINK);
		cout << "김민석";
		SetTextColor(WHITE);
	}
	void DrawGameClear()
	{
		SetTextColor(YELLOW);
		gotoxy(10, 3);
		cout << "=========================";
		gotoxy(10, 4);
		cout << "======= C L E A R =======";
		gotoxy(10, 5);
		cout << "=========================";
		SetTextColor(WHITE);
	}
	void SetTextColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};
int main(void)
{
	SetConsole();
	Mygame *pgr = new Mygame();
	pgr->startgame();
	delete(pgr);
	return 0;
}