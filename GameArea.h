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

    //New getters
    int getSize(ClickedArea areaToCheck);
    //int getSideAreaSize();
    //int getDiscardPileSize();
    int getXofFieldWithIdx(const int& index, ClickedArea area);
    int getYofFieldWithIdx(const int& index, ClickedArea area);
    //int getXofSideFieldWithIdx(const int& index);
    //int getYofSideFieldWithIdx(const int& index, ClickedArea area);
    bool isFieldHighlighted(const int& index);
    bool isSideFieldHighlighted(const int& index);
    const std::unique_ptr<Card>& getContentOfIdx(const int& index, ClickedArea area);
    const std::unique_ptr<Card>& getSideContentOfIdx(const int& index);

private:

    std::vector<std::unique_ptr<Field>> gameArea;
    std::vector<std::unique_ptr<Field>> cardArea;
    std::vector<std::unique_ptr<Field>> discardPile;
};

