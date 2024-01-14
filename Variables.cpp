#include "Variables.h"
#include <Windows.h>
namespace global
{
	std::vector<std::vector<std::vector<char>>> imageFigures =
{
	{
/*I*/	{leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture},
	    {' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
    },
	{
	    {' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, ' '},
/*T*/	{' ', ' ', ' ', leftSideTexture, rightSideTexture, ' ', ' ', ' '},
    },
	{
/*J*/	{' ',leftSideTexture, rightSideTexture, ' ', ' ', ' ', ' ', ' '},
		{' ', leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,' '},
    },
	{
/*L*/	{' ', ' ', ' ', ' ', ' ', leftSideTexture, rightSideTexture,' '},
	    {' ', leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,leftSideTexture, rightSideTexture,' '},
    },
	{
/*O*/	{' ', ' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, ' ', ' '},
	    {' ', ' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, ' ', ' '},
    },
	{
/*Z*/	{' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture,' ', ' ', ' '},
	    {' ', ' ', ' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, ' '}
    },
	{
/*S*/	{' ', ' ', ' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture, ' '},
	    {' ', leftSideTexture, rightSideTexture, leftSideTexture, rightSideTexture,' ', ' ', ' '}
    }
};
	std::vector<int> highScores = { 0, 0, 0, 0, 0 };
    int score = 0;
    char leftSideTexture = '[';
    char rightSideTexture = ']';
    bool stopMenu = true;
    bool stopGameLoop = false;
    bool stopSettings = true;
	bool stopPause = true;
	bool stopGame = true;
	bool restart = false;
    FileManager fileManager("userData.txt");
    int moveRightKey = VK_RIGHT;
    int moveLeftKey = VK_LEFT;
    int rotateKey = VK_UP;
    int softDropKey = VK_DOWN;
    int hardDropKey = 32;
    int holdKey = 'C';

    int soundVolume = 100;
}

void updateImageFigures()
{
    global::imageFigures =
{
	{
/*I*/	{ global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture},
	    {' ', ' ', ' ', ' ',' ', ' ', ' ', ' '},
    },
	{
	    {' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture, ' '},
/*T*/	{' ', ' ', ' ',  global::leftSideTexture,  global::rightSideTexture, ' ', ' ', ' '},
    },
	{
/*J*/	{' ', global::leftSideTexture,  global::rightSideTexture, ' ', ' ', ' ', ' ', ' '},
		{' ',  global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture,' '},
    },
	{
/*L*/	{' ', ' ', ' ', ' ', ' ',  global::leftSideTexture,  global::rightSideTexture,' '},
	    {' ',  global::leftSideTexture,  global::rightSideTexture, global::leftSideTexture, global::rightSideTexture, global::leftSideTexture,  global::rightSideTexture,' '},
    },
	{
/*O*/	{' ', ' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture, ' ', ' '},
	    {' ', ' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture, ' ', ' '},
    },
	{
/*Z*/	{' ',  global::leftSideTexture, global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture,' ', ' ', ' '},
	    {' ', ' ', ' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture, ' '}
    },
	{
/*S*/	{' ', ' ', ' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture, ' '},
	    {' ',  global::leftSideTexture,  global::rightSideTexture,  global::leftSideTexture,  global::rightSideTexture,' ', ' ', ' '}
    }
};
}