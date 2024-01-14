#include "splashScreen.h"
#include "figure.h"
#include "Timer.h"
#include "Images.h"
#include "game.h"
#include <SFML/Audio.hpp>
struct triple
{
	Figure* figure;
	int delay;
	Timer timer;
};
Cell defaultCell(false, Black);
std::vector<std::vector<Cell>> buffer(30, std::vector<Cell>(36, defaultCell));
std::vector<triple> activeFigures;

bool figureIsFallen(Figure* myFigure)
{
	for (int i = 0; i < 4; i++)
	{
		if (myFigure->getPosition().second + myFigure->figure[i].getPosition().second + 1 == 30 ||
			buffer[myFigure->getPosition().second + myFigure->figure[i].getPosition().second + 1][(myFigure->getPosition().first + myFigure->figure[i].getPosition().first) / 2].state == true)
		{
			return true;
		}
	}
	return false;
}

void addFigureImage(Figure* myFigure, int posX, int posY)
{
	myFigure->setPosition(posX, posY);
	for (int i = 0; i < 4; i++)
	{
		buffer[myFigure->figure[i].getPosition().second + posY][(myFigure->figure[i].getPosition().first + posX)/2].state = true;
		buffer[myFigure->figure[i].getPosition().second + posY][(myFigure->figure[i].getPosition().first + posX)/2].color = myFigure->figure[i].getColor();
	}
	myFigure->show();
}

void deadLine(int y)
{
	for (int i = 29; i >= y; i--)
	{
		buffer[i] = buffer[i - y];
	}
	for (int i = 29; i >= 25; i--)
	{
		for (int j = 0; j < 72; j += 2)
		{
			saveConsoleAttributes();
			setColorForeground(buffer[i][j / 2].color);
			setcur(j, i);
			std::cout << global::leftSideTexture << global::rightSideTexture;
			restoreConsoleAttributes();
		}
	}

}

void checkLine()
{
	int cnt = 0;
	for (int i = 0; i < 30; i++)
	{
		bool flag = true;
		for (int j = 0; j < 36; j++)
		{
			if (buffer[i][j].state == false)flag = false;
		}
		if (flag)
		{
			cnt++;
		}
	}

	if (cnt > 0)
	{
		for (int i = 29; i >= 27; i--)
		{
			for (int j = 0; j < 72; j += 2)
			{
				setcur(j, i);
				std::cout << global::leftSideTexture << global::rightSideTexture;
			}
		}
		Sleep(100);
		for (int i = 29; i >= 25; i--)
		{
			for (int j = 0; j < 72; j += 2)
			{
				saveConsoleAttributes();
				setColorForeground(buffer[i][j / 2].color);
				setcur(j, i);
				std::cout << global::leftSideTexture << global::rightSideTexture;
				restoreConsoleAttributes();
			}
		}
		Sleep(100);
		for (int i = 29; i >= 27; i--)
		{
			for (int j = 0; j < 72; j += 2)
			{
				setcur(j, i);
				std::cout << global::leftSideTexture << global::rightSideTexture;
			}
		}
		Sleep(100);
		deadLine(cnt);
	}
}

void printFiguresOnISplashScreen()
{
	std::vector<Figure*> figures =
	{
	  new IFigure(5 ,5),
	  new OFigure(20, 3),
	  new TFigure(14, 2),
	  new SFigure(35, 4),
	  new ZFigure(50, 1),
	  new JFigure(30, 8),
	  new LFigure(60,1)
	};

	addFigureImage(figures[0], 0, 27);
	addFigureImage(figures[0], 20, 27);
	addFigureImage(figures[0], 40, 27);
	addFigureImage(figures[0], 60, 27);


	addFigureImage(figures[1], 8, 28);
	addFigureImage(figures[1], 20, 27);
	addFigureImage(figures[1], 42, 27);

	addFigureImage(figures[2], 26, 27);
	addFigureImage(figures[2], 50, 27);
	figures[2]->rotation();
	addFigureImage(figures[2], 12, 26);
	figures[2]->rotation();
	addFigureImage(figures[2], 58, 26);

	addFigureImage(figures[3], 4, 26);
	addFigureImage(figures[3], 36, 27);
	figures[3]->rotation();
	addFigureImage(figures[3], 16, 27);

	addFigureImage(figures[4], 46, 27);
	figures[4]->rotation();
	addFigureImage(figures[4], 34, 27);

	addFigureImage(figures[5], 12, 28);
	figures[5]->rotation(); figures[5]->rotation();
	addFigureImage(figures[5], 64, 27);
	figures[5]->rotation();
	addFigureImage(figures[5], 30, 27);
	addFigureImage(figures[5], 54, 27);

	figures[6]->rotation();
	figures[6]->rotation();
	addFigureImage(figures[6], 58, 27);
	addFigureImage(figures[6], 24, 26);

	Timer t;

	Figure* i1 = new IFigure(48, 5);
	activeFigures.push_back({ i1 , 500, t });
	i1->show();

	Figure* i2 = new IFigure(66, 0);
	i2->rotation();
	activeFigures.push_back({ i2, 800, t });
	i2->show();

	Figure* o1 = new OFigure(0, 5);
	activeFigures.push_back({ o1 , 400, t });
	o1->show();

	Figure* t1 = new TFigure(2, 0);
	activeFigures.push_back({ t1, 700, t });
	t1->show();

	Figure* z1 = new ZFigure(10, 7);
	z1->rotation();
	activeFigures.push_back({ z1, 650, t });
	z1->show();

	Figure* z2 = new ZFigure(36, 5);
	activeFigures.push_back({ z2, 550, t });
	z2->show();

	Figure* s1 = new SFigure(32, 1);
	s1->rotation();
	activeFigures.push_back({ s1, 520, t });
	s1->show();

	Figure* j1 = new JFigure(26, 7);
	j1->rotation(); j1->rotation();
	activeFigures.push_back({ j1, 600, t });
	j1->show();

	Figure* j2 = new JFigure(42, 2);
	j2->rotation(); j2->rotation();
	activeFigures.push_back({ j2, 630, t });
	j2->show();

	Figure* l1 = new LFigure(18, 2);
	l1->rotation(); l1->rotation();
	activeFigures.push_back({ l1, 720, t });
	l1->show();

	Figure* l2 = new LFigure(64, 7);
	activeFigures.push_back({ l2, 670, t });
	l2->show();
}

void cleanActiveFigures(Figure* myFigure)
{
	std::pair<int, int> pos = myFigure->getPosition();
	for (int i = 0; i < 4; i++)
	{
		std::pair<int, int> posSquare = myFigure->figure[i].getPosition();
		if (pos.first + posSquare.first < 12 || pos.first + posSquare.first > 58 ||
			pos.second + posSquare.second < 12 || pos.second + posSquare.second > 17)
		{
			myFigure->figure[i].clear(pos.first, pos.second);
		}
	}
}

void showActiveFigures(Figure* myFigure)
{
	std::pair<int, int> pos = myFigure->getPosition();
	for (int i = 0; i < 4; i++)
	{
		std::pair<int, int> posSquare = myFigure->figure[i].getPosition();
		if (pos.first + posSquare.first < 12 || pos.first + posSquare.first > 58 ||
			pos.second + posSquare.second < 12 || pos.second + posSquare.second > 17)
		{
			setcur(pos.first + posSquare.first, pos.second + posSquare.second);
			std::cout << myFigure->figure[i];
		}
	}
}

void splashScreenLogic()
{
	for (int i = 0; i < activeFigures.size(); i++)
	{
		if (activeFigures[i].figure != nullptr && figureIsFallen(activeFigures[i].figure))
		{
			for (int j = 0; j < 4; j++)
			{
				buffer[activeFigures[i].figure->figure[j].getPosition().second + activeFigures[i].figure->getPosition().second][(activeFigures[i].figure->figure[j].getPosition().first + activeFigures[i].figure->getPosition().first) / 2].state = true;
				buffer[activeFigures[i].figure->figure[j].getPosition().second + activeFigures[i].figure->getPosition().second][(activeFigures[i].figure->figure[j].getPosition().first + activeFigures[i].figure->getPosition().first) / 2].color = activeFigures[i].figure->figure[j].getColor();
			}
			activeFigures[i].figure = nullptr;
			checkLine();
		}
		else
		{
			if (activeFigures[i].figure != nullptr && activeFigures[i].timer.elapsedMiliseconds() > activeFigures[i].delay)
			{
				cleanActiveFigures(activeFigures[i].figure);
				activeFigures[i].figure->setPosition(activeFigures[i].figure->getPosition().first, activeFigures[i].figure->getPosition().second + 1);
				showActiveFigures(activeFigures[i].figure);
				activeFigures[i].timer.reset();
			}
		}
	}
}

void splashScreen()
{
	srand(time(0));
	Timer t;

	invisibleCursor();
	printFiguresOnISplashScreen();
	printTitleTetris(13, 12);
	sf::Music music;
	music.openFromFile("music\\splashScreen_music.mp3");
	music.play();
	music.setVolume(static_cast<float>(global::soundVolume));
	setupInputHandling();
	while (true)
	{
		invisibleCursor();
		splashScreenLogic();
		if (_kbhit())break;
		if (t.elapsedSeconds() > 22.3)
		{
			setcur(28, 21);
			std::cout << "press any key...";
		}
	}
	system("cls");
}