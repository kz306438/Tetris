#include "LevelData.h"
#include "../ConsoleManager.h"
#include <string>

namespace Tetris
{
	uint64_t LevelData::getScore() const
	{
		return m_Score;
	}

	int LevelData::getLevel() const
	{
		return m_Level;
	}

	int LevelData::getLines() const
	{
		return m_Lines;
	}

	void LevelData::render()
	{
		std::string data;
		data = std::to_string(m_Score);
		ConsoleManager::getInstance().SetCursorPosition(8, 16); std::cout << "SCORE";
		ConsoleManager::getInstance().SetCursorPosition(4 + (14 - data.size()) / 2, 17); std::cout << m_Score;

		data = std::to_string(m_Level);
		ConsoleManager::getInstance().SetCursorPosition(8, 19); std::cout << "LEVEL";
		ConsoleManager::getInstance().SetCursorPosition(4 + (14 - data.size()) / 2, 20); std::cout << m_Level;

		data = std::to_string(m_Lines);
		ConsoleManager::getInstance().SetCursorPosition(8, 22); std::cout << "LINES";
		ConsoleManager::getInstance().SetCursorPosition(4 + (14 - data.size()) / 2, 23); std::cout << m_Lines;
	}

	void LevelData::incScore()
	{
		m_Score++;
	}

	void LevelData::calculatePoints(int numOfLines)
	{
		if (numOfLines < 1 || numOfLines > 4)
			return;

		if(numOfLines == 1)
			m_Score += 100LL * m_Level;

		if (numOfLines == 2)
			m_Score += 300LL * m_Level;

		if (numOfLines == 3)
			m_Score += 500LL * m_Level;

		if (numOfLines == 4)
			m_Score += 800LL * m_Level;

		m_Lines += numOfLines;
		m_Level = m_Lines / 10 + 1;

		render();
	}

	void LevelData::resetData()
	{
		m_Score = 0;
		m_Level = 1;
		m_Lines = 0;
	}

} // Tetris