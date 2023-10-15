#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// 내가 적은 답들을 화면에 표시할려고 했으나 system("cls") 때문에 어차피 지어지기 때문에 구현하지 못하였다.
// input이라 내가 적으려고 하는 부분들이 겹치기 때문에 그 부분을 수정하였다.
// gotoxy() 함수는 마우스 위치
// SetConsole()함수는 콘솔창 크기 조절
// DrawmainMenu()함수는 메인메뉴를 그리는 것 system("cls")로 화면을 지우고 시작한다.
// Mainmenu()함수는 bool 함수로 Game 화면으로 넘어갈지에 대한 yes no 답을 제공한다.
// SetDictionary()함수는 문제에 쓸 단어들을 이 프로그램으로 불러들이는 사전작업을 하는 함수이다.
// DrawGame()함수는 게임화면을 그리는 함수 이 함수에 있는 system("cls") 때문에 myanswer()를 화면에 표시를 못한다.
// Game()함수는 게임이 동작되는 과정 전반을 코드로 나타내는 함수
// GameDraw()함수를 두개 만들어서 myanswer()를 표시하면 되지 않을까? 라는 의문이 생긴다.
// 각 단어에 맞는 그 의미를 매칭시키게 해서 맞추면 더 좋은 프로그램이 되지 않을까?
// 이상 첫 프로젝트 코드 작성및 복기 끝
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
	system("title 첫 프로젝트");
}
void DrawMainmenu()
{
	system("cls");
	gotoxy(10, 1);
	cout << "==============================";
	gotoxy(10, 2);
	cout << "======= 단어 맞추기 ==========";
	gotoxy(10, 3);
	cout << "==============================";
	gotoxy(10, 5);
	cout << "시작하려면 's'를 눌러주세요";
	gotoxy(10, 6);
	cout << "종료하려면 'q'를 눌러주세요";
	gotoxy(10, 8);
	cout << "by.김민석";
	gotoxy(10, 10);
}
int UserInput()
{
	if (_kbhit() != 0) {
		return _getch();
	}
	return 0;
}
bool Mainmenu()
{
	DrawMainmenu();
	while (true) {
		int key = UserInput();
		if (key == 's' || key == 'S') {
			return true;
		}
		else if (key == 'q' || key == 'Q') {
			break;
		}
	}
	return false;
}
void SetDictionary(vector<string> & Gameanswer)
{
	const int num = 5;
	const string str[num] = { "apple","banana","tango","egg","chicken" };
	ifstream ReadToFile("game.txt");
	if (!ReadToFile.is_open()) {
		ofstream WriteToFile("game.txt");
		for (int i = 0; i < num; i++) {
			string tmp;
			tmp = str[i];
			if (i != num - 1) {
				tmp += "\n";
			}
			Gameanswer.push_back(str[i]);
			WriteToFile.write(tmp.c_str(),tmp.size());
		}
		WriteToFile.close();
		return;
	}
	while (!ReadToFile.eof()) {
		string tmp;
		getline(ReadToFile, tmp);
		Gameanswer.push_back(tmp);
	}
	ReadToFile.close();
	return;
}
void DrawGame(int life, int score, vector<string>& Gameanswer)
{
	system("cls");
	gotoxy(5, 1);
	cout << "life = " << life;
	gotoxy(15, 1);
	cout << "score = " << score;
	gotoxy(5, 8);
	cout << "past = ";
	for (int i = 0; i < static_cast<int>(Gameanswer.size()); i++) {
		cout << Gameanswer[i] << " ";
	}
	gotoxy(5, 12);
	cout << "input = ";
	gotoxy(13, 14);
	cout << "메인화면 'qq'" << '\n';
}
void Gamemenu()
{
	vector<string> Gameanswer;
	vector<string> myanswer;
	int score = 0;
	SetDictionary(Gameanswer);
	
	while (true) {
		int num = 0;
		srand(unsigned(time(NULL)));
		num = rand() % static_cast<int>(Gameanswer.size());
		string shidden;
		const string svisible = Gameanswer[num];
		int life = static_cast<int>(svisible.length()) + 2;
		for (int i = 0; i < svisible.length(); i++) {
			shidden += "_";
		}
		while (true) {
			DrawGame(life, score, Gameanswer);
			gotoxy(5, 5);
			cout << shidden;
			gotoxy(20, 12);
			string tmp;
			cin >> tmp;
			if (tmp == "qq") {
				return;
			}
			myanswer.push_back(tmp);
			
			if (tmp.length() == 1) {
				for (int i = 0; i < svisible.length(); i++){
					if (svisible[i] == tmp[i]) {
						shidden[i] = tmp[i];
					}
				}
			}
			else if (tmp.length() > 1) {
				if (tmp == svisible) {
					score += 5;
					myanswer.clear();
					break;
				}
			}
			life -= 1;
			if (life < 0) {
				score -= 5;
				if (score < 0) {
					score = 0;
				}
				myanswer.clear();
				break;
			}
		}
	}
}
int main(void)
{
	SetConsole();
	bool isright = false;
	while (true) {
		isright = Mainmenu();
		if (isright) {
			Gamemenu();
		}
		else {
			break;
		}
	}
	return 0;
}