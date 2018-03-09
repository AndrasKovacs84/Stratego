#pragma once
#include "MenuItem.h"
#include <vector>
#include "SubmenuName.h"
#include "SubmenuAnimState.h"
#include <functional>

class Submenu
{
public:
    Submenu();
    ~Submenu();

    void addButton(MenuItem btn, size_t btnIdx);
    void btnAction(size_t btnIdx);
    int getNextX();
    int getBtnX();
    int getBtnY(size_t btnIdx);
    const std::string getCaption(size_t btnIdx) const;
    const size_t getMenuSize() const;
    bool isBtnPressed(size_t btnIdx);
    void setBtnPress(size_t btnIdx, bool pressed);
    void setMessage(std::vector<std::string>& message);
    const std::vector<std::string> getMsg();
    void clearPresses();
    void setAnimState(SubmenuAnimState nextState);
    void setX(int x);

    std::string getInputField() const;
    void enterCharacter(char input);
    void removeLastCharacter();

    bool isAnimated();
    bool hasMessage();



    static const int SCREEN_MIDDLE_X = 140; //Where the left edge of the menu needs to be so that the menu itself is completely centered on screen.
    static const int SCREEN_RIGHT_EDGE = 780;
    static const int SCREEN_LEFT_EDGE = -500;

    static const int LEFT_OFFSET_TO_BTNS = 115;
    static const int TOP_OFFSET_TO_BTNS = 47;
    static const int OFFSET_BETWEEN_BTNS = 45;

private:

    std::vector<std::string> messageText;
    std::string inputField;
    int progressTowards(int from, int target);

    SubmenuAnimState currentAnimState;
    int _x;
    int _y;

    static const size_t MENU_SIZE = 5; //Max number of buttons the menu can accomodate (limited by graphic design)
    MenuItem options[MENU_SIZE];

};

