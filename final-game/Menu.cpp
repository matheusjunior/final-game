#include <iostream>
#include "Menu.h"

void Menu::adjustText()
{
    if (singleInstance) {
//		colorPause.r = 255;
//		colorPause.g = 255;
//		colorPause.b = 255;
//
//		colorSelected.r = 255;
//		colorSelected.g = 255;
//		colorSelected.b = 0;
//
//		m_gameMainMenuOpt1 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2 - m_rightArrowX, SCREEN_HEIGHT / 2 - 45, 150 + m_rightArrowW, 25);
//		m_gameMainMenuOpt2 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2, SCREEN_HEIGHT / 2 - 25, 130, 25);
//		m_gameMainMenuOpt3 = loadFontAndSetPositionRef(SCREEN_WIDTH / 2 - 220 / 2, SCREEN_HEIGHT / 2 - 5, 75, 25);
//		m_gameMainMenuOpt1->displayText = "> New Game";
//		m_gameMainMenuOpt2->displayText = "Options";
//		m_gameMainMenuOpt3->displayText = "Exit";
//
//		m_gameMainMenuOpt1->color = colorSelected;
//		m_gameMainMenuOpt2->color = colorPause;
//		m_gameMainMenuOpt3->color = colorPause;
//
//		singleInstance = false;
    }
}

void Menu::updatePosition(Text *t, int px, int py, int w, int h)
{
    t->rect.x = px;
    t->rect.y = py;
    t->rect.w = w;
    t->rect.h = h;
}

Text *Menu::loadFontAndSetPositionRef(int px, int py, int w, int h)
{
    Text *text = new Text();
    text->font = TTF_OpenFont("media/emulogic.ttf", 20);
    if (!text->font) {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    }

    text->rect.x = px;
    text->rect.y = py;
    text->rect.w = w;
    text->rect.h = h;
    text->displayText = "Test";
    return text;
}

Text Menu::loadFontAndSetPosition(int px, int py, int w, int h)
{

    Text text;
    text.font = TTF_OpenFont("media/emulogic.ttf", 20);

    text.rect.x = px;
    text.rect.y = py;
    text.rect.w = w;
    text.rect.h = h;
    text.displayText = "Test";
    return text;
}

void Menu::updateSelection(int direction)
{
    if (direction == MENU_UP) {
        if (currSelectedOption == 1 || currSelectedOption == 2) {
            m_gameMainMenuOpt1->displayText = "> New Game";
            m_gameMainMenuOpt2->displayText = "Options";

            m_gameMainMenuOpt1->color = colorSelected;
            m_gameMainMenuOpt2->color = colorPause;
            currSelectedOption = 1;
        }
        else {
            m_gameMainMenuOpt1->displayText = "New Game";
            m_gameMainMenuOpt2->displayText = "> Options";

            m_gameMainMenuOpt1->color = colorPause;
            m_gameMainMenuOpt2->color = colorSelected;
            currSelectedOption = 2;
        }
        m_gameMainMenuOpt3->displayText = "Exit";
        m_gameMainMenuOpt3->color = colorPause;
    }
    else {
        if (direction == MENU_DOWN) {
            if (currSelectedOption == 2 || currSelectedOption == 3) {
                m_gameMainMenuOpt2->displayText = "Options";
                m_gameMainMenuOpt3->displayText = "> Exit";

                m_gameMainMenuOpt2->color = colorPause;
                m_gameMainMenuOpt3->color = colorSelected;
                currSelectedOption = 3;
            }
            else {
                m_gameMainMenuOpt1->displayText = "New Game";
                m_gameMainMenuOpt2->displayText = "> Options";
                m_gameMainMenuOpt3->displayText = "Exit";

                m_gameMainMenuOpt2->color = colorSelected;
                m_gameMainMenuOpt3->color = colorPause;
                currSelectedOption = 2;
            }
            m_gameMainMenuOpt1->displayText = "New Game";
            m_gameMainMenuOpt1->color = colorPause;
        }
    }
}

Text *Menu::getMainMenuOpt1()
{
    return m_gameMainMenuOpt1;
}

Text *Menu::getMainMenuOpt2()
{
    return m_gameMainMenuOpt2;
}

Text *Menu::getMainMenuOpt3()
{
    return m_gameMainMenuOpt3;
}