#pragma once
#include "Button.h"
#include <vector>
#include "SubmenuName.h"

class Submenu
{
public:
    Submenu();
    ~Submenu();

    void addButton(Button btn, size_t btnPos);

private:
    SubmenuName name;
    Button options[5];

};

