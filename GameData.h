#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include "FileManager.h"
#include "Menu/OptionsMenu.h"

namespace Tetris
{
    void warningWindow();

    class GameData
    {
    public:
        GameData(const GameData&) = delete;
        GameData& operator=(const GameData&) = delete;

        static GameData& getInstance() {
            static GameData instance;
            return instance;
        }

        void loadUserData();
        void saveUserData();

        void updateTopScores(uint64_t score);

    private:

        GameData();
        ~GameData();
    public:
        std::vector<uint64_t> topScores;
        uint64_t score = 0;

        int moveRightKey = VK_RIGHT;
        int moveLeftKey = VK_LEFT;
        int rotateKey = VK_UP;
        int softDropKey = VK_DOWN;
        int hardDropKey = VK_SPACE;
        int holdKey = 'C';

        char menuMusicType = 'A';
        char gameMusicType = 'A';

        float musicVolume = 100.0f;
        float soundVolume = 100.0f;

        double motionDelay = 100.0;

        uint32_t MaxLines = 0;

        //ALL-TIME
        float TotalTime = 0.0f;
        uint64_t TotalGames = 0;
        uint64_t TotalLinesRemoved = 0;
        uint64_t TotalFigures = 0;
        uint64_t TotalScore = 0;

        //AVERAGE
        float AverageScore = 0.0f;
        float AverageLinesRemoved = 0.0f;
        float AverageFigures = 0.0f;
    };

} // Tetris
