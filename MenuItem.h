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

private:
    std::string caption;
    std::function<void()> onClickAction;

};

