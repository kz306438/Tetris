#pragma once
#include <windows.h>
#include <string>

class ConsoleManager
{
public:
    static ConsoleManager& getInstance();

    ConsoleManager(const ConsoleManager&) = delete;
    ConsoleManager& operator=(const ConsoleManager&) = delete;

    void DisableResize();
    void SetTitle(const std::string& title);
    void SetSize(int width, int height);
    int GetWidth();
    int GetHeight();
    void DisableScrollbars();
    void SetCursorPosition(int x, int y);
    void SetCursorVisibility(bool visible);
    void SetFontSize(int width, int height);
    void ClearScreen();

private:
    ConsoleManager();
    ~ConsoleManager();

    HWND consoleWindow;
    HANDLE consoleOutput;
};

