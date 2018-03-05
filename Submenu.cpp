#include "Submenu.h"



Submenu::Submenu() : _x(Submenu::SCREEN_LEFT_EDGE), _y(0), currentAnimState(SubmenuAnimState::LEFT_TO_CENTER) {}


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

int Submenu::getNextX()
{
    int target = 0;
    if (currentAnimState == SubmenuAnimState::NOT_ANIMATED) return _x;
    if (currentAnimState == SubmenuAnimState::CENTER_TO_RIGHT) target = Submenu::SCREEN_RIGHT_EDGE;
    if (currentAnimState == SubmenuAnimState::LEFT_TO_CENTER) target = Submenu::SCREEN_MIDDLE_X;
    _x += progressTowards(_x, target);
    if (_x == target) 
    { 
        currentAnimState = SubmenuAnimState::NOT_ANIMATED; 
        //_x = Submenu::SCREEN_MIDDLE_X;
    }
    return _x;
}

int Submenu::getBtnX()
{
    return _x + LEFT_OFFSET_TO_BTNS;
}

int Submenu::getBtnY(size_t btnIdx)
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
    return options[btnIdx].getCaption();
}

const size_t Submenu::getMenuSize() const
{
    return Submenu::MENU_SIZE;
}

bool Submenu::isBtnPressed(size_t btnIdx)
{
    return options[btnIdx].isPressed();
}

void Submenu::setBtnPress(size_t btnIdx, bool pressed)
{
    options[btnIdx].setPressed(pressed);
}

void Submenu::setMessage(std::vector<std::string>& message)
{
    messageText = message;
}

const std::vector<std::string> Submenu::getMsg()
{
    return messageText;
}

void Submenu::clearPresses()
{
    for (size_t i = 0; i < Submenu::MENU_SIZE; i++)
    {
        if (options[i].isPressed())
        {
            options[i].setPressed(false);
        }
    }
}

void Submenu::setAnimState(SubmenuAnimState nextState)
{
    currentAnimState = nextState;
}

void Submenu::setX(int x)
{
    _x = x;
}

bool Submenu::isAnimated()
{
    return currentAnimState != SubmenuAnimState::NOT_ANIMATED;
}

bool Submenu::hasMessage()
{
    return messageText.size() > 0;
}

int Submenu::progressTowards(int from, int target)
{
    double nextY = (target - from) / 5.0;
    if (nextY < 0) { nextY = std::floor(nextY); }
    else { nextY = std::ceil(nextY); }
    return static_cast<int>(nextY);
}
