#pragma once
#include <string>
#include <functional>

class MenuItem
{
public:
    MenuItem();
    MenuItem(std::string caption, std::function<void()> onClickAction);
    void action();
    ~MenuItem();
private:
    size_t relativeX;
    size_t relativeY;
    std::string caption;
    std::function<void()> onClickAction;

};

