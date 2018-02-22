#pragma once
#include <string>
#include <functional>

class MenuItem
{
public:
    MenuItem();
    MenuItem(std::string caption, std::function<void()> onClickAction);
    ~MenuItem();

    void action();
    const std::string getCaption() const;

    bool isPressed();
    void setPressed(bool pressed);

private:
    bool pressed = false;
    std::string caption;
    std::function<void()> onClickAction;

};

