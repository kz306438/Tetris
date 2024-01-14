#include "game.h"
#include "Variables.h"
#include "Images.h"
#include "dataManagment.h"
#include "pause.h"
#include <SFML/Audio.hpp>

bool upKeyIsPressed = false;

int Game::numberActiveFigure(Figure* myFigure)
{
	if (IFigure* myTFigure = dynamic_cast<IFigure*>(myFigure))
	{
		return 0;
	}
	else  if (TFigure* myTFigure = dynamic_cast<TFigure*>(myFigure))
	{
		return 1;
	}
	else if (JFigure* myTFigure = dynamic_cast<JFigure*>(myFigure))
	{
		return 2;
	}
	else  if (LFigure* myTFigure = dynamic_cast<LFigure*>(myFigure))
	{
		return 3;
	}
	else  if (OFigure* myTFigure = dynamic_cast<OFigure*>(myFigure))
	{
		return 4;
	}
	else if (ZFigure* myTFigure = dynamic_cast<ZFigure*>(myFigure))
	{
		return 5;
	}
	else  if (SFigure* myTFigure = dynamic_cast<SFigure*>(myFigure))
	{
		return 6;
	}
	return -1;
}

void Game::printFigureImage(Figure* myFigure, int posX, int posY)
{
	int index = numberActiveFigure(myFigure);
	ConsoleColor clr = myFigure->figure[0].getColor();
	saveConsoleAttributes();
	setColorForeground(clr);
	for (int i = 0; i < global::imageFigures[index].size(); i++)
	{
		for (int j = 0; j < global::imageFigures[index][i].size(); j++)
		{
			setcur(posX + j, posY + i);
			std::cout << global::imageFigures[index][i][j];
		}
	}
	restoreConsoleAttributes();
}

void Game::controlFigure()
{
	if (!upKeyIsPressed &&(GetAsyncKeyState(global::rotateKey) & 0x8000))
	{
		bool flag = true;
		myFigure->clear();
		myFigure->rotation();
		for (int i = 0; i < 4; i++)
		{
			if (myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX > Width * 2 - 2 ||
				myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX < 0 ||
				myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY >= Height ||
				MAP[myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX) / 2].state == true)
			{
				flag = false;
			}
		}
		if (!flag)
		{
			myFigure->rotation(); myFigure->rotation(); myFigure->rotation();
		}
		myFigure->show();
		delayRotate.reset();
		upKeyIsPressed = true;
	}
	else if ((GetAsyncKeyState(global::rotateKey) & 0x8000) == 0)
	{
		upKeyIsPressed = false;
	}
	if (delayMoveRight.elapsedMiliseconds() > 100 && (GetAsyncKeyState(global::moveRightKey) & 0x8000))
	{
		myFigure->clear();
		bool flag = true;
		std::pair<int, int> pos = myFigure->getPosition();
		for (int i = 0; i < 4; i++)
		{
			if (pos.first + myFigure->figure[i].getPosition().first - mapPositionX + 2 == Width * 2 ||
				MAP[myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX) / 2 + 1].state == true)flag = false;
		}
		if (flag)myFigure->setPosition(pos.first + 2, pos.second);
		myFigure->show();
		delayMoveRight.reset();
	}
	if (delayMoveLeft.elapsedMiliseconds() > 100 && (GetAsyncKeyState(global::moveLeftKey) & 0x8000))
	{
		myFigure->clear();
		bool flag = true;
		std::pair<int, int> pos = myFigure->getPosition();
		for (int i = 0; i < 4; i++)
		{
			if (pos.first + myFigure->figure[i].getPosition().first - mapPositionX == 0 ||
				MAP[myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX) / 2 - 1].state == true)flag = false;
		}
		if (flag)myFigure->setPosition(pos.first - 2, pos.second);
		myFigure->show();
		delayMoveLeft.reset();
	}
	if (GetAsyncKeyState(global::holdKey) & 0x8000)
	{
		if (isCanUseHold)hold();
	}
	else
	{
		myFigure->show();
	}
}

bool Game::isFallen()
{
	for (int i = 0; i < 4; i++)
	{
		if (myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY + 1 == Height ||
			MAP[myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY + 1][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX) / 2].state == true)
		{
			return true;
		}
	}
	return false;
}

void Game::updateMap()
{
	for (int i = 0; i < 4; i++)
	{
		std::pair<int, int> posFigure = myFigure->getPosition();
		std::pair<int, int> posSquare = myFigure->figure[i].getPosition();
		MAP[posFigure.second + posSquare.second - mapPositionY][(posFigure.first + posSquare.first - mapPositionX) / 2].state = true;
		MAP[posFigure.second + posSquare.second - mapPositionY][(posFigure.first + posSquare.first - mapPositionX) / 2].color = myFigure->figure[i].getColor();
	}
}

void Game::goDown()
{
	myFigure->clear();
	myFigure->setPosition(myFigure->getPosition().first, myFigure->getPosition().second + 1);
}

void Game::shaffleShapes()
{
	std::vector<Figure*> shapes =
	{
		new IFigure(spawnPositionX, spawnPositionY),
		new OFigure(spawnPositionX, spawnPositionY),
		new TFigure(spawnPositionX, spawnPositionY),
		new SFigure(spawnPositionX, spawnPositionY),
		new ZFigure(spawnPositionX, spawnPositionY),
		new JFigure(spawnPositionX, spawnPositionY),
		new LFigure(spawnPositionX, spawnPositionY)
	};
	bag = shapes;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(bag.begin(), bag.end(), g);
}

Figure* Game::getNextFigure()
{
	if (bag.empty())shaffleShapes();
	Figure* myFigure = bag[bag.size() - 1];
	bag.pop_back();
	return myFigure;
}

void Game::deadLine(int y)
{
	for (int i = y; i > 0; i--)
	{
		MAP[i] = MAP[i - 1];
	}
	for (int i = y; i >= 0; i--)
	{
		for (int j = 0; j < Width * 2; j += 2)
		{
			saveConsoleAttributes();
			setColorForeground(MAP[i][j / 2].color);
			setcur(mapPositionX + j, mapPositionY + i);
			std::cout << global::leftSideTexture << global::rightSideTexture;
			restoreConsoleAttributes();
		}
	}

}

void Game::printData()
{
	std::string s;
	s = std::to_string(score);
	setcur(8, 16); std::cout << "SCORE";
	setcur(4 + (14 - s.size()) / 2, 17); std::cout << score;

	setcur(8, 19); std::cout << "LEVEL";
	setcur(10, 20); std::cout << level;

	s = std::to_string(lines);
	setcur(8, 22); std::cout << "LINES";
	setcur(4 + (14 - s.size()) / 2, 23); std::cout << lines;
}

void Game::checkLine()
{
	int countLine = 0;
	for (int i = 0; i < Height; i++)
	{
		bool flag = true;
		for (int j = 0; j < Width; j++)
		{
			if (MAP[i][j].state == false)flag = false;
		}
		if (flag)
		{
			deadLine(i);
			countLine++;
		}
	}
	switch (countLine)
	{
	case 1:
		score += 100 * level;
		break;
	case 2:
		score += 300 * level;
		break;
	case 3:
		score += 500 * level;
		break;
	case 4:
		score += 800 * level;
		break;
	}
	lines += countLine;
	level = lines / 10 + 1;
	printData();
}

bool Game::isDead()
{
	for (int i = 0; i < 4; i++)
	{
		if (MAP[myFigure->getPosition().second + myFigure->figure[i].getPosition().second - mapPositionY][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first - mapPositionX) / 2].state == true)
		{
			return true;
		}
	}
	return false;
}

void Game::setupGame()
{
	global::stopGame = false;

	score = 0;
	level = 1;
	lines = 0;

	Window gameWindow(1 + Width * 2 + 1, 1 + Height + 1, mapPositionX - 1, mapPositionY - 1);
	gameWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	gameWindow.show();

	Window nextFigureWindow(14, 7, 54, 5);
	nextFigureWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	nextFigureWindow.addWindowName("NEXT", 5, 1);
	nextFigureWindow.show();
	printFigureImage(nextFigure, 57, 8);

	Window holdFigureWindow(14, 7, 4, 5);
	holdFigureWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	holdFigureWindow.addWindowName("HOLD", 5, 1);
	holdFigureWindow.show();

	Window dataWindow(14, 13, 4, 14);
	dataWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	dataWindow.show();
	printData();
}

void Game::updateNextWindow()
{
	printFigureImage(nextFigure, 57, 8);
}

void Game::hold()
{
	if (holdFigure == nullptr)
	{
		holdFigure = myFigure;
		holdFigure->clear();
		printFigureImage(holdFigure, 7, 8);
		nextFigure->setPosition(spawnPositionX, spawnPositionY);
		myFigure = nextFigure;
		nextFigure = getNextFigure();
		checkLine();
		updateNextWindow();
	}
	else
	{
		Figure* tempFigure = myFigure;
		holdFigure->setPosition(spawnPositionX, spawnPositionY);
		myFigure = holdFigure;

		holdFigure = tempFigure;
		holdFigure->clear();
		printFigureImage(holdFigure, 7, 8);
	}
	isCanUseHold = false;
}

void Game::showGameObject()
{
	printStandartTitleTetris(22, 0);

	Window gameWindow(1 + Width * 2 + 1, 1 + Height + 1, mapPositionX - 1, mapPositionY - 1);
	gameWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	gameWindow.show();

	Window nextFigureWindow(14, 7, 54, 5);
	nextFigureWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	nextFigureWindow.addWindowName("NEXT", 5, 1);
	nextFigureWindow.show();

	Window holdFigureWindow(14, 7, 4, 5);
	holdFigureWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	holdFigureWindow.addWindowName("HOLD", 5, 1);
	holdFigureWindow.show();

	Window dataWindow(14, 13, 4, 14);
	dataWindow.setTexture(char(220), char(220), char(223), char(223), char(220), char(223), char(219), char(219));
	dataWindow.show();
	printData();

	if (holdFigure != nullptr)printFigureImage(holdFigure, 7, 8);
	printFigureImage(nextFigure, 57, 8);

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width * 2; j += 2)
		{
			saveConsoleAttributes();
			setColorForeground(MAP[i][j / 2].color);
			setcur(mapPositionX + j, mapPositionY + i);
			std::cout << global::leftSideTexture << global::rightSideTexture;
			restoreConsoleAttributes();
		}
	}
}

void Game::gameOver()
{
	bool stopGameOver = false;
	system("cls");
	titleGameOver(16, 5);
	setcur(16, 14); std::cout << "YOUR SCORE " << score;
	setcur(16, 17); std::cout << "HIGH SCORE " << global::highScores[0];
	StandartButton home(18, 5, "HOME", 16, 20);
	StandartButton restart(18, 5, "RESTART", 37, 20);
	home.connect([&]()
		{
			global::restart = false;
			stopGameOver = true;
		});
	restart.connect([&]()
		{
			global::restart = true;
			stopGameOver = true;
		});

	setupInputHandling();
	while (!stopGameOver)
	{
		mouseButtonInteraction(&home, &restart);
	}
	system("cls");
}

void Game::run()
{
	sf::Music gameMusic;
	gameMusic.openFromFile("music\\game_music.mp3");
	gameMusic.play();
	gameMusic.setVolume(static_cast<float>(global::soundVolume));
	gameMusic.setLoop(true);
	std::vector<std::vector<char>> pauseImagePressed =
	{
		{char(220),char(220),char(220),char(220),char(220),char(220),char(220), char(220), char(220)},
		{char(219), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(219)},
		{char(219),char(32), char(32), char(219), char(32), char(219), char(32),char(32), char(219)},
		{char(219), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(219)},
		{char(223),char(223),char(223),char(223),char(223),char(223), char(223), char(223), char(223)}
	};
	std::vector<std::vector<char>> pauseImageDefault =
	{
		{char(201),char(205),char(205),char(205),char(205),char(205),char(205), char(205), char(187)},
		{char(186), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(186)},
		{char(186),char(32), char(32), char(219), char(32), char(219), char(32),char(32), char(186)},
		{char(186), char(32), char(32), char(32), char(32), char(32),char(32),char(32), char(186)},
		{char(200),char(205),char(205),char(205),char(205),char(205), char(205), char(205), char(188)}
	};
	CustomButton pauseButton(pauseImageDefault, pauseImagePressed, 56, 22);
	pauseButton.connect([&]()
		{
			gameMusic.pause();
			int temp = pauseMenu();
			if(temp == 1)
			{
				system("cls");
				showGameObject();
				gameMusic.play();
				pauseButton.allowChanges();
				pauseButton.show();
				setupInputHandling();
			}
			gameMusic.setVolume(static_cast<float>(global::soundVolume));
		});

	printStandartTitleTetris(22, 0);

	invisibleCursor();

	shaffleShapes();
	myFigure = getNextFigure();
	nextFigure = getNextFigure();

	setupGame();

	Timer t, t1;
	double time = 0;
	setupInputHandling();
	while (!isDead() && !global::stopGame)
	{
		time = t.elapsedMiliseconds();
		controlFigure();
		if (isFallen())
		{
			figureSpeed = 1010 - level * 40;
			if (time >= 300)
			{
				updateMap();
				t.reset();
				time = 0;
				nextFigure->clear();
				nextFigure->setPosition(spawnPositionX, spawnPositionY);
				myFigure = nextFigure;
				nextFigure = getNextFigure();
				checkLine();
				updateNextWindow();
				isCanUseHold = true;
			}
		}
		else if (time >= figureSpeed)
		{
			if (figureSpeed == 40 || figureSpeed == 0)
			{
				score++;
				printData();
			}
			goDown();
			t.reset();
		}
		if (GetAsyncKeyState(global::softDropKey) & 0x8000) {
			figureSpeed = 40;
		}
        else if (GetAsyncKeyState(global::hardDropKey) & 0x8000)
		{
			figureSpeed = 0;
		}
		else 
		{
			figureSpeed = 1010 - level * 40;
		}
		mouseButtonInteraction(&pauseButton);
	}
	if (!global::stopGame)
	{
		myFigure->show();
	}
	global::score = score;
	updateHighScores();
	gameMusic.stop();
	global::restart = false;
	if(!global::stopGame)gameOver();
}