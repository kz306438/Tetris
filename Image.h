#pragma once

#include <vector>
#include <string>
#include "consoleGUI/colors.h"
#include "ConsoleManager.h"

namespace Tetris
{
    class Image;

    class TetrisTitleRender
    {
    public:

        static TetrisTitleRender& get()
        {
           static TetrisTitleRender instance;
           return instance;
        }

        void render(int X, int Y);
    private:
        TetrisTitleRender();

        void setupImage();

        std::vector<Image> m_tetrisTitle;
    };


    class Image
    {

    public:

        Image(const std::vector<std::vector<char>>& inputPixels);
        Image(const std::vector<std::vector<char>>& inputPixels, ConsoleColor color);

        Image(const std::string& filePath);
        Image(const std::string& filePath, ConsoleColor color);

        void loadFromVector(const std::vector<std::vector<char>>& inputPixels);
        void loadFromFile(const std::string& filePath);

        void setPixel(int x, int y, char value);
        char getPixel(int x, int y) const;

        void render() const;
        void render(int x, int y) const;

        void fill(char fill_char);

        int getWidth() const;
        int getHeight() const;
        std::vector<std::vector<char>> getMatrix();

        void setFgColor(const ConsoleColor& clr);
        void setBgColor(const ConsoleColor& clr);

        void setPosition(int x, int y);
    private:

        std::vector<std::vector<char>> m_pixels;

        int m_width;
        int m_height;

        int m_posX = 0;
        int m_posY = 0;

        ConsoleColor fgColor = White;
        ConsoleColor bgColor = Black;
    };

} // Tetris
