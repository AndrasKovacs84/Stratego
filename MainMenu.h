#pragma once
#include "Submenu.h"
#include "SubmenuName.h"
#include <map>

class MainMenu
{
public:
    MainMenu();
    void initMenu();
    ~MainMenu();
private:
    SubmenuName currentSubmenu;
    std::map<SubmenuName, Submenu> submenus;

};

