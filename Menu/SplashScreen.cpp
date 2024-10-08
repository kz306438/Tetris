#include "SplashScreen.h"
#include <Windows.h>
#include "../Images.h"
#include "MainMenu.h"
#include "../Sound/Sound.h"

namespace Tetris
{
	Tetris::SplashScreen::SplashScreen(Game& game)
		: m_Game(game),
		m_Field(30, 36, 0, 0)
	{
		fillField();
		setupActiveFigures();
	}

	SplashScreen::~SplashScreen()
	{
		for (auto& el : activeFigures)
		{
			delete el.figure;
		}
	}

	void SplashScreen::render()
	{
		m_Field.render();

		for (const auto& el : activeFigures)
		{
			renderActiveFigures(el.figure);
		}

		Tile::TitleTetris.render(13, 12);
	}

	void SplashScreen::update(float ts)
	{
		if (Application::pastTime.elapsedSeconds() < ts)
			return;

		if (checkInput())
		{
			Sounds::SplashcreenTheme.stop();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->play();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->setLoop(true);
			m_Game.SetMenu<MainMenu>();
		}

		updateActiveFigures();
		Application::pastTime.reset();
	}

	void SplashScreen::fillField()
	{
		Figure* I = new IFigure(0, 0);
		Figure* O = new OFigure(0, 0);
		Figure* T = new TFigure(0, 0);
		Figure* S = new SFigure(0, 0);
		Figure* Z = new ZFigure(0, 0);
		Figure* J = new JFigure(0, 0);
		Figure* L = new LFigure(0, 0);

		addFigure(I, 0, 27);
		addFigure(I, 20, 27);
		addFigure(I, 40, 27);
		addFigure(I, 60, 27);

		addFigure(O, 8, 28);
		addFigure(O, 20, 27);
		addFigure(O, 42, 27);

		addFigure(T, 26, 27);
		addFigure(T, 50, 27);
		T->rotation();
		addFigure(T, 12, 26);
		T->rotation();
		addFigure(T, 58, 26);

		addFigure(S, 4, 26);
		addFigure(S, 36, 27);
		S->rotation();
		addFigure(S, 16, 27);

		addFigure(Z, 46, 27);
		Z->rotation();
		addFigure(Z, 34, 27);

		addFigure(J, 12, 28);
		J->rotation(); J->rotation();
		addFigure(J, 64, 27);
		J->rotation();
		addFigure(J, 30, 27);
		addFigure(J, 54, 27);

		L->rotation();
		L->rotation();
		addFigure(L, 58, 27);
		addFigure(L, 24, 26);

		delete I; 
		delete O;
		delete T;
		delete S;
		delete Z;
		delete J;
		delete L;
	}

	void SplashScreen::addFigure(Figure* myFigure, int X, int Y)
	{
		myFigure->setPosition(X, Y);
		m_Field.addFigure(myFigure);
	}

	void SplashScreen::setupActiveFigures()
	{
		Timer t;

		activeFigures.push_back({ new IFigure(48, 5), 500, t });
		activeFigures.push_back({ new IFigure(66, 0), 800, t });
		activeFigures.push_back({ new OFigure(0, 5) , 400, t });
		activeFigures.push_back({ new TFigure(2, 0), 700, t });
		activeFigures.push_back({ new ZFigure(10, 7), 650, t });
		activeFigures.push_back({ new ZFigure(36, 5), 550, t });
		activeFigures.push_back({ new SFigure(32, 1), 520, t });
		activeFigures.push_back({ new JFigure(26, 7), 600, t });
		activeFigures.push_back({ new JFigure(42, 2), 630, t });
		activeFigures.push_back({ new LFigure(18, 2), 720, t });
		activeFigures.push_back({ new LFigure(64, 7), 670, t });

		activeFigures[1].figure->rotation();
		activeFigures[4].figure->rotation();
		activeFigures[6].figure->rotation();
		activeFigures[7].figure->rotation();
		activeFigures[7].figure->rotation();
		activeFigures[8].figure->rotation();
		activeFigures[8].figure->rotation();
		activeFigures[9].figure->rotation();
		activeFigures[9].figure->rotation();
	}

	void SplashScreen::renderActiveFigures(Figure* myFigure)
	{
		int posX = myFigure->getPosition().first;
		int posY = myFigure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = myFigure->coord[i].getPosition().first;
			int cellY = myFigure->coord[i].getPosition().second;

			if (posX + cellX < 12 || posX + cellX > 58 ||
				posY + cellY< 12 || posY + cellY > 17)
			{
				ConsoleManager::getInstance().SetCursorPosition
				(
					posX + cellX,
					posY + cellY
				);
				std::cout << myFigure->coord[i];
			}
		}
	}

	bool SplashScreen::figureIsFallen(Figure* myFigure)
	{
		int posX = myFigure->getPosition().first;
		int posY = myFigure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = myFigure->coord[i].getPosition().first;
			int cellY = myFigure->coord[i].getPosition().second;

			if (posY + cellY + 1 == 30 ||
				m_Field.getCell((posX + cellX) / 2, posY + cellY + 1).state == true)
			{
				return true;
			}
		}
		return false;
	}

	void SplashScreen::clearActiveFigure(Figure* myFigure)
	{
		int posX = myFigure->getPosition().first;
		int posY = myFigure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = myFigure->coord[i].getPosition().first;
			int cellY = myFigure->coord[i].getPosition().second;

			if (posX + cellX < 12 || posX + cellX > 58 ||
				posY + cellY < 12 || posY + cellY > 17)
			{
				myFigure->coord[i].clear(posX, posY);
			}
		}
	}

	void SplashScreen::drawLine(int startRow, int endRow, bool useBufferColor)
	{
		for (int i = startRow; i >= endRow; i--)
		{
			for (int j = 0; j < 72; j += 2)
			{
				ConsoleManager::getInstance().SetCursorPosition(j, i);
				if (useBufferColor)
				{
					saveConsoleAttributes();
					setColorForeground(m_Field.getCell(j / 2, i).color);
					std::cout << '[' << ']';
					restoreConsoleAttributes();
				}
				else
				{
					std::cout << '[' << ']';
				}
			}
		}
	}

	void SplashScreen::checkLine()
	{
		int cnt = 0;

		for (int i = 0; i < 30; i++)
		{
			if (isLineComplete(i))
			{
				cnt++;
			}
		}

		if (cnt > 0)
		{
			drawLine(29, 27, false);
			Sleep(100);
			drawLine(29, 25, true);
			Sleep(100);
			drawLine(29, 27, false);
			Sleep(100);
			deadLine(cnt);

			ConsoleManager::getInstance().SetCursorPosition(28, 21);
			std::cout << "press any key...";
		}
	}

	bool SplashScreen::checkInput()
	{
		if (_kbhit())
			return true;

		HWND consoleWindow = GetConsoleWindow();
		if (!consoleWindow) {
			std::cerr << "Failed to get console window handle.\n";
			return false;
		}

		POINT cursorPos;
		if (!GetCursorPos(&cursorPos)) {
			std::cerr << "Failed to get cursor position.\n";
			return false;
		}

		RECT consoleRect;
		if (!GetWindowRect(consoleWindow, &consoleRect)) {
			std::cerr << "Failed to get console window rectangle.\n";
			return false;
		}

		if (PtInRect(&consoleRect, cursorPos)) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				return true;
			}
		}

		return false;
	}

    void SplashScreen::deadLine(int y)
	{
		for (int i = m_Field.getHeight() - 1; i >= y; i--)
		{
			for (int j = 0; j < m_Field.getWidth(); j++)
			{
				m_Field.setCellColor(j, i, m_Field.getCell(j, i - y).color);
				m_Field.setCellState(j, i, m_Field.getCell(j, i - y).state);
			}
		}
		for (int i = 29; i >= 25; i--)
		{
			for (int j = 0; j < 72; j += 2)
			{
				saveConsoleAttributes();
				setColorForeground(m_Field.getCell(j / 2, i).color);
				ConsoleManager::getInstance().SetCursorPosition(j, i);
				std::cout << '[' << ']';
				restoreConsoleAttributes();
			}
		}

	}

	bool SplashScreen::isLineComplete(int rowIndex)
	{
		for (int j = 0; j < 36; j++)
		{
			if (!m_Field.getCell(j, rowIndex).state)
			{
				return false;
			}
		}
		return true;
	}

	void SplashScreen::updateActiveFigures()
	{
		for (auto& el : activeFigures)
		{
			if (el.figure != nullptr)
			{
				if (figureIsFallen(el.figure))
				{
					handleFallenFigure(el);
					el.figure = nullptr;
					checkLine();
				}
				else if (el.timer.elapsedMiliseconds() > el.delay)
				{
					moveFigureDown(el);
				}
			}
		}
	}

	void SplashScreen::handleFallenFigure(FigureInstance& el)
	{
		int posX = el.figure->getPosition().first;
		int posY = el.figure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = el.figure->coord[i].getPosition().first;
			int cellY = el.figure->coord[i].getPosition().second;

			m_Field.setCellState((posX + cellX) / 2, posY + cellY, true);
			m_Field.setCellColor((posX + cellX) / 2, posY + cellY, el.figure->getColor());
		}
	}

	void SplashScreen::moveFigureDown(FigureInstance& el)
	{
		int posX = el.figure->getPosition().first;
		int posY = el.figure->getPosition().second;

		clearActiveFigure(el.figure);
		el.figure->setPosition(posX, posY + 1);
		renderActiveFigures(el.figure);
		el.timer.reset();
	}

} // Tetris