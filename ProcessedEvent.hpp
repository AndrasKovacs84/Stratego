#pragma once

#include "Color.h"
#include "ClickedArea.h"
#include "InputType.h"

struct ProcessedEvent {
    InputType inputType = InputType::NONE;
    bool restartBtn = false;
    bool exitBtn = false;
    int fieldIndex = -1;
    int sideAreaIndex = -1;
    int menuItem = -1;

    bool isEmpty() {
        return (inputType == InputType::NONE && !restartBtn && !exitBtn && fieldIndex == -1 && sideAreaIndex == -1 && menuItem == -1);
    }

    bool isInBlueTerritory() {
        return fieldIndex <= 39;
    }

    bool isInRedTerritory() {
        return fieldIndex >= 60;
    }

    bool isInTerritory(Color color) {
        if(fieldIndex == -1) return false;

        if(color == Color::RED) {
            return fieldIndex <= 39;
        } else {
            return fieldIndex >= 60;
        }
    }

    ClickedArea getClickedArea() {
        if(fieldIndex != -1) return ClickedArea::GAME_AREA;
        if(sideAreaIndex != -1) return ClickedArea::SIDE_AREA;
        if(fieldIndex == -1 && sideAreaIndex == -1) return ClickedArea::UI;
    }

    void empty() {
        inputType = InputType::NONE;
        restartBtn = false;
        exitBtn = false;
        fieldIndex = -1;
        sideAreaIndex = -1;
        menuItem = -1;
    }
};