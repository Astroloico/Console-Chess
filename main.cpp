#include <iostream>
#include <array>
#include <conio.h>
#include <string>
#include <windows.h> 
#define setConParam SetConsoleTextAttribute
#define kbhit _kbhit
#define getch _getch
#define white 0xf0
#define swhite 0x70
#define black 0x0f
#define sblack 0x8f
#define bgcol 0x90
#define K "KW"
#define Q "QW"
#define R "RW"
#define B "BW"
#define H "HW"
#define P "PW"
#define k "KB"
#define q "QB"
#define r "RB"
#define b "BB"
#define h "HB"
#define p "PB"
#define e "  "
#define startingBoard {{(string)r, (string)h, (string)b, (string)q, (string)k, (string)b, (string)h, (string)r},{(string)p, (string)p, (string)p, (string)p, (string)p, (string)p, (string)p, (string)p},{(string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e},{(string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e},{(string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e},{(string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e, (string)e},{(string)P, (string)P, (string)P, (string)P, (string)P, (string)P, (string)P, (string)P},{(string)R, (string)H, (string)B, (string)Q, (string)K, (string)B, (string)H, (string)R}};
using namespace std;
void resetBoard();
HANDLE console_color = GetStdHandle(STD_OUTPUT_HANDLE);
string operator * (string a, unsigned int m) {
	string output = "";
	while (m--) {
		output += a;
	}
	return output;
}
string pickedPiece = e;
struct coords {
	int x = 0;
	int y = 0;
};
coords cursor;
string board[8][8] = startingBoard;
int printPixel(bool col, string s, bool sel) {
	if (col)
	{
		if (!sel) setConParam(console_color, white);
		else setConParam(console_color, swhite);
	}
	else {
		if (!sel) setConParam(console_color, black);
		else setConParam(console_color, sblack);
	}
	if (sel && pickedPiece != e)
		cout << pickedPiece;
	else cout << s;
	setConParam(console_color, bgcol);
	return 0;
}
int main()
{
	system("color 90");
	while (true)
	{
		system("cls");
		cout << (string)"\n" * 10;
		for (int i = 0; i < 8; i++) {
			cout << (string)" " * 50 << to_string(-i + 8) << " ";
			for (int j = 0; j < 8; j++) {
				printPixel(!((i + j) % 2), board[i][j], j == cursor.x && i == cursor.y);
			}
			cout << "\n";
		}
		cout << (string)" " * 52 << "A B C D E F G H" << "\n";
		while (!kbhit()) {}
		int key = getch();
		if (key == 0 || key == 224) {
			switch (getch()) {
			case 72:
				cursor.y--; break;
			case 75:
				cursor.x--; break;
			case 80:
				cursor.y++; break;
			case 77:
				cursor.x++; break;
			}
		}
		else if (key == ' ') {
			if (pickedPiece != e) {
				board[cursor.y % 8][cursor.x % 8] = pickedPiece;
				pickedPiece = e;
			}
			else {
				pickedPiece = board[cursor.y][cursor.x];
				board[cursor.y % 8][cursor.x % 8] = e;
			}
		}
		else if (key == 'r')
			resetBoard();
	}
}
inline void resetBoard()
{
	string rboard[8][8] = startingBoard;
	for (char i = 0; i < 8; i++)
		for (char j = 0; j < 8; j++)
			board[i][j] = rboard[i][j];
}
