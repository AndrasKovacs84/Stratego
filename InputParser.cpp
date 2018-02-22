#include "InputParser.h"


InputParser InputParser::instance;

InputParser* InputParser::getInstance()
{
    return &instance;
}

void InputParser::registerMenuItem(SubmenuName submenu, size_t menuItemNr)
{
    int minX, maxX, minY, maxY;
    minX = Submenu::SCREEN_MIDDLE_X + Submenu::LEFT_OFFSET_TO_BTNS;
    maxX = minX + 270; // 270 == btn width registered in assets.cpp
    minY = Submenu::TOP_OFFSET_TO_BTNS + (menuItemNr * (Submenu::OFFSET_BETWEEN_BTNS + 50));
    maxY = minY + 50; // 50 == btn height registered in assets.cpp
    SDL_EventType eventName = SDL_MOUSEBUTTONDOWN;
    InteractableArea newAreaBtnDown(minX, maxX, minY, maxY, menuItemNr, eventName);
    interactableAreaRegistrar[submenu].push_back(newAreaBtnDown);

    eventName = SDL_MOUSEBUTTONUP;
    InteractableArea newAreaBtnUp(minX, maxX, minY, maxY, menuItemNr, eventName);
    interactableAreaRegistrar[submenu].push_back(newAreaBtnUp);
}

ProcessedEvent InputParser::processEvent(int mouseX, int mouseY, SDL_EventType eventToProcess)
{
    ProcessedEvent processedEvent;
    UIState currentState = States::getInstance()->getUIState();

    if (currentState == UIState::MENU)
    {
        processedEvent = processMenuEvent(mouseX, mouseY, eventToProcess);
    }
    else if (currentState == UIState::IN_GAME)
    {
        processedEvent = processInGameEvent(mouseX, mouseY, eventToProcess);
    }


    return processedEvent;
}

ProcessedEvent InputParser::processMenuEvent(int mouseX, int mouseY, SDL_EventType eventToProcess)
{
    ProcessedEvent processedEvent;
    SubmenuName currentSubmenu = States::getInstance()->getCurrentSubmenu();

    std::vector<InteractableArea>& currentInteractableAreas = interactableAreaRegistrar[currentSubmenu];

    size_t length = currentInteractableAreas.size();
    for (size_t i = 0; i < length; i++)
    {
        if (currentInteractableAreas[i].isEventValid(mouseX, mouseY, eventToProcess))
        {
            processedEvent.menuItem = currentInteractableAreas[i].getMenuItemNr();
        }
    }
    processedEvent.inputType = eventToProcess;
    return processedEvent;
}

ProcessedEvent InputParser::processInGameEvent(int x, int y, SDL_EventType input) {
    ProcessedEvent processedEvent;
    processedEvent.inputType = input;
    if (x < 10 || x>770 || y < 10 || y > 510) { return processedEvent; }

    if (x > 550 && x < 630 && y>65 && y < 95) {
        processedEvent.exitBtn = true;
    }
    if (x > 660 && x < 740 && y>65 && y < 95) {
        processedEvent.restartBtn = true;
    }
    if (x > 10 && x < 510 && y>10 && y < 510) {
        processedEvent.fieldIndex = processGameAreaClick(x, y);
    }
    if (x > 520 && x < 770 & y>110 && y < 510) {
        processedEvent.sideAreaIndex = processSideAreaClick(x, y);
    }
    return processedEvent;
}

int InputParser::processGameAreaClick(int x, int y) {
    int fieldIndex;
    fieldIndex = (((y - 10) / 50) * 10) + ((x - 10) / 50);
    return fieldIndex;
}

int InputParser::processSideAreaClick(int x, int y) {
    int sideIndex;
    sideIndex = (((y - 110) / 50) * 5) + ((x - 520) / 50);
    return sideIndex;
}
