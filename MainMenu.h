#pragma once
#include "Submenu.h"
#include "SubmenuName.h"
#include "States.h"
#include <map>
#include <functional>

class MainMenu
{
public:
    MainMenu();
    void initMenu();
    ~MainMenu();

    Submenu& getSubmenu(SubmenuName name);
private:

    //Submenu init functions:
    Submenu initMainMenu();
    Submenu initNewGameMenu();
    Submenu initHowToPlayMenu();
    Submenu initExitMenu();
    Submenu initMultiplayerMenu();
    Submenu initMultiHostMenu();
    Submenu initMultiJoinMenu();

    //SubmenuName currentSubmenu;
    std::map<SubmenuName, Submenu> submenus;

};

