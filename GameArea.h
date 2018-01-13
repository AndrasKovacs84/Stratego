#pragma once
#include "Field.h"
#include "Direction.h"
#include <iostream>
#include <memory>
#include <vector>

class GameArea
{
public:
    GameArea();
    ~GameArea();
    
    void initGameArea(); 
    void initDiscardPile();
    void initCardArea();
    void placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace);
    void initCardPositions();
    void moveCard(ProcessedEvent& source, ProcessedEvent& destination);
    bool isCardAreaEmpty();
    bool playerHasValidMoves(Color color);
    void gatherViableMovesInDir(int index, unsigned char moveDist, Color color, std::vector<int> &result, Direction dir);
    void clearHighlights();
    void changeFacingOfCards(Color color, bool faceDown);
    void revealCombatants();
    std::vector<int> gatherNearbyValidFieldIndeces(unsigned char moveDist, int index, Color color);
    void resolveBattle();
    int getNextEmptyDiscardPileIndex();

private:

    std::vector<std::unique_ptr<Field>> gameArea;
    std::vector<std::unique_ptr<Field>> cardArea;
    std::vector<std::unique_ptr<Field>> discardPile;
};

