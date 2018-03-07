#pragma once

#include "SubmenuName.h"
#include "Submenu.h"
#include "InteractableArea.hpp"
#include "SDL_events.h"
#include "ProcessedEvent.hpp"
#include "UIState.h"
#include "States.h"
#include "InputType.h"

#include <map>
#include <vector>

class InputParser
{
public:
    static InputParser* getInstance();

    void registerMenuItem(SubmenuName submenu, size_t menuItemNr);
    ProcessedEvent processEvent(int mouseX, int mouseY, InputType eventToProcess);
    ProcessedEvent processKeyEvent(SDL_Event event);

private:
    InputParser() {};
    InputParser(InputParser const&) {};
    InputParser& operator=(InputParser const&) {};
    static InputParser instance;



    ProcessedEvent processMenuEvent(int mouseX, int mouseY, InputType eventToProcess);
    ProcessedEvent processInGameEvent(int x, int y, InputType input);
    int processGameAreaClick(int x, int y);
    int processSideAreaClick(int x, int y);

    std::map<SubmenuName, std::vector<InteractableArea>> interactableAreaRegistrar;
};

