#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <mmsystem.h>
#include <vector>
#include <string>
#pragma comment(lib,"winmm.lib")
using namespace std;

#define SOUND_FILE_NAME "HYP-Hit.wav"

#define MAGIC_KEY 224
#define SPACE 32
#define KEY_NUM 4
#define LIFE 3
#define MAX_LEVEL 11

enum KEYBOARD {
	UP=72,
	LEFT=75,
	RIGHT=77,
	DOWN = 80
};
enum MENU {
	GAMESTART =0,
	INFO,
	QUIT
};
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void SetConsole()
{
	system("mode con:cols=50 lines=20");
	system("title 3번째 프로젝트");
}
void DrawReadyGame()
{
	system("cls");
	gotoxy(5, 2);
	cout << "******************************";
	gotoxy(5, 3);
	cout << "*        3번째 프로젝트      *";
	gotoxy(5, 4);
	cout << "******************************";
	gotoxy(10, 8);
	cout << "GameStart";
	gotoxy(10, 9);
	cout << "GameInfo";
	gotoxy(10, 10);
	cout << "Quit";
}
void DrawGameOver(const int playTime)
{
	gotoxy(8, 8);
	cout << "-------------------";
	gotoxy(8, 9);
	cout << "| G A M E O V E R |";
	gotoxy(8, 10);
	cout << " " << playTime << " sec";
	gotoxy(8, 11);
	cout << "-------------------";
	system("pause>null");
}
void DrawUserCursor(int& y)
{
	if (y <= 0) {
		y = 0;
	}
	else if (y >= 2) {
		y = 2;
	}
	gotoxy(9, 8 + y);
	cout << ">";
}
void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)
{
	system("cls");
	gotoxy(2, 1);
	cout << "*******************************************";
	gotoxy(4, 3);
	cout << "Life : " << life << " / " << LIFE;
	gotoxy(4, 4);
	cout << "Score : " << score;
	gotoxy(4, 8);
	cout << "Q : " << questionStr;
	gotoxy(4, 10);
	cout << "A : " << answerStr;
	gotoxy(4, 12);
	cout << "press SPACE! after input done.";
	gotoxy(2, 18);
	cout << "*******************************************" << endl;
}
void DrawInfoGame()
{
	system("cls");
	gotoxy(1, 3);
	cout << "*******************************************";
	gotoxy(1, 4);
	cout << "김민석";
	gotoxy(1, 5);
	cout << "3번째 프로젝트";
	gotoxy(1, 8);
	cout << "|Thank you.";
	gotoxy(1, 9);
	cout << "*******************************************";
	gotoxy(1, 10);
	cout << "|Music - https://www.youtube.com/HYPMUSIC";
}
MENU ReadyGame()
{
	int y = 0;
	int input = 0;
	while (true) {
		DrawReadyGame();
		DrawUserCursor(y);
		input = _getch();
		if (input == MAGIC_KEY) {
			switch (_getch()) {
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == SPACE) {
			switch (y) {
			case 0:
				return GAMESTART;
			case 1:
				return INFO;
			case 2:
				return QUIT;
			}
		}
	}
}

void InfoGame()
{
	DrawInfoGame();
	system("pause>null");
}
void SetQuestion(vector<int>& questionVec, int level)
{
	if (level >= MAX_LEVEL) {
		level = MAX_LEVEL;
	}
	int num = 0;
	srand(unsigned(time(NULL)));
	for (int i = 0; i < level; i++) {
		num = rand() % KEY_NUM;
		switch (num) {
		case 0:
			questionVec.push_back(UP);
			break;
		case 1:
			questionVec.push_back(RIGHT);
			break;
		case 2:
			questionVec.push_back(LEFT);
			break;
		case 3:
			questionVec.push_back(DOWN);
			break;
		}
	}
}
void VectortoString(vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		switch (v[i]) {
		case UP:
			str += "↑ ";
			break;
		case DOWN:
			str += "↓ ";
			break;
		case LEFT:
			str += "← ";
			break;
		case RIGHT:
			str += "→ ";
			break;
		}
	}
}
bool CheckAnswer(vector<int> answerVec, vector<int> questionVec)
{
	if (answerVec.size() != questionVec.size()) {
		return false;
	}
	for (int i = 0; i < answerVec.size(); i++) {
		if (questionVec[i] != answerVec[i]) {
			return false;
		}
	}
	return true;
}
void StartGame()
{
	PlaySound(TEXT(SOUND_FILE_NAME), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	int life = LIFE;
	int score = 0;
	clock_t startTime, endTime;
	startTime = clock();
	string answerStr = "";
	string questionStr = "";
	vector<int> answerVec;
	vector<int> questionVec;
	int firstinput = 0;
	int secondinput = 0;
	while (true)
	{
		int level = (score / 30) + 1;
		SetQuestion(questionVec,level);
		VectortoString(questionVec,questionStr);
		while (true) {
			DrawStartGame(life,score,questionStr,answerStr);
			if (life == 0) {
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);
				DrawGameOver(playTime);
				PlaySound(NULL, 0, 0);
				return;
			}
			firstinput = _getch();
			if (firstinput == MAGIC_KEY) {
				secondinput = _getch();
				answerVec.push_back(secondinput);
				switch (secondinput) {
				case UP:
					answerStr += "↑ ";
					break;
				case DOWN:
					answerStr += "↓ ";
					break;
				case LEFT:
					answerStr += "← ";
					break;
				case RIGHT:
					answerStr += "→ ";
					break;
				}
			}
			else if (firstinput == SPACE)
			{
				if (CheckAnswer(questionVec, answerVec)) {
					score += 10;
				}
				else {
					--life;
					score -= 5;
					if (score < 0) {
						score = 0;
					}
				}
				questionVec.clear();
				answerVec.clear();
				answerStr = "";
				questionStr = "";
				break;
			}
		}
	}
}
int main(void)
{
	SetConsole();
	while (true) {
		switch (ReadyGame()) {
		case GAMESTART:
			StartGame();
			break;
		case INFO:
			InfoGame();
			break;
		case QUIT:
			return 0;
		}
	}
	return 0;
}