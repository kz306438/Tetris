#include "settings.h"
#include "consoleGUI/GUI.h"
#include "Variables.h"
#include "dataManagment.h"

bool dialogWindow(const std::string& head);
void popUpForChangeButton(const std::string& head, const std::string& text, int& keyForChange);
std::string GetKeyName(int keyCode);
void showGlobalOptionsObject();
void showPauseOptionsObject();

std::vector<std::vector<std::vector<char>>> textureFigure =
{
        {
        {' ', '[', ']', '[', ']', '[', ']', ' '},
        {' ', ' ', ' ', '[', ']', ' ', ' ', ' '},
        },
        {
        {' ', char(219),  char(219),  char(219),  char(219),  char(219),  char(219), ' '},
        {' ', ' ', ' ',  char(219),  char(219), ' ', ' ', ' '},
        },
    };

StandartButton moveRight(16, 3, GetKeyName(global::moveRightKey), 16, 2);
StandartButton moveLeft(16, 3, GetKeyName(global::moveLeftKey), 16, 5);
StandartButton rotate(16, 3, GetKeyName(global::rotateKey), 16, 8);
StandartButton done(16, 3, "DONE", 28, 26);
StandartButton softDrop(16, 3, GetKeyName(global::softDropKey), 52, 2);
StandartButton hardDrop(16, 3, GetKeyName(global::hardDropKey), 52, 5);
StandartButton hold(16, 3, GetKeyName(global::holdKey), 52, 8);
StandartButton resetHighScores(21, 3, "RESET HIGH SCORES", 8, 21);
StandartButton resetOptions(20, 3, "RESET OPTIONS", 44, 21);
SliderButton soundVolume(0, 20, "SOUND VOLUME", global::soundVolume / 5, 5, 7, 14, SliderButton::Orientation::HORIZONTAL);
ScrollButton texture(textureFigure, 48, 16, ScrollButton::Orientation::HORIZONTAL);

std::string GetKeyName(int keyCode) {
    switch (keyCode) {
    case 13: return "ENTER";
    case 32: return "SPACE";
    case 9: return "TAB";
    case 27: return "ESCAPE";
    case VK_LEFT: return "LEFT ARROW";
    case VK_UP: return "UP ARROW";
    case VK_RIGHT: return "RIGHT ARROW";
    case VK_DOWN: return "DOWN ARROW";
    default: return std::string(1, char(keyCode));
    }
}

bool isCanChangeName(int key)
{
    int cnt = 0;
    if (key == global::moveRightKey)cnt++;
    if (key == global::moveLeftKey)cnt++;
    if (key == global::rotateKey)cnt++;
    if (key == global::softDropKey)cnt++;
    if (key == global::hardDropKey)cnt++;
    if (key == global::holdKey)cnt++;
    if (cnt >= 2) return false;
    else return true;
}

void setupGlobalOptionsButton()
{
    moveRight.setName(GetKeyName(global::moveRightKey));
    moveLeft.setName(GetKeyName(global::moveLeftKey));
    rotate.setName(GetKeyName(global::rotateKey));
    softDrop.setName(GetKeyName(global::softDropKey));
    hardDrop.setName(GetKeyName(global::hardDropKey));
    hold.setName(GetKeyName(global::holdKey));
    texture.addName("FIGURE TEXTURE", 47, 14);
    texture.setForegroundColor(BrightMagenta);
    if (global::leftSideTexture == '[')texture.nextSlide(0);
    else texture.nextSlide(1);
    moveRight.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "MOVE RIGHT", global::moveRightKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
            moveRight.setName(GetKeyName(global::moveRightKey));
        });
    moveLeft.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "MOVE LEFT", global::moveLeftKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
            moveLeft.setName(GetKeyName(global::moveLeftKey));
        });
    rotate.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "ROTATE", global::rotateKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
            rotate.setName(GetKeyName(global::rotateKey));
        });
    done.connect([&]()
        {
            global::stopSettings = true;
            saveUserData();
        });
    softDrop.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "SOFT DROP", global::softDropKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
           softDrop.setName(GetKeyName(global::softDropKey));
        });
    hardDrop.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "HARD DROP", global::hardDropKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
            hardDrop.setName(GetKeyName(global::hardDropKey));
        });
    hold.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "HOLD", global::holdKey);
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
             hold.setName(GetKeyName(global::holdKey));
        });
    soundVolume.connect([&]()
        {
            global::soundVolume -= 5;
        },
        [&]()
        {
            global::soundVolume += 5;
        });
    texture.connect(
        [&]()
        {
            int num = texture.getSlideNumber();
            if (num == 0)
            {
                global::leftSideTexture = '[';
                global::rightSideTexture = ']';
            }
            else if (num == 1)
            {
                global::leftSideTexture = char(219);
                global::rightSideTexture = char(219);
            }
            updateImageFigures();
        },
        [&]()
        {
            int num = texture.getSlideNumber();
            if (num == 0)
            {
                global::leftSideTexture = '[';
                global::rightSideTexture = ']';
            }
            else if (num == 1)
            {
                global::leftSideTexture = char(219);
                global::rightSideTexture = char(219);
            }
            updateImageFigures();
        });
    resetHighScores.connect([&]() 
        {
            if (dialogWindow("RESET HIGH SCORES?"))
            {
                global::highScores = { 0, 0, 0, 0, 0 };
            }
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
        });
    resetOptions.connect([&]()
        {
            if(dialogWindow("RESET OPTIONS?"))
            {
                global::leftSideTexture = '[';
                global::rightSideTexture = ']';
                global::moveRightKey = VK_RIGHT;
                global::moveLeftKey = VK_LEFT;
                global::rotateKey = VK_UP;
                global::softDropKey = VK_DOWN;
                global::hardDropKey = 32;
                global::holdKey = 'C';
                setupGlobalOptionsButton();
                showGlobalOptionsObject();
            }
            system("cls");
            showGlobalOptionsObject();
            setupInputHandling();
        });

    moveRight.changePosition(16, 2);
    moveLeft.changePosition(16, 5);
    rotate.changePosition(16, 8);
    softDrop.changePosition(52, 2);
    hardDrop.changePosition(52, 5);
    hold.changePosition(52, 8);
    soundVolume.changePosition(7, 14);
    done.changePosition(28, 26);
}

void setupPauseOptionsButton()
{
    moveRight.setName(GetKeyName(global::moveRightKey));
    moveLeft.setName(GetKeyName(global::moveLeftKey));
    rotate.setName(GetKeyName(global::rotateKey));
    softDrop.setName(GetKeyName(global::softDropKey));
    hardDrop.setName(GetKeyName(global::hardDropKey));
    hold.setName(GetKeyName(global::holdKey));

    moveRight.changePosition(35, 3);
    moveLeft.changePosition(35, 6);
    rotate.changePosition(35, 9);
    softDrop.changePosition(35, 12);
    hardDrop.changePosition(35, 15);
    hold.changePosition(35, 18);
    soundVolume.changePosition(25, 21);
    done.changePosition(28, 25);

    moveRight.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "MOVE RIGHT", global::moveRightKey);
            showPauseOptionsObject();
            setupInputHandling();
            moveRight.setName(GetKeyName(global::moveRightKey));
        });
    moveLeft.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "MOVE LEFT", global::moveLeftKey);
            showPauseOptionsObject();
            setupInputHandling();
            moveLeft.setName(GetKeyName(global::moveLeftKey));
        });
    rotate.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "ROTATE", global::rotateKey);
            showPauseOptionsObject();
            setupInputHandling();
            rotate.setName(GetKeyName(global::rotateKey));
        });
    softDrop.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "SOFT DROP", global::softDropKey);
            showPauseOptionsObject();
            setupInputHandling();
            softDrop.setName(GetKeyName(global::softDropKey));
        });
    hardDrop.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "HARD DROP", global::hardDropKey);
            showPauseOptionsObject();
            setupInputHandling();
            hardDrop.setName(GetKeyName(global::hardDropKey));
        });
    hold.connect([&]()
        {
            popUpForChangeButton("PRESS THE DESIRED KEY FOR", "HOLD", global::holdKey);
            showPauseOptionsObject();
            setupInputHandling();
            hold.setName(GetKeyName(global::holdKey));
        });
    soundVolume.connect([&]()
        {
            global::soundVolume -= 5;
        },
        [&]()
        {
            global::soundVolume += 5;
        });
}

void showGlobalOptionsObject()
{
    moveRight.allowChanges();
    moveRight.show();
    moveLeft.allowChanges();
    moveLeft.show();
    rotate.allowChanges();
    rotate.show();
    softDrop.allowChanges();
    softDrop.show();
    hardDrop.allowChanges();
    hardDrop.show();
    hold.allowChanges();
    hold.show();
    soundVolume.allowChanges();
    soundVolume.show();
    texture.allowChanges();
    texture.show();
    resetHighScores.allowChanges();
    resetHighScores.show();
    resetOptions.allowChanges();
    resetOptions.show();
    done.allowChanges();
    done.show();

    setcur(2, 3); std::cout << "MOVE RIGHT";
    setcur(2, 6); std::cout << "MOVE LEFT";
    setcur(2, 9); std::cout << "ROTATE";
    setcur(38, 3); std::cout << "SOFT DROP";
    setcur(38, 6); std::cout << "HARD DROP";
    setcur(38, 9); std::cout << "HOLD";
}

void showPauseOptionsObject()
{
    Window optionsWindow(42, 27, 15, 2);
    optionsWindow.addWindowName("OPTIONS", 15, 0);
    optionsWindow.show();

    setcur(21, 4); std::cout << "MOVE RIGHT";
    setcur(21, 7); std::cout << "MOVE LEFT";
    setcur(21, 10); std::cout << "ROTATE";
    setcur(21, 13); std::cout << "SOFT DROP";
    setcur(21, 16); std::cout << "HARD DROP";
    setcur(21, 19); std::cout << "HOLD";

    moveRight.allowChanges();
    moveRight.show();
    moveLeft.allowChanges();
    moveLeft.show();
    rotate.allowChanges();
    rotate.show();
    softDrop.allowChanges();
    softDrop.show();
    hardDrop.allowChanges();
    hardDrop.show();
    hold.allowChanges();
    hold.show();
    soundVolume.allowChanges();
    soundVolume.show();
}

void popUpForChangeButton(const std::string &head, const std::string &text, int &keyForChange)
{
    bool stopWindow = false;

    Window popUpWindow(40, 10, 16, 10);
    popUpWindow.show();
     
    StandartButton cancel(12, 3, "CANCEL", 30, 16);
    cancel.connect([&]() { stopWindow = true; });
    setcur(36 - head.size() / 2, 11);
    std::cout << head;

    setcur(36 - text.size() / 2, 13);
    std::cout << text;  

    setupInputHandling();
    while (!stopWindow)
    {
        mouseButtonInteraction(&cancel);
        if (_kbhit())
        {
            int temp = keyForChange;
            keyForChange = _getch();
            keyForChange = _getch();
            keyForChange = toupper(keyForChange);
            if (keyForChange == 0x50)keyForChange = VK_DOWN;
            if (keyForChange == 0x48)keyForChange = VK_UP;
            if (keyForChange == 0x4B)keyForChange = VK_LEFT;
            if (keyForChange == 0x4D)keyForChange = VK_RIGHT;
            if (!isCanChangeName(keyForChange))keyForChange = temp;
            stopWindow = true;
        }
    }
}

bool dialogWindow(const std::string& head)
{
    bool returnValue = true;
    bool stopDialogWindow = false;
    Window dialogWindow(40, 8, 16, 10);
    dialogWindow.show();

    StandartButton OK(16, 3, "OK", 19, 14);
    StandartButton cancel(16, 3, "CANCEL", 37, 14);
    OK.connect([&]()
        {
            stopDialogWindow = true;
            returnValue = true;
        });
    cancel.connect([&]()
        {
            stopDialogWindow = true;
            returnValue = false;
        });
    setcur(36 - head.size() / 2, 11);
    std::cout << head;
    
    while (!stopDialogWindow)
    {
        mouseButtonInteraction(&OK, &cancel);
    }
    return returnValue;
}


void pauseOptions()
{
    setupPauseOptionsButton();
    showPauseOptionsObject();

    bool stopPauseOptions = false;

    done.connect([&]()
        {
            stopPauseOptions = true;
            saveUserData();
        });

    setupInputHandling();
    while (!stopPauseOptions)
    {
        invisibleCursor();
        mouseButtonInteraction(&moveRight, &moveLeft, &rotate, &done, &softDrop, &hardDrop, &hold, &soundVolume);
        done.allowChanges();
        done.show();
    }
}

void globalOptions()
{
    setupGlobalOptionsButton();
	global::stopSettings = false;
    showGlobalOptionsObject();
	setupInputHandling();
	while (!global::stopSettings)
	{
		invisibleCursor();
		mouseButtonInteraction(&moveRight, &moveLeft, &rotate, &done, &softDrop, &hardDrop, &hold, &soundVolume, &texture, &resetHighScores, &resetOptions);
	}
}