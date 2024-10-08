#include "AILogic.h"
#include "../../Images.h"
#include "../../consoleGUI/GUI.h"
namespace Tetris
{

	AILogic::AILogic(PlayField& field)
		: Logic(field)
	{
		figureSpeed = NORMAL_FALL_SPEED;
	}

	/*virtual*/ void AILogic::Control()
	{
		while (!m_Path.empty())
		{
			std::string cmd = m_Path.front();
			m_Path.pop();
			if (cmd == "REPLACE")
			{
				hold();
			}
			else if (cmd == "ROTATE")
			{
				activeFigure->clear();
				activeFigure->rotation();
				activeFigure->render();
			}
			else if (cmd == "RIGHT")
			{
				activeFigure->clear();
				activeFigure->setPosition(activeFigure->getPosition().first + 2, activeFigure->getPosition().second);
				activeFigure->render();
			}
			else if (cmd == "LEFT")
			{
				activeFigure->clear();
				activeFigure->setPosition(activeFigure->getPosition().first - 2, activeFigure->getPosition().second);
				activeFigure->render();
			}
		}
		activeFigure->render();
	}

	
	/*virtual*/ void AILogic::GetFigureOutOfBag()
	{
		if (activeFigure)
		{
			nextFigure->clear();
			nextFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = nextFigure;
			nextFigure = defineNextFigure();
			Tile::TileMap[nextFigure->getColor()]->render(Field.getPosX() + Field.getWidth() * 2 + 11, 8);
		}
		else
		{
			activeFigure = defineNextFigure();
			nextFigure = defineNextFigure();
		}
		isCanUseHold = true;

		ChooseBestFigure();
		//FindBestPosition();
		FindPath();
	}

	bool AILogic::InsideMap()
	{
		int posX = activeFigure->getPosition().first;
		int posY = activeFigure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = activeFigure->coord[i].getPosition().first;
			int cellY = activeFigure->coord[i].getPosition().second;

			if ((posX + cellX - Field.getPosX() == 0) ||
				(posX + cellX - Field.getPosX() + 2 == Field.getWidth() * 2) ||
				Field.getCell((posX + cellX - Field.getPosY() - 2) / 2,
				               posY + cellY - Field.getPosX()).state == true)
			{
				return false;
			}

		}
		return true;
	}

	bool AILogic::IsFallen()
	{
		int posX = activeFigure->getPosition().first - Field.getPosX();
		int posY = activeFigure->getPosition().second - Field.getPosY();

		for (int i = 0; i < 4; i++)
		{
			int cellX = activeFigure->coord[i].getPosition().first;
			int cellY = activeFigure->coord[i].getPosition().second;

			if (posY + cellY + 1 == Field.getHeight() ||
				Field.getCell((posX + cellX) / 2,
					posY + cellY + 1).state == true)
			{
				return true;
			}
		}
		return false;
	}

	float AILogic::FindEfficiency()
	{
		std::vector<std::vector<bool>> tempMap(Field.getHeight(), std::vector<bool>(Field.getWidth()));

		for (int i = 0; i < Field.getHeight(); i++)
		{
			for (int j = 0; j < Field.getWidth(); j++)
			{
				tempMap[i][j] = Field.getCell(j, i).state;
			}
		}

		int figureHeight                = FindHeightOfFigure();
		int	numberOfIsolatedCellsBefore = FindNumOfIsolatedCells(tempMap);
		int numberOfThePitsBefore       = FindNumOfPits(tempMap);


		int posX = activeFigure->getPosition().first - Field.getPosX();
		int posY = activeFigure->getPosition().second - Field.getPosY();
		for (int i = 0; i < 4; i++)
		{
			int cellX = activeFigure->coord[i].getPosition().first;
			int cellY = activeFigure->coord[i].getPosition().second;

			tempMap[posY + cellY][(posX + cellX) / 2] = true;
		}

		int highestPosition            = FindHighestPosition   (tempMap);
		int	numberOfIsolatedCellsAfter = FindNumOfIsolatedCells(tempMap);
		int numberOfThePitsAfter       = FindNumOfPits         (tempMap);
		int numberOfRemovedLines       = FindNumOfRemovedLines (tempMap);

		float efficiency;

		efficiency = (m_HeightCoef - m_DinamicHCoef * (Field.getHeight() - highestPosition - 1)) * figureHeight +
		              m_LineCoef * numberOfRemovedLines +
			         (m_IsolatedCellsCoef + m_DinamicICCoef * highestPosition) * (numberOfIsolatedCellsBefore - numberOfIsolatedCellsAfter) +
			         m_PitsCoef * (numberOfThePitsBefore - numberOfThePitsAfter);
 
		return efficiency;
	}

	int AILogic::FindLowestCellPosition()
	{
		int ans = INT_MIN;

		for (int i = 0; i < 4; i++)
		{
			int cellY = activeFigure->coord[i].getPosition().second;

			if (ans < cellY)ans = cellY;
		}
		return ans + activeFigure->getPosition().second - Field.getPosY();
	}

	int AILogic::FindNumOfIsolatedCells(std::vector<std::vector<bool>>& tempMap)
	{
		int countIsolatedCells = 0;
		for (int j = 0; j < Field.getWidth(); j++)
		{
			bool isIsolated = false;
			for (int i = 0; i < Field.getHeight(); i++)
			{
				if (tempMap[i][j] == true)
					isIsolated = true;
				if (tempMap[i][j] == false && isIsolated)
					countIsolatedCells++;
			}
		}
		return countIsolatedCells;
	}

	int AILogic::FindNumOfPits(std::vector<std::vector<bool>>& tempMap)
	{
		int countPits = 0;
		for (int j = 0; j < Field.getWidth(); j++)
		{
			bool isPit = false;
			bool flag = true;
			int cnt = 0;
			for (int i = 0; i < Field.getHeight(); i++)
			{
				if ((j == 0 && tempMap[i][j] == false && tempMap[i][j + 1] == true) ||
					(j == Field.getWidth() - 1 && tempMap[i][j - 1] == true && tempMap[i][j] == false) ||
					(j > 0 && j < Field.getWidth() - 1 && tempMap[i][j - 1] == true && tempMap[i][j] == false && tempMap[i][j + 1] == true))
				{
					isPit = true;
				}

				if (tempMap[i][j] == true)
					flag = false;

				if (isPit == true && tempMap[i][j] == false && flag)
					cnt++;
			}
			if (cnt > 2)countPits++;
		}
		return countPits;
	}

	int AILogic::FindHighestPosition(std::vector<std::vector<bool>>& tempMap)
	{
		for (int i = 0; i < Field.getHeight(); i++)
		{
			for (int j = 0; j < Field.getWidth(); j++)
			{
				if (tempMap[i][j] == true)return i;
			}
		}
		return Field.getHeight() - 1;
	}

	int AILogic::FindHeightOfFigure()
	{
		int ans = INT_MAX;
		for (int i = 0; i < 4; i++)
		{
			int posY = activeFigure->getPosition().second + activeFigure->coord[i].getPosition().second - Field.getPosY();
			
			if (ans > posY)
			{
				ans = posY;
			}
		}
		return ans;
	}

	void AILogic::FindPath()
	{
		while (!m_Path.empty()) { m_Path.pop(); }

		if (m_ReplaceFigure)m_Path.push("REPLACE");

		for (int i = 0; i < m_NumOfRotations; i++)
			m_Path.push("ROTATE");

		int shiftX = (m_FigurePosition.first - activeFigure->getPosition().first) / 2;
		int shiftY = m_FigurePosition.second - activeFigure->getPosition().second;

		for (int i = 0; i < abs(shiftX); i++)
		{
			if (shiftX > 0)m_Path.push("RIGHT");
			else m_Path.push("LEFT");
		}
	}

	void AILogic::MoveFigureToLeftEdge()
	{
		while (InsideMap())
		{
			activeFigure->setPosition
			(
				activeFigure->getPosition().first - 2,
				activeFigure->getPosition().second
			);
		}
	}

	void AILogic::LowerFigure()
	{
		while (!IsFallen())
		{
			activeFigure->setPosition
			(
				activeFigure->getPosition().first,
				activeFigure->getPosition().second + 1
			);
		}
	}

	void AILogic::ChooseBestFigure()
	{
		FindBestPosition();

		float   myFigureEfficiency        = m_Efficiency;
		int     myFigureNumberOfRotations = m_NumOfRotations;
		std::pair<int, int>  myfigurePosition = m_FigurePosition;

		std::shared_ptr<Figure>  tempFigure = activeFigure;

		m_ReplaceFigure = false;

		if (holdFigure == nullptr)
		{
			nextFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = nextFigure;
			FindBestPosition();
			if (m_Efficiency > myFigureEfficiency)
			{
				m_ReplaceFigure = true;
			}
			else
			{
				m_NumOfRotations = myFigureNumberOfRotations;
				m_FigurePosition = myfigurePosition;
			}
			activeFigure = tempFigure;
		}
		else
		{
			holdFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = holdFigure;
			FindBestPosition();
			if (m_Efficiency > myFigureEfficiency)
			{
				m_ReplaceFigure = true;
			}
			else
			{
				m_NumOfRotations = myFigureNumberOfRotations;
				m_FigurePosition = myfigurePosition;
			}
			activeFigure = tempFigure;
		}
	}

	bool AILogic::CheckRightBorder()
	{
		int posX = activeFigure->getPosition().first;
		int posY = activeFigure->getPosition().second;

		for (int i = 0; i < 4; i++)
		{
			int cellX = activeFigure->coord[i].getPosition().first;
			int cellY = activeFigure->coord[i].getPosition().second;

			if ((posX + cellX - Field.getPosX() == Field.getWidth() * 2) ||
				Field.getCell((posX + cellX - Field.getPosX()) / 2,
					posY + cellY - Field.getPosY()).state == true)
			{
				return false;
			}
		}
		return true;
	}

	int AILogic::FindNumOfRemovedLines(std::vector<std::vector<bool>>& tempMap)
	{
		int countLine = 0;
		for (int i = 0; i < Field.getHeight(); i++)
		{
			bool flag = true;
			for (int j = 0; j < Field.getWidth(); j++)
			{
				if (tempMap[i][j] == false)flag = false;
			}
			if (flag)
			{
				countLine++;
			}
		}
		return countLine;
	}

	void AILogic::FindBestPosition()
	{
		m_Efficiency = INT_MIN;
		m_FigurePosition = { 0, 0 };
		m_NumOfRotations = 0;

		for (int r = 0; r < 4; r++)
		{
			activeFigure->rotation();
			MoveFigureToLeftEdge();

			while (CheckRightBorder())
			{
				LowerFigure();
				float efficiency = FindEfficiency();
				if (efficiency > m_Efficiency)
				{
					m_Efficiency = efficiency;
					m_NumOfRotations = r + 1;
					m_FigurePosition = activeFigure->getPosition();
				}
				activeFigure->setPosition(activeFigure->getPosition().first + 2, spawnPositionY);
			}
			activeFigure->setPosition(spawnPositionX, spawnPositionY);
		}
		activeFigure->setPosition(spawnPositionX, spawnPositionY);
	}

} // Tetris