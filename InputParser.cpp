#include "InputParser.h"
#include <algorithm>

void InputParser::evaluateInitPhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                              std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                              ProcessedEvent &destination, Color currentPlayerColor) {

    if(event.getClickedArea() == ClickedArea::GAME_AREA) {
        if(event.isInTerritory(currentPlayerColor)) {
            initPhaseGameAreaClick(event, gameArea, cardArea, source, destination);
        }
    } else if(event.getClickedArea() == ClickedArea::SIDE_AREA) {
        initPhaseSideAreaClick(event, gameArea, cardArea, source, destination);
    }
}

void InputParser::initPhaseGameAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                         std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(!source.isEmpty()) {
        if(gameArea[event.fieldIndex]->getContent() == nullptr) {
            destination = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex != source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(source.getClickedArea() == ClickedArea::GAME_AREA &&
                  event.fieldIndex == source.fieldIndex) {
            gameArea[source.fieldIndex]->unhighlight();
            source.empty();
        } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
            cardArea[source.sideAreaIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        }
    } else {
        if(gameArea[event.fieldIndex]->getContent() != nullptr) {
            source = event;
            gameArea[source.fieldIndex]->highlight();
        }
    }
}

void InputParser::initPhaseSideAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                         std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source,
                                         ProcessedEvent &destination) {
    if(cardArea[event.sideAreaIndex]->getContent() != nullptr) {
        if(source.isEmpty()) {
            source = event;
            cardArea[source.sideAreaIndex]->highlight();
        } else {
            if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
               source.sideAreaIndex == event.sideAreaIndex) {
                cardArea[source.sideAreaIndex]->unhighlight();
                source.empty();
            } else if(source.getClickedArea() == ClickedArea::SIDE_AREA &&
                      source.sideAreaIndex != event.sideAreaIndex){
                cardArea[source.sideAreaIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            } else if(source.getClickedArea() == ClickedArea::GAME_AREA) {
                gameArea[source.fieldIndex]->unhighlight();
                cardArea[event.sideAreaIndex]->highlight();
                source = event;
            }
        }
    }
}

void InputParser::evaluatBattlePhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                               std::vector<int> &possibleMoves, ProcessedEvent &source,
                                               ProcessedEvent &destination, ProcessedEvent &attacker,
                                               ProcessedEvent &defender, Color currentPlayerColor,
                                               GameState &gameState) {

    if(gameArea[event.fieldIndex]->getContent() == nullptr) {
        if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
            destination = event;
        }
    } else {
        if(source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() == currentPlayerColor) {
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() == currentPlayerColor) {
            gameArea[source.fieldIndex]->unhighlight();
            gameArea[event.fieldIndex]->highlight();
            source = event;
        } else if(!source.isEmpty() && gameArea[event.fieldIndex]->getContent()->getColor() != currentPlayerColor) {
            if(std::find(possibleMoves.begin(), possibleMoves.end(), event.fieldIndex) != possibleMoves.end()) {
                defender = event;
                attacker = source;
                if(currentPlayerColor == Color::BLUE) {
                    gameState = GameState::WAIT_FOR_RED_START;
                } else if(currentPlayerColor == Color::RED) {
                    gameState = GameState::WAIT_FOR_BLUE_START;
                }
                source.empty();
                destination.empty();
            }
        }
    }
}

