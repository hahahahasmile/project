#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <ctime>
#pragma comment(lib, "winmm.lib")
using namespace std;

#define MAGIC_KEY 224
#define SPACE 32
#define KEY_NUM 4
#define LIFE 3
#define MAX_LEVEL 11

enum MENU {
	GAMESTART =0,
	INFO,
	QUIT
};
enum KEYBOARD {
	UP =72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title 3번째 프로젝트 프로토타입");
}
void DrawReadyGame()
{
	system("cls");
	gotoxy(5, 2);
	system("cls");
	gotoxy(5, 2);
	cout << "******************************";
	gotoxy(5, 3);
	cout << "*        Dance Dance         *";
	gotoxy(5, 4);
	cout << "******************************";
	gotoxy(10, 8);
	cout << "GameStart";
	gotoxy(10, 9);
	cout << "GameInfo";
	gotoxy(10, 10);
	cout << "Quit" << endl;
}
void DrawInfoGame()
{
	system("cls");
	gotoxy(1, 3);
	cout << "*******************************************";
	gotoxy(1, 4);
	cout << "김민석";
	gotoxy(1, 5);
	cout << "3번째 프로젝트입니다.";
	gotoxy(1, 8);
	cout << "|Thank you.";
	gotoxy(1, 9);
	cout << "*******************************************";
	gotoxy(1, 10);
	cout << "|Music - https://www.youtube.com/HYPMUSIC";
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
MENU ReadyGame()
{
	int y = 0;
	int input = 0;
	while (true) {
		DrawReadyGame();
		DrawUserCursor(y);
		input = _getch();
		if (input == MAGIC_KEY) {
			switch (_getch())
			{
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == SPACE)
		{
			switch (y)
			{
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
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}
	int num = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < level; i++)
	{
		num = rand() % KEY_NUM;
		switch (num)
		{
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
void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		switch (v[i])
		{
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
bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)
{
	if (questionVec.size() != answerVec.size()) {
		return false;
	}
	for (int i = 0; i < static_cast<int>(questionVec.size()); i++) {
		if (questionVec[i] != answerVec[i]) {
			return false;
		}
	}
	return true;
}
void StartGame()
{
	PlaySound("HYP-Hit.wav", NULL, SND_NODEFAULT | SND_ASYNC | SND_LOOP);
	int life = LIFE;
	int score = 0;
	//재생했을때 현재시간.
	clock_t startTime, endTime;
	startTime = clock();

	//→←↑↓, d a w s
	//문제
	vector<int> questionVec;
	string questionStr = "";
	//답안지
	vector<int> answerVec;
	string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;
	while (true)
	{
		int level = (score / 30) + 1;

		//문제를 세팅
		SetQuestion(questionVec, level);
		//문제를 보여주기.
		VectorToString(questionVec, questionStr);
		while (true)
		{
			//1문제를 가지고 문제를 푼다.
			DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//게임 오버일때 현재시간
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				DrawGameOver(playTime);
				PlaySound(NULL, NULL, 0);
				return;
			}

			//정답 하나씩 입력.
			firstInput = _getch();
			if (firstInput == MAGIC_KEY)
			{
				secondInput = _getch();
				answerVec.push_back(secondInput);
				switch (secondInput)
				{
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
			else if (firstInput == SPACE)
			{
				//답안 제출
				//답안 확인
				if (CheckAnswer(questionVec, answerVec))
				{
					score += 10;
				}
				else
				{
					//틀렸다.
					--life;
					score -= 5;
					if (score < 0)
					{
						score = 0;
					}
				}

				questionVec.clear();
				questionStr = "";
				answerVec.clear();
				answerStr = "";
				break;
			}
		}
	}
}

int main(void)
{
	SetConsoleView();
	while (true)
	{
		switch (ReadyGame())
		{
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
