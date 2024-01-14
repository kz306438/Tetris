#pragma once
#include "consoleGUI/colors.h"
#include <vector>
#include "figure.h"
#include "Timer.h"
#include "FileManager.h"

struct Cell
{
	Cell() = default;
	Cell(bool state, ConsoleColor color) :
		state(state), color(color) {}
	ConsoleColor color;
	bool state;
};
class Game
{
public:
	Game()
	{
		Cell defaultCell (false, Black);
		MAP.resize(Height, std::vector<Cell>(Width, defaultCell));
	}

	int numberActiveFigure(Figure* myFigure);

	void printFigureImage(Figure* myFigure, int posX, int posY);

	void controlFigure();

	bool isFallen();

	void updateMap();

	void goDown();

	void shaffleShapes();

	Figure* getNextFigure();

	void deadLine(int y);

	void printData();

	void checkLine();

	bool isDead();

	void setupGame();

	void updateNextWindow();
	
	void hold();
	
	void gameOver();

	void showGameObject();

	void run();
private:
	int Height = 20;
	int Width = 10;
	int mapPositionX = 26;
	int mapPositionY = 6;
	int spawnPositionX = mapPositionX + Width - 2;
	int spawnPositionY = mapPositionY;
	int figureSpeed = 1010;
	int score = global::score;
	int level = 1;
	int lines = 0;
	Figure* myFigure = nullptr;
	Figure* nextFigure = nullptr;
	Figure* holdFigure = nullptr;
	std::vector<Figure*> bag;
	Timer gameMusicTimer;
	Timer delayMoveRight;
	Timer delayMoveLeft;
	Timer delayRotate;
	bool isCanUseHold = true;
	std::vector<std::vector<Cell>> MAP;
};

