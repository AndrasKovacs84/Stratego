#pragma once
#include "SDL_events.h"
#include <string>

class InteractableArea
{
public:
    InteractableArea(int minX, int maxX, int minY, int maxY, int menuItem, SDL_EventType interactTo)
    {
        _minX = minX;
        _maxX = maxX;
        _minY = minY;
        _maxY = maxY;
        _menuItem = menuItem;
        _interactTo = interactTo;
    };

    bool isEventValid(int x, int y, SDL_EventType eventToCheck)
    {
        std::string dummy;
        if (x >= _minX && 
            x <= _maxX &&
            y >= _minY &&
            y <= _maxY &&
            eventToCheck == _interactTo)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    int getMenuItemNr() { return _menuItem; };

private:
    int _minX;
    int _maxX;
    int _minY;
    int _maxY;
    int _menuItem = -1;
    SDL_EventType _interactTo;
};