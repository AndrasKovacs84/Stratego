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
    InteractableArea newAreaBtnDown(minX, maxX, minY, maxY, menuItemNr, InputType::MOUSE_CLICK_DOWN);
    interactableAreaRegistrar[submenu].push_back(newAreaBtnDown);

    InteractableArea newAreaBtnUp(minX, maxX, minY, maxY, menuItemNr, InputType::MOUSE_CLICK_RELEASE);
    interactableAreaRegistrar[submenu].push_back(newAreaBtnUp);
}

ProcessedEvent InputParser::processEvent(int mouseX, int mouseY, InputType eventToProcess)
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
    else
    {
        processedEvent.inputType = eventToProcess;
    }


    return processedEvent;
}

ProcessedEvent InputParser::processKeyEvent(SDL_Event event)
{
    ProcessedEvent processedEvent;
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_ESCAPE);
        break;

    case SDLK_PERIOD:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_PERIOD);
        break;
    case SDLK_KP_PERIOD:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_PERIOD);
        break;

    case SDLK_0:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_0);
        break;
    case SDLK_KP_0:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_0);
        break;

    case SDLK_1:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_1);
        break;
    case SDLK_KP_1:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_1);
        break;

    case SDLK_2:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_2);
        break;
    case SDLK_KP_2:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_2);
        break;

    case SDLK_3:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_3);
        break;
    case SDLK_KP_3:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_3);
        break;

    case SDLK_4:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_4);
        break;
    case SDLK_KP_4:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_4);
        break;

    case SDLK_5:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_5);
        break;
    case SDLK_KP_5:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_5);
        break;

    case SDLK_6:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_6);
        break;
    case SDLK_KP_6:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_6);
        break;

    case SDLK_7:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_7);
        break;
    case SDLK_KP_7:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_7);
        break;

    case SDLK_8:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_8);
        break;
    case SDLK_KP_8:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_8);
        break;

    case SDLK_9:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_9);
        break;
    case SDLK_KP_9:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_9);
        break;
    case SDLK_BACKSPACE:
        processedEvent = InputParser::getInstance()->processEvent(-1, -1, InputType::KEY_BACKSPACE);
        break;

    default:
        break;
    }
    return processedEvent;
}

ProcessedEvent InputParser::processMenuEvent(int mouseX, int mouseY, InputType eventToProcess)
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

ProcessedEvent InputParser::processInGameEvent(int x, int y, InputType input) {
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
