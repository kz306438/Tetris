#pragma once

#include "Menu.h"
#include "../Game.h"
#include <vector>
#include "../Session/Figure.h"
#include "../Session/PlayField.h"

namespace Tetris
{
	class Game;

	class SplashScreen : public Menu
	{
	public:
		SplashScreen(Game& game);

		~SplashScreen();

		void render() override;
		void update(float ts) override;

		struct FigureInstance
		{
			Figure* figure;
			double delay;
			Timer timer;
		};


	private:
		void fillField();
		void addFigure(Figure* myFigure, int X, int Y);
		void setupActiveFigures();
		void renderActiveFigures(Figure* myFigure);
		bool figureIsFallen(Figure* myFigure);
		void clearActiveFigure(Figure* myFigure);
		void drawLine(int startRow, int endRow, bool useBufferColor);
		void checkLine();
		bool checkInput();
		void deadLine(int y);
		bool isLineComplete(int rowIndex);
		void handleFallenFigure(FigureInstance& el);
		void moveFigureDown(FigureInstance& el);
		void updateActiveFigures();

	private:
		std::vector<FigureInstance> activeFigures;

		Game& m_Game;
		PlayField m_Field;
	};

} // Tetris