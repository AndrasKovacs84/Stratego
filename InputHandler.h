#pragma once
#include <vector>
#include "Field.h"
#include "GameArea.h"
#include "States.h"

class InputHandler {
public:
    void evaluateInitPhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination);
    void evaluateBattlePhaseClickEvent(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, std::vector<int> &possibleMoves, ProcessedEvent &source,
                                      ProcessedEvent &destination, ProcessedEvent &attacker, ProcessedEvent &defender);
    char keyInputHandler(ProcessedEvent event);
    bool validKeyInput(ProcessedEvent event);
private:
    void initPhaseGameAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination);
    void initPhaseSideAreaClick(ProcessedEvent event, std::unique_ptr<GameArea>& gameArea, ProcessedEvent &source, ProcessedEvent &destination);
};