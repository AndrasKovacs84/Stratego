#pragma once
#include "Submenu.h"
#include "SubmenuName.h"
#include "States.h"
#include "InputParser.h"
#include "BackgroundAnimState.h"

#include <map>
#include <functional>

class MainMenu
{
public:
    MainMenu();
    void initMenu();
    ~MainMenu();

    Submenu& getSubmenu(SubmenuName name);

    int getNextY(bool top);
    void setAnimation(BackgroundAnimState animation);
    bool isAnimated();

private:

    int progressTowards(int from, int targetY);

    BackgroundAnimState currentTopAnimState;
    BackgroundAnimState currentBottomAnimState;

    int topCurrentY;
    int bottomCurrentY;

    static const int TOP_CLOSING_TARGET_Y = 0;
    static const int TOP_OPENING_TARGET_Y = -260;
    static const int BOTTOM_CLOSING_TARGET_Y = 260;
    static const int BOTTOM_OPENING_TARGET_Y = 520;


    //Submenu init functions:
    Submenu initMainMenu();
    Submenu initNewGameMenu();
    Submenu initHowToPlayMenu();
    Submenu initExitMenu();
    Submenu initMultiplayerMenu();
    Submenu initMultiHostMenu();
    Submenu initMultiJoinMenu();

    SubmenuName previousSubmenu;
    std::map<SubmenuName, Submenu> submenus;


};

