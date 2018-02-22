#include "MenuItem.h"



MenuItem::MenuItem()
{
}

MenuItem::MenuItem(std::string caption, std::function<void()> onClickAction) : pressed(false), caption(caption), onClickAction(onClickAction)
{
    //this->caption = caption;
    //this->onClickAction = onClickAction;
}

void MenuItem::action()
{
    onClickAction();
}

const std::string MenuItem::getCaption() const
{
    return caption;
}

bool MenuItem::isPressed()
{
    return pressed;
}

void MenuItem::setPressed(bool pressed)
{
    this->pressed = pressed;
}


MenuItem::~MenuItem()
{
}
