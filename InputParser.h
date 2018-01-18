#pragma once
#include <vector>
#include "Field.h"
#include "GameArea.h"

class InputParser {
public:
    void evaluateInitPhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination, Color currentPlayerColor);
    void evaluateBattlePhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, std::vector<int> &possibleMoves, ProcessedEvent &source,
                                      ProcessedEvent &destination, ProcessedEvent &attacker, ProcessedEvent &defender, Color currentPlayerColor, GameState &gameState);
private:
    void initPhaseGameAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination);
    void initPhaseSideAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination);
};