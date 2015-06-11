#ifndef MENU
#define MENU

#ifdef _WIN32
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <string>
#include "Text.h"
#include "Consts.h"

extern bool isGamePaused;
extern bool quit;

class Menu
{
private:
    const int m_rightArrowX = 34;
    const int m_rightArrowW = 30;
    int currSelectedOption = 1;
    bool singleInstance = true;
    Text *m_gameMainMenuOpt1;
    Text *m_gameMainMenuOpt2;
    Text *m_gameMainMenuOpt3;
    SDL_Color colorPause;
    SDL_Color colorSelected;

    void updatePosition(Text *t, int px, int py, int w, int h);

public:
    Menu() {
        colorPause.r = 255;
        colorPause.g = 255;
        colorPause.b = 255;

        colorSelected.r = 255;
        colorSelected.g = 255;
        colorSelected.b = 0;

        m_gameMainMenuOpt1 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2 - m_rightArrowX,
                SCREEN_HEIGHT / 2 - 45, 150 + m_rightArrowW, 25);
        m_gameMainMenuOpt2 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2, SCREEN_HEIGHT / 2 - 25, 130, 25);
        m_gameMainMenuOpt3 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2, SCREEN_HEIGHT / 2 - 5, 75, 25);

        m_gameMainMenuOpt1->displayText = "> New Game";
        m_gameMainMenuOpt2->displayText = "Options";
        m_gameMainMenuOpt3->displayText = "Exit";

        m_gameMainMenuOpt1->color = colorSelected;
        m_gameMainMenuOpt2->color = colorPause;
        m_gameMainMenuOpt3->color = colorPause;
    };

    Text static loadFontAndSetPosition(int px, int py, int w, int h);

    Text *loadFontAndSetPositionRef(int px, int py, int w, int h);

    void adjustText();

    void updateSelection(int direction);

    Text *getMainMenuOpt1();

    Text *getMainMenuOpt2();

    Text *getMainMenuOpt3();

    void handleEvent(SDL_Event e);
};


#endif