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
