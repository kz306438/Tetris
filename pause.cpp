#include "pause.h"
#include "consoleGUI/GUI.h"
#include "Variables.h"
#include "settings.h"


int pauseMenu()
{
	int returnValue = 0 ;
	Window pauseWindow(42, 27, 15, 2);
	pauseWindow.addWindowName("PAUSE", 16, 0);
	pauseWindow.show();
	StandartButton resume(20, 5, "RESUME", 26, 7);
	StandartButton options(20, 5, "OPTIONS", 26, 13);
	StandartButton quit(20, 5, "QUIT", 26, 19);

	resume.connect([&]()
		{
			global::stopPause = true;
			returnValue = 1;
		});
	options.connect([&]() 
		{
			pauseOptions();
			pauseWindow.show();
			resume.allowChanges();
			resume.show();
			options.allowChanges();
			options.show();
			quit.allowChanges();
			quit.show();
			setupInputHandling();
		});
	quit.connect([&]()
		{
			if (dialogWindow("QUIT GAME?"))
			{
				global::stopGame = true;
				returnValue = 2;
				global::stopPause = true;
			}
			else
			{
				pauseWindow.show();
				pauseWindow.show();
				resume.allowChanges();
				resume.show();
				options.allowChanges();
				options.show();
				quit.allowChanges();
				quit.show();
				setupInputHandling();
			}
			
		});
	global::stopPause = false;

	setupInputHandling();
	while (!global::stopPause)
	{
		mouseButtonInteraction(&resume, &options, &quit);
	}
	return returnValue;
}