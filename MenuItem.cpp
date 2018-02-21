#include "MenuItem.h"



MenuItem::MenuItem()
{
}

MenuItem::MenuItem(std::string caption, std::function<void()> onClickAction)
{
    this->caption = caption;
    this->onClickAction = onClickAction;
}

void MenuItem::action()
{
    onClickAction();
}

const std::string& MenuItem::getCaption() const
{
    return caption;
}


MenuItem::~MenuItem()
{
}
