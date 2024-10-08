#pragma once
#include "Image.h"
#include <unordered_map>

namespace Tetris
{
	namespace Tile
	{
		inline Image TitleTetris("res/images/TitleTetris.txt");
		inline Image TitleGameOver("res/images/TitleGameOver.txt");
		inline Image PressedPauseImage("res/images/Pressed_Pause_Button.txt");
		inline Image DefaultPauseImage("res/images/Default_Pause_Button.txt");

		inline Image IFigure("res/images/IFigure_type1.txt", BrightCyan);
		inline Image TFigure("res/images/TFigure_type1.txt", BrightMagenta);
		inline Image JFigure("res/images/JFigure_type1.txt", BrightBlue);
		inline Image LFigure("res/images/LFigure_type1.txt", Yellow);
		inline Image OFigure("res/images/OFigure_type1.txt", BrightYellow);
		inline Image ZFigure("res/images/ZFigure_type1.txt", BrightRed);
		inline Image SFigure("res/images/SFigure_type1.txt", BrightGreen);

		/*inline Image ATypeText("res/images/AType.txt");
		inline Image BTypeText("res/images/BType.txt");
		inline Image CTypeText("res/images/CType.txt");*/

		inline std::unordered_map<ConsoleColor, Image*> TileMap =
		{
			{BrightCyan, &Tile::IFigure},
			{BrightMagenta, &Tile::TFigure},
			{BrightBlue, &Tile::JFigure},
			{Yellow, &Tile::LFigure},
			{BrightYellow, &Tile::OFigure},
			{BrightRed, &Tile::ZFigure},
			{BrightGreen, &Tile::SFigure},
		};

		inline std::vector<std::vector<std::vector<char>>> musicTypes =
		{
			{
				{'A', '-', 'T', 'Y', 'P', 'E'}
            },
			{
				{'B', '-', 'T', 'Y', 'P', 'E'}
            },
			{
				{'C', '-', 'T', 'Y', 'P', 'E'}
            }
		};
	}
} // Tetris