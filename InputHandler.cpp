#include "InputHandler.h"
#include <algorithm>

void InputHandler::evaluateInitPhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea> &gameArea, ProcessedEvent &source,
                                              ProcessedEvent &destination) {

    Color currentPlayerColor = States::getInstance()->getPlayerColor();
    if(event.getClickedArea() == ClickedArea::GAME_AREA) {
        if(event.isInTerritory(currentPlayerColor)) {
            initPhaseGameAreaClick(event, gameArea, source, destination);
        }
    } else if(event.getClickedArea() == ClickedArea::SIDE_AREA) {
        initPhaseSideAreaClick(event, gameArea, source, destination);
    }
}

void InputHandler::initPhaseGameAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(!source.isEmpty()) {
        if(gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA) == nullptr) {
            destination = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex != source.fieldIndex) {
            gameArea->getFieldOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->unhighlight();
            gameArea->getFieldOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->highlight();
            source = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex == source.fieldIndex) {
            gameArea->getFieldOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->unhighlight();
            source.empty();
        } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
            gameArea->getFieldOfIdx(source.sideAreaIndex, ClickedArea::SIDE_AREA)->unhighlight();
            gameArea->getFieldOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->highlight();
            source = event;
        }
    } else {
        if(gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA) != nullptr) {
            source = event;
            gameArea->getFieldOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->highlight();
        }
    }
}

void InputHandler::initPhaseSideAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(gameArea->getContentOfIdx(event.sideAreaIndex, ClickedArea::SIDE_AREA) != nullptr) {
        if(source.isEmpty()) {
            source = event;
            gameArea->getFieldOfIdx(source.sideAreaIndex, ClickedArea::SIDE_AREA)->highlight();
        } else {
            if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
               source.sideAreaIndex == event.sideAreaIndex) {
                gameArea->getFieldOfIdx(source.sideAreaIndex, ClickedArea::SIDE_AREA)->unhighlight();
                source.empty();
            } else if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
                      source.sideAreaIndex != event.sideAreaIndex){
                gameArea->getFieldOfIdx(source.sideAreaIndex, ClickedArea::SIDE_AREA)->unhighlight();
                gameArea->getFieldOfIdx(event.sideAreaIndex, ClickedArea::SIDE_AREA)->highlight();
                source = event;
            } else if(source.getClickedArea() == ClickedArea::GAME_AREA) {
                gameArea->getFieldOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->unhighlight();
                gameArea->getFieldOfIdx(event.sideAreaIndex, ClickedArea::SIDE_AREA)->highlight();
                source = event;
            }
        }
    }
}

void InputHandler::evaluateBattlePhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea,
                                               std::vector<int> &possibleMoves, ProcessedEvent &source,
                                               ProcessedEvent &destination, ProcessedEvent &attacker,
                                               ProcessedEvent &defender) 
{
    Color currentPlayerColor = States::getInstance()->getPlayerColor();
    if(gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA) == nullptr) {
        if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
            destination = event;
        }
    } else {
        if(source.isEmpty() && gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->getColor() == currentPlayerColor) {
            gameArea->getFieldOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->getColor() == currentPlayerColor) {
            gameArea->getFieldOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->unhighlight();
            gameArea->getFieldOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea->getContentOfIdx(event.fieldIndex, ClickedArea::GAME_AREA)->getColor() != currentPlayerColor) {
            if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
                defender = event;
                attacker = source;
                States::getInstance()->progressTurn();
                //if(currentPlayerColor == Color::BLUE) {
                //    gameState = GameState::WAIT_FOR_RED_START;
                //} else if(currentPlayerColor == Color::RED) {
                //    gameState = GameState::WAIT_FOR_BLUE_START;
                //}
                source.empty();
                destination.empty();
            }
        }
    }
}

char InputHandler::keyInputHandler(ProcessedEvent event)
{
    switch (event.inputType)
    {
    case InputType::KEY_0: return '0';
    case InputType::KEY_1: return '1';
    case InputType::KEY_2: return '2';
    case InputType::KEY_3: return '3';
    case InputType::KEY_4: return '4';
    case InputType::KEY_5: return '5';
    case InputType::KEY_6: return '6';
    case InputType::KEY_7: return '7';
    case InputType::KEY_8: return '8';
    case InputType::KEY_9: return '9';
    case InputType::KEY_PERIOD: return '.';
    default: break; 
    }
    return 0;
}

bool InputHandler::validKeyInput(ProcessedEvent event)
{
    return (event.inputType == InputType::KEY_0 ||
        event.inputType == InputType::KEY_1 ||
        event.inputType == InputType::KEY_2 ||
        event.inputType == InputType::KEY_3 ||
        event.inputType == InputType::KEY_4 ||
        event.inputType == InputType::KEY_5 ||
        event.inputType == InputType::KEY_6 ||
        event.inputType == InputType::KEY_7 ||
        event.inputType == InputType::KEY_8 ||
        event.inputType == InputType::KEY_9 ||
        event.inputType == InputType::KEY_PERIOD ||
        event.inputType == InputType::KEY_BACKSPACE);
}

