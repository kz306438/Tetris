#include "ConsoleManager.h"
#include <iostream>

ConsoleManager& ConsoleManager::getInstance()
{
    static ConsoleManager instance;
    return instance;
}

ConsoleManager::ConsoleManager()
{
    consoleWindow = GetConsoleWindow();
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleWindow == NULL || consoleOutput == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Не удалось получить дескриптор окна консоли или дескриптор вывода." << std::endl;
    }
}

ConsoleManager::~ConsoleManager() { }

void ConsoleManager::DisableResize()
{
    if (consoleWindow)
    {
        LONG_PTR style = GetWindowLongPtr(consoleWindow, GWL_STYLE);
        style &= ~WS_SIZEBOX;
        SetWindowLongPtr(consoleWindow, GWL_STYLE, style);
        SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

void ConsoleManager::SetTitle(const std::string& title)
{
    SetConsoleTitleA(title.c_str());
}

void ConsoleManager::SetSize(int width, int height)
{
    SMALL_RECT rect;
    COORD coord;

    coord.X = width;
    coord.Y = height;

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = height - 1;
    rect.Right = width - 1;

    SetConsoleScreenBufferSize(consoleOutput, coord);
    SetConsoleWindowInfo(consoleOutput, TRUE, &rect);
}

int ConsoleManager::GetWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(consoleOutput, &csbi))
    {
        return csbi.srWindow.Right - csbi.srWindow.Left + 1;
    }
    return 0;
}

int ConsoleManager::GetHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(consoleOutput, &csbi))
    {
        return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }
    return 0;
}

void ConsoleManager::DisableScrollbars()
{
    if (consoleOutput != INVALID_HANDLE_VALUE)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(consoleOutput, &csbi))
        {
            COORD newSize;
            newSize.X = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            newSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

            SetConsoleScreenBufferSize(consoleOutput, newSize);
        }
    }
}

void ConsoleManager::SetCursorPosition(int x, int y)
{
    if (consoleOutput != INVALID_HANDLE_VALUE)
    {
        COORD position = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(consoleOutput, position);
    }
}

void ConsoleManager::SetCursorVisibility(bool visible)
{
    if (consoleOutput != INVALID_HANDLE_VALUE)
    {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleOutput, &cursorInfo);
        cursorInfo.bVisible = visible;
        SetConsoleCursorInfo(consoleOutput, &cursorInfo);
    }
}

void ConsoleManager::SetFontSize(int width, int height)
{
    if (consoleOutput != INVALID_HANDLE_VALUE)
    {
        CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };
        GetCurrentConsoleFontEx(consoleOutput, FALSE, &cfi);
        cfi.dwFontSize.X = width;
        cfi.dwFontSize.Y = height;
        SetCurrentConsoleFontEx(consoleOutput, FALSE, &cfi);
    }
}

void ConsoleManager::ClearScreen() {
    if (consoleOutput != INVALID_HANDLE_VALUE) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = { 0, 0 };

        if (GetConsoleScreenBufferInfo(consoleOutput, &csbi)) {
            cellCount = csbi.dwSize.X * csbi.dwSize.Y;
            FillConsoleOutputCharacter(consoleOutput, ' ', cellCount, homeCoords, &count);
            FillConsoleOutputAttribute(consoleOutput, csbi.wAttributes, cellCount, homeCoords, &count);
            SetConsoleCursorPosition(consoleOutput, homeCoords);
        }
    }
}