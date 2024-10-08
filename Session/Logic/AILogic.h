#pragma once

#include "Logic.h"
#include "../PlayField.h"
#include <vector>
#include <queue>
#include <climits>

namespace Tetris
{
	
	class AILogic : public Logic
	{
	public:
		AILogic(PlayField& field);

		void Control() override;
		void GetFigureOutOfBag() override;

	private:
		void ChooseBestFigure();
		void FindBestPosition();
		void FindPath();

		float FindEfficiency();
		int   FindNumOfIsolatedCells(std::vector<std::vector<bool>>& tempMap);
		int   FindNumOfRemovedLines (std::vector<std::vector<bool>>& tempMap);
		int   FindNumOfPits         (std::vector<std::vector<bool>>& tempMap);
		int   FindHighestPosition   (std::vector<std::vector<bool>>& tempMap);

		int  FindLowestCellPosition();
		int  FindHeightOfFigure();
		void MoveFigureToLeftEdge();
		void LowerFigure();
		bool CheckRightBorder();
		bool InsideMap();
		bool IsFallen();

	private:
		int   m_NumOfRotations = 0;
		bool  m_ReplaceFigure  = false;
		float m_Efficiency     = std::numeric_limits<float>::lowest();

		std::queue<std::string>  m_Path;
		std::pair<int, int>      m_FigurePosition;

		float m_HeightCoef        = 0.32f;
		float m_LineCoef          = 0.25f;
		float m_PitsCoef          = 0.75f;
		float m_IsolatedCellsCoef = 0.6625f;
		float m_DinamicHCoef      = 0.00425f;
		float m_DinamicICCoef     = 0.02775f;
	};

} // Tetris