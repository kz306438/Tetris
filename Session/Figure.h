#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include "../consoleGUI/GUI.h"

namespace Tetris
{

	class Square
	{
	public:
		Square() = default;
		Square(int squarePositionX, int squarePositionY);
		Square(int squarePositionX, int squarePositionY, ConsoleColor squareColor);

		void setPosition(int newPositionX, int newPositionY);
		void setColor(ConsoleColor newSquareColor);

		std::pair<int, int> getPosition();
		ConsoleColor getColor();

		void clear(int posX, int posY);

		friend std::ostream& operator<<(std::ostream& os, const Square& obj);

	private:

		int m_SquarePositionX = 0;
		int m_SquarePositionY = 0;

		std::pair<char, char> m_Square = { '[', ']' };
		
		ConsoleColor m_SquareColor = White;
	};

	static std::ostream& operator<<(std::ostream& os, const Square& obj) {
		saveConsoleAttributes();
		setColorForeground(obj.m_SquareColor);
		os << obj.m_Square.first << obj.m_Square.second;
		restoreConsoleAttributes();
		return os;
	}

	class Figure
	{
	public:
		virtual ~Figure() = default;

		virtual void rotation() = 0;

		void clear();
		void render();

		void setPosition(int newPosX, int newPosY);

		std::pair<int, int> getPosition() const;
		std::pair<int, int> getAxisOfRotation() const;
		ConsoleColor getColor() const;

	public:
		std::vector<Square> coord;

	protected:
		int m_posX = 0;
		int m_posY = 0;

		std::pair<int, int> m_AxisOfRotation;

		ConsoleColor m_Color = White;
	};

	class OFigure : public Figure
	{
	public:

		OFigure(int posX, int posY);

		void rotation() override;

	private:
		void fill();
	};

	class LFigure : public Figure
	{
	public:
		LFigure(int posX, int posY);

		void rotation() override;

	private:
		void fill();
	};

	class SFigure : public Figure
	{
	public:
		SFigure(int posX, int posY);

		void rotation() override;

	private:
		void fill();
	};

	class ZFigure : public Figure
	{
	public:
		ZFigure(int posX, int posY);

		void rotation() override;

	private:
		void fill();

	};

	class IFigure : public Figure
	{
	public:
		IFigure(int posX, int posY);

		void rotation() override;
	private:
		void fill();

	};

	class JFigure : public Figure
	{
	public:
		JFigure(int posX, int posY);

		void rotation() override;
	private:
		void fill();
	};

	class TFigure : public Figure
	{
	public:
		TFigure(int posX, int posY);

		void rotation() override;
	private:
		void fill();
	};

}
