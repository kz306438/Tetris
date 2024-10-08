#include "PlayField.h"
#include "../GameData.h"
#include "../Sound/Sound.h"
namespace Tetris
{

	PlayField::PlayField(int height, int width, int posX, int posY)
		: m_Height(height), m_Width(width),
	   	  m_posX(posX), m_posY(posY)
	{
		m_Field.resize(m_Height);
		for (auto &el : m_Field)
		{
			el.resize(m_Width, { false, Black });
		}
	}

	Cell PlayField::getCell(int x, int y) const
	{
		if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
			return m_Field[y][x];

		return { false, Black };
	}

	int PlayField::getHeight() const
	{
		return m_Height;
	}

	int PlayField::getWidth() const
	{
		return m_Width;
	}

	int PlayField::getPosX() const
	{
		return m_posX;
	}

	int PlayField::getPosY() const
	{
		return m_posY;
	}

	void PlayField::setCellState(int x, int y, bool state)
	{
		if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
			m_Field[y][x].state = state;
	}

	void PlayField::setCellColor(int x, int y, ConsoleColor clr)
	{
		if (x >= 0 && x < m_Width && y >= 0 && y < m_Height)
			m_Field[y][x].color = clr;
	}

	int PlayField::checkLine()
	{
		int countLine = 0;

		for (int i = 0; i < m_Height; i++)
		{
			bool lineIsFull = true;
			for (int j = 0; j < m_Width; j++)
			{
				if (m_Field[i][j].state == false)
					lineIsFull = false;
			}
			if (lineIsFull)
			{
				deadLine(i);
				countLine++;
			}
		}

		GameData::getInstance().TotalLinesRemoved += countLine;

		return countLine;
	}

	void PlayField::deadLine(int y)
	{
		Sounds::DeadLineSound.play();
		
		for (int i = y; i > 0; i--)
			m_Field[i] = m_Field[i - 1];

		for (int i = y; i >= 0; i--)
		{
			for (int j = 0; j < m_Width * 2; j += 2)
			{
				saveConsoleAttributes();
				setColorForeground(m_Field[i][j / 2].color);
				ConsoleManager::getInstance().SetCursorPosition(m_posX + j, m_posY + i);
				std::cout << '[' << ']';
				restoreConsoleAttributes();
			}
		}
	}

	void PlayField::addFigure(Figure* myFigure)
	{
		int posX = myFigure->getPosition().first - m_posX;
		int posY = myFigure->getPosition().second - m_posY;

		for (int i = 0; i < 4; i++)
		{
			setCellState((posX + myFigure->coord[i].getPosition().first) / 2,
				posY + myFigure->coord[i].getPosition().second, true);

			setCellColor((posX + myFigure->coord[i].getPosition().first) / 2,
				posY + myFigure->coord[i].getPosition().second, myFigure->coord[i].getColor());
		}
	}

	void PlayField::render()
	{
		for (int i = 0; i < m_Height; i++)
		{
			for (int j = 0; j < m_Width * 2; j += 2)
			{
				saveConsoleAttributes();
				setColorForeground(getCell(j / 2, i).color);
				setcur(m_posX + j, m_posY + i);
				std::cout << '[' << ']';
				restoreConsoleAttributes();
			}
		}
	}

	void PlayField::clear()
	{
		for (auto& row : m_Field)
		{
			for (auto& cell :row)
			{
				cell = { false, Black };
			}
		}
	}

} // Tetris