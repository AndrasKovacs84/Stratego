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
    size_t getNextX();
    size_t getBtnX();
    size_t getBtnY(size_t btnIdx);
    const std::string getCaption(size_t btnIdx) const;
    const size_t getMenuSize() const;

    static const size_t SCREEN_MIDDLE_X = 140; //Where the left edge of the menu needs to be so that the menu itself is completely centered on screen.
    static const size_t LEFT_OFFSET_TO_BTNS = 115;
    static const size_t TOP_OFFSET_TO_BTNS = 47;
    static const size_t OFFSET_BETWEEN_BTNS = 45;

private:


    size_t _x = SCREEN_MIDDLE_X;
    size_t _y = 0;

    static const size_t MENU_SIZE = 5; //Max number of buttons the menu can accomodate (limited by graphic design)
    MenuItem options[MENU_SIZE];

};

