#include <iostream>
#include "consoleGUI/GUI.h"
#include <ctime>
#include "Variables.h"
#include <string>
#include <mmsystem.h>
#include "game.h"
#include "splashScreen.h"
#include "menu.h"
#include "dataManagment.h"


int main()
{
	std::system("mode con cols=73 lines=30");
	HWND console = GetConsoleWindow();
	SetConsoleTitleA("Tetris");
	loadUserData();
	splashScreen();
	while (!global::stopGameLoop)
	{
		menu();
	}
	saveUserData();
	return 0;
}
