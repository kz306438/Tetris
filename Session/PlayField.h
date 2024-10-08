#pragma once

#include "../consoleGUI/GUI.h"
#include <vector>
#include "Figure.h"

namespace Tetris
{
	struct Cell
	{
		Cell() = default;
		Cell(bool state, ConsoleColor color) :
		state(state), color(color) {}
		ConsoleColor color;
		bool state;
	};

	class PlayField
	{
	public:
		PlayField() = default;
		PlayField(int height, int width, int m_posX, int m_posY);

		Cell getCell(int x, int y) const;
		int getHeight() const;
		int getWidth() const;
		int getPosX() const;
		int getPosY() const;


		void setCellState(int x, int y, bool state);
		void setCellColor(int x, int y, ConsoleColor clr);
		void addFigure(Figure* myFigure);

		int checkLine();
		void deadLine(int y);

		void render();

		void clear();

	private:
		std::vector<std::vector<Cell>> m_Field;

		int m_Height{};
		int m_Width{};

		int m_posX{};
		int m_posY{};
	};

} // Tetris
