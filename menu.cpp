#include "menu.h"
#include "consoleGUI/GUI.h"
#include "Variables.h"
#include "game.h"
#include "Images.h"
#include "Timer.h"
#include <ctime>
#include "settings.h"

void printHighScores()
{
	for (int i = 0; i < 5; i++)
	{
		std::string s = std::to_string(global::highScores[i]);
		setcur(26 + 10 - s.size() / 2, 12 + i * 2);
		std::cout << global::highScores[i];
	}
}

void menu()
{
	StandartButton Play(20, 5, "PLAY", 26, 5);
	StandartButton Options(10, 5, "OPTIONS", 26, 22);
	StandartButton Quit(10, 5, "QUIT", 37, 22);
	Window highScoresWindow(20, 12, 26, 10);
	highScoresWindow.addWindowName("HIGH SCORES", 3, 0);
	highScoresWindow.show();

	printHighScores();

	Play.connect([&]()
		{
			system("cls");
			do 
			{ 
				Game tetris;
				tetris.run();
			} while (global::restart);
			system("cls");
			global::stopMenu = true;
		});
	Options.connect([&]() 
		{
			system("cls");
			globalOptions();
			system("cls");
			global::stopMenu = true;
		});
	Quit.connect([&]() 
		{
			if (dialogWindow("QUIT GAME?"))
			{
				global::stopMenu = true;
				global::stopGameLoop = true;
			}
			else
			{
				system("cls");
				printStandartTitleTetris(22, 0);
				Play.allowChanges();
				Play.show();
				Options.allowChanges();
				Options.show();
				Quit.allowChanges();
				Quit.show();
				highScoresWindow.show();
				printHighScores();
				setupInputHandling();
			}
		});
	printStandartTitleTetris(22, 0);
	global::stopMenu = false;
	setupInputHandling();
	while (!global::stopMenu)
	{
		invisibleCursor();
		mouseButtonInteraction(&Play, &Options, &Quit  );
	}
}