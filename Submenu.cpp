#include "Submenu.h"



Submenu::Submenu()
{
}


Submenu::~Submenu()
{
}

void Submenu::addButton(MenuItem btn, size_t btnIdx)
{
    options[btnIdx] = btn;
}

void Submenu::btnAction(size_t btnIdx)
{
    if (btnIdx <= Submenu::MENU_SIZE) 
    {
        options[btnIdx].action();
    }
}

size_t Submenu::getNextX()
{
    return _x;
}

size_t Submenu::getBtnX()
{
    return _x + LEFT_OFFSET_TO_BTNS;
}

size_t Submenu::getBtnY(size_t btnIdx)
{
    size_t result = _y;
    if (btnIdx <= MENU_SIZE)
    {
        result += TOP_OFFSET_TO_BTNS;
        result += btnIdx * 50;
        result += btnIdx * OFFSET_BETWEEN_BTNS;
    }
    return result;
}

const std::string Submenu::getCaption(size_t btnIdx) const
{
    // TODO: insert return statement here
    return options[btnIdx].getCaption();
}

const size_t Submenu::getMenuSize() const
{
    return Submenu::MENU_SIZE;
}
