#pragma once
#include <iostream>

namespace Tetris
{

	class LevelData
	{
	public:

		uint64_t getScore() const;
		int      getLevel() const;
		int      getLines() const;

		void render();
		void incScore();
		void calculatePoints(int numOfLines);

		void resetData();

	private:
		uint64_t m_Score = 0;
		int      m_Level = 1;
		int      m_Lines = 0;
	};

} // Tetris