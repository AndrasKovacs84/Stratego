#pragma once
#include <vector>
#include "Field.h"

class InputParser {
public:
    void evaluateInitPhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination, Color currentPlayerColor);
    void evaluatBattlePhaseClickEvent(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea, std::vector<int> &possibleMoves, ProcessedEvent &source,
                                      ProcessedEvent &destination, ProcessedEvent &attacker, ProcessedEvent &defender, Color currentPlayerColor, GameState &gameState);
private:
    void initPhaseGameAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination);

    void initPhaseSideAreaClick(ProcessedEvent event, std::vector<std::unique_ptr<Field>> &gameArea,
                                std::vector<std::unique_ptr<Field>> &cardArea, ProcessedEvent &source, ProcessedEvent &destination);
};