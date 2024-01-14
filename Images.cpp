#include "Images.h"
#include <vector>
#include "consoleGUI/GUI.h"
#include "figure.h"
void printTitleTetris(int posX, int posY)
{
	std::vector<std::vector<char>> titleTetris =
	{
		{char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(187),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(187),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(187),char(219),char(219),char(219),char(219),char(219),char(219),char(187),char(176),char(219),char(219),char(187),char(176),char(219),char(219),char(219),char(219),char(219),char(219),char(187)},
		{char(200),char(205),char(205),char(219),char(219),char(201),char(205),char(205),char(188),char(219),char(219),char(201),char(205),char(205),char(205),char(205),char(188),char(200),char(205),char(205),char(219),char(219),char(201),char(205),char(205),char(188),char(219),char(219),char(201),char(205),char(205),char(219),char(219),char(187),char(219),char(219),char(186),char(219),char(219),char(201),char(205),char(205),char(205),char(205),char(188)},
		{char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(219),char(219),char(219),char(187),char(176),char(176),char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(219),char(219),char(219),char(219),char(201),char(188),char(219),char(219),char(186),char(200),char(219),char(219),char(219),char(219),char(219),char(187),char(176)},
		{char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(201),char(205),char(205),char(188),char(176),char(176),char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(201),char(205),char(205),char(219),char(219),char(187),char(219),char(219),char(186),char(176),char(200),char(205),char(205),char(205),char(219),char(219),char(187)},
		{char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(219),char(219),char(219),char(219),char(219),char(187),char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(176),char(219),char(219),char(186),char(176),char(176),char(219),char(219),char(186),char(219),char(219),char(186),char(219),char(219),char(219),char(219),char(219),char(219),char(201),char(188)},
		{char(176),char(176),char(176),char(200),char(205),char(188),char(176),char(176),char(176),char(200),char(205),char(205),char(205),char(205),char(205),char(205),char(188),char(176),char(176),char(176),char(200),char(205),char(188),char(176),char(176),char(176),char(200),char(205),char(188),char(176),char(176),char(200),char(205),char(188),char(200),char(205),char(188),char(200),char(205),char(205),char(205),char(205),char(205),char(188),char(176)}
	};
	for (int i = 0; i < titleTetris.size(); i++)
	{
		for (int j = 0; j < titleTetris[i].size(); j++)
		{
			setcur(posX + j, posY + i);
			std::cout << titleTetris[i][j];
		}
	}
}

void printStandartTitleTetris(int posX, int posY)
{
	std::vector<std::vector<char>> standartTitkeTetris =
	{
		{' ', '_', '_',  '_', ' ', ' ', '_', '_', '_', ' ',  ' ', '_', '_', '_', ' ',  ' ', '_', '_', '_', ' ',  ' ', '_', ' ', ' ', '_', '_', ' '},
		{'|', '_', ' ', '_', '|', '|', ' ', '_', '_', '|', '|', '_', ' ', '_', '|', '|', ' ', 'o', ' ', char(92), '|', ' ',  '|', char(47), ' ',  '_', '|'},
		{' ', '|', ' ', '|', ' ', '|', ' ', '_', '|', ' ', ' ', '|', ' ', '|', ' ', '|', ' ', ' ',  ' ', char(47), '|', ' ', '|', char(92), '_', ' ',char(92)},
		{' ', '|', '_', '|', ' ', '|', '_', '_', '_', '|', ' ', '|', '_', '|', ' ', '|', '_',  '|', char(92), char(92), '|', '_', '|', '|', '_', '_', char(47)},
};
	for (int i = 0; i < standartTitkeTetris.size(); i++)
	{
		for (int j = 0; j < standartTitkeTetris[i].size(); j++)
		{
			saveConsoleAttributes();
			if (j <= 4)setColorForeground(BrightRed);
			else if (j > 4 && j <= 9)setColorForeground(Yellow);
			else if (j > 9 && j <= 14)setColorForeground(BrightYellow);
			else if (j > 14 && j <= 19)setColorForeground(BrightGreen);
			else if (j > 19 && j <= 22)setColorForeground(BrightCyan);
			else if (j > 22 && j <= 26)setColorForeground(BrightMagenta);
			setcur(posX + j, posY + i);
			std::cout << standartTitkeTetris[i][j];
			restoreConsoleAttributes();
		}
	}
}

void printPauseImage(int x, int y)
{
	std::vector<std::vector<char>> pauseImage =
	{
		{char(220),char(220),char(220),char(220),char(220),char(220),char(220), char(220), char(220)},
		{char(219), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(219)},
		{char(219),char(32), char(32), char(219), char(32), char(219), char(32),char(32), char(219)},
		{char(219), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(219)},
		{char(223),char(223),char(223),char(223),char(223),char(223), char(223), char(223), char(223)}
	};
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			setcur(x + j, y + i);
			std::cout << pauseImage[i][j];
		}
	}
}

void titleGameOver(int posX, int posY)
{
	char w = char(219);
	char arr[7][39] =
	{

		{w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w},
		{w,' ',' ',' ',' ',w,' ',' ',' ',' ',w,' ',w,w,w,' ',w,' ',' ',' ',w,' ',' ',' ',' ',w,' ',w,' ',w,' ',' ',' ',w,' ',' ',' ',' ',w},
		{w,' ',w,w,w,w,' ',w,w,' ',w,' ',' ',w,' ',' ',w,' ',w,w,w,' ',w,w,' ',w,' ',w,' ',w,' ',w,w,w,' ',w,w,' ',w},
		{w,' ',w,' ',' ',w,' ',' ',' ',' ',w,' ',w,' ',w,' ',w,' ',' ',' ',w,' ',w,w,' ',w,' ',w,' ',w,' ',' ',' ',w,' ',' ',' ',' ',w},
		{w,' ',w,w,' ',w,' ',w,w,' ',w,' ',w,w,w,' ',w,' ',w,w,w,' ',w,w,' ',w,' ',' ',' ',w,' ',w,w,w,' ',w,' ',w,w},
		{w,' ',' ',' ',' ',w,' ',w,w,' ',w,' ',w,w,w,' ',w,' ',' ',' ',w,' ',' ',' ',' ',w,w,' ',w,w,' ',' ',' ',w,' ',w,' ',w,w},
		{w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w,w}
	};

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 39; j++)
		{
			setcur(posX + j, posY + i);
			std::cout << arr[i][j];
		}
	}

}