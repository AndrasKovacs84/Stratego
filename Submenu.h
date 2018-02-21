#pragma once
#include "MenuItem.h"
#include <vector>
#include "SubmenuName.h"
#include <functional>

class Submenu
{
public:
    Submenu();
    ~Submenu();

    void addButton(MenuItem btn, size_t btnIdx);
    void btnAction(size_t btnIdx);

private:
    static const size_t MENU_SIZE = 5; //Max number of buttons the menu can accomodate
    //SubmenuName name; //Unnecessary as it is defined in main menu in a map?
    MenuItem options[MENU_SIZE];

};

