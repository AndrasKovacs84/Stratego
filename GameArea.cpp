#include "GameArea.h"



GameArea::GameArea()
{
}


GameArea::~GameArea()
{
}

void GameArea::initGameArea()
{
    size_t x, y;
    for (int i = 0; i < 10; ++i) {
        y = 10 + 50 * static_cast<size_t >(i);
        for (int j = 0; j < 10; ++j) {
            x = 10 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
			newField->unhighlight();
            gameArea.emplace_back(std::move(newField));
        }
    }
    //Creating western lake
    gameArea[42]->setIsTraversable(false);
    gameArea[43]->setIsTraversable(false);
    gameArea[52]->setIsTraversable(false);
    gameArea[53]->setIsTraversable(false);

    //Creating eastern lake
    gameArea[46]->setIsTraversable(false);
    gameArea[47]->setIsTraversable(false);
    gameArea[56]->setIsTraversable(false);
    gameArea[57]->setIsTraversable(false);
}

void GameArea::initDiscardPile()
{
    size_t x, y;
    for (int i = 0; i < 16; ++i) {
        y = 110 + 25 * static_cast<size_t >(i);
        for (int j = 0; j < 5; ++j) {
            x = 520 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
			newField->unhighlight();
            discardPile.emplace_back(std::move(newField));
        }
    }
}

void GameArea::initCardArea()
{
    size_t x, y;
    for (int i = 0; i < 8; ++i) {
        y = 110 + 50 * static_cast<size_t >(i);
        for (int j = 0; j < 5; ++j) {
            x = 520 + 50 * static_cast<size_t>(j);
            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
			newField->unhighlight();
            cardArea.emplace_back(std::move(newField));
        }
    }
}

void GameArea::placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace)
{
    for (int j = 0; j < cardArea.size() ; ++j) {
        if(cardArea[j]->getContent() == nullptr) {
            cardArea[j]->placeCard(std::move(cardToPlace));
        }
    }
}

//After spawning cards into the fields within the card area, this initializes each card's
//x, y coord to match that of the field it is in.
void GameArea::initCardPositions()
{
    int x, y;
    for (int i = 0; i < cardArea.size() ; ++i) {
        if(cardArea[i]->getContent() != nullptr) {
            x = cardArea[i]->getX();
            y = cardArea[i]->getY();
            cardArea[i]->getContent()->setCurrentX(x);
            cardArea[i]->getContent()->setCurrentY(y);
        }
    }
}

void GameArea::moveCard(ProcessedEvent & source, ProcessedEvent & destination)
{

    std::unique_ptr<Card> tempCard;
    if(source.getClickedArea() == ClickedArea::GAME_AREA) {
        tempCard = gameArea[source.fieldIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        gameArea[source.fieldIndex]->unhighlight();

    } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
        tempCard = cardArea[source.sideAreaIndex]->removeCard();
        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
        cardArea[source.sideAreaIndex]->unhighlight();
    }

    //if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
    //    gameState = GameState::WAIT_FOR_RED_START;
    //    gameArea[source.fieldIndex]->highlight();
    //    gameArea[destination.fieldIndex]->highlight();
    //}

    //if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
    //    gameState = GameState::WAIT_FOR_BLUE_START;
    //    gameArea[source.fieldIndex]->highlight();
    //    gameArea[destination.fieldIndex]->highlight();
    //}

    source.empty();
    destination.empty();

}

bool GameArea::isCardAreaEmpty()
{
    for (int i = 0; i < cardArea.size(); ++i) {
        if(cardArea[i]->getContent() != nullptr) {
            return false;
        }
    }
    return true;
}

bool GameArea::playerHasValidMoves(Color color)
{
    unsigned char moveDist;
    std::vector<int> validMoveIndeces;
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getContent() != nullptr) {
            if(gameArea[i]->getContent()->getColor() == color) {
                moveDist = gameArea[i]->getContent()->getMoveDistance();
                validMoveIndeces = gatherNearbyValidFieldIndeces(moveDist, i, color);
                if(validMoveIndeces.size() > 0){
                    return true;
                }
            }
        }
    }
    return false;
}

void GameArea::gatherViableMovesInDir(int index, unsigned char moveDist, Color color, std::vector<int>& result, Direction dir)
{
    int gameAreaDiameter = 10;
    int rightEdge = ((index / gameAreaDiameter)*gameAreaDiameter) + gameAreaDiameter -1;
    int leftEdge = ((index / gameAreaDiameter)*gameAreaDiameter);

    int nextIndex;

    for (int i = 1; i <= moveDist; ++i) {
        if(dir == Direction::EAST) {
            nextIndex = index + i;
            if(nextIndex > rightEdge) break;
        } else if(dir == Direction::SOUTH) {
            nextIndex = index + (i * gameAreaDiameter);
            if(nextIndex > 99) break;
        } else if(dir == Direction::WEST) {
            nextIndex = index - i;
            if(nextIndex < leftEdge) break;
        } else if(dir == Direction::NORTH) {
            nextIndex = index - (i * gameAreaDiameter);
            if(nextIndex < 0) break;
        }

        if (gameArea[nextIndex]->getContent() == nullptr) {
            if( gameArea[nextIndex]->getIsTraversable()) {
                result.emplace_back(nextIndex);
            } else {
                break;
            }
        } else if (gameArea[nextIndex]->getContent()->getColor() != color) {
            result.emplace_back(nextIndex);
            break;
        } else {
            break;
        }
    }
}

void GameArea::clearHighlights()
{
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getIsHighlighted()) {
            gameArea[i]->unhighlight();
        }
    }
}

void GameArea::changeFacingOfCards(Color color, bool faceDown)
{
    int delay = 0;
    for (int i = 0; i < gameArea.size(); ++i) {
        if(gameArea[i]->getContent() != nullptr) {
            delay += 3;
            if(gameArea[i]->getContent()->getColor() == color) {
                if(faceDown) {
                    gameArea[i]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_DOWN, delay, 25);
                } else if(!faceDown){
                    gameArea[i]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, delay, 25);
                }
            }
        }
    }
}

void GameArea::revealCombatants()
{
    if(attacker.fieldIndex != -1 && defender.fieldIndex != -1) {
        gameArea[attacker.fieldIndex]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, 1, 25);
        gameArea[defender.fieldIndex]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, 1, 25);
    }
}

std::vector<int> GameArea::gatherNearbyValidFieldIndeces(unsigned char moveDist, int index, Color color)
{
    std::vector<int> result;
    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::NORTH);
    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::EAST);
    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::SOUTH);
    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::WEST);
    return result;
}

void GameArea::resolveBattle()
{
    if(attacker.isEmpty() || defender.isEmpty()) return;
    std::unique_ptr<Card> tempCard;
    if(gameArea[attacker.fieldIndex]->getContent()->getType() ==
            gameArea[defender.fieldIndex]->getContent()->getType()) {

        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

        tempCard = gameArea[defender.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

    } else if (gameArea[attacker.fieldIndex]->getContent()->canDefeat(gameArea[defender.fieldIndex]->getContent()->getType())) {
        if(gameArea[defender.fieldIndex]->getContent()->getType() == CardType::FLAG) {
            Color winnerColor = gameArea[attacker.fieldIndex]->getContent()->getColor();
            triggerVictory(winnerColor);
        }

        tempCard = gameArea[defender.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));

        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        gameArea[defender.fieldIndex]->placeCard(std::move(tempCard));
    } else {
        tempCard = gameArea[attacker.fieldIndex]->removeCard();
        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
    }
    attacker.empty();
    defender.empty();
}

int GameArea::getNextEmptyDiscardPileIndex()
{
    for (int i = 0; i < discardPile.size(); ++i) {
        if(discardPile[i]->getContent() == nullptr) {
            return i;
        }
    }
}

int GameArea::getSize(ClickedArea areaToCheck)
{
    switch (areaToCheck)
    {
    case ClickedArea::GAME_AREA:
        return gameArea.size();
    case ClickedArea::SIDE_AREA:
        return cardArea.size();
    case ClickedArea::DISCARD_PILE:
        return discardPile.size();
    case ClickedArea::UI:
        break;
    default:
        return 0;
        break;
    }
}

int GameArea::getSideAreaSize()
{
    return cardArea.size();
}

int GameArea::getDiscardPileSize()
{
    return discardPile.size();
}

int GameArea::getXofFieldWithIdx(const int & index, ClickedArea area)
{
    switch (area)
    {
    case ClickedArea::GAME_AREA:
        return gameArea[index]->getX();
        break;
    case ClickedArea::SIDE_AREA:
        return sideArea[index]->getX();
        break;
    case ClickedArea::DISCARD_PILE:
        return discardPile[index]->getX();
        break;
    default:
        return 0;
    }
    return gameArea[index]->getX();
}

int GameArea::getYofFieldWithIdx(const int & index, ClickedArea area)
{
    switch (area)
    {
    case ClickedArea::GAME_AREA:
        return gameArea[index]->getY();
    case ClickedArea::SIDE_AREA:
        return sideArea[index]->getY();
    case ClickedArea::DISCARD_PILE:
        break;
    default:
        return 0;
    }
}

int GameArea::getXofSideFieldWithIdx(const int & index)
{
    return cardArea[index]->getX();
}

int GameArea::getYofSideFieldWithIdx(const int & index, ClickedArea area)
{
    switch (area)
    {
    case ClickedArea::GAME_AREA:
        return gameArea[index]->getY();
    case ClickedArea::SIDE_AREA:
        return sideArea[index]->getY();
    case ClickedArea::DISCARD_PILE:
        break;
    default:
        return 0;
    }
}

bool GameArea::isFieldHighlighted(const int & index)
{
    return gameArea[index]->getIsHighlighted(index);
}

bool GameArea::isSideFieldHighlighted(const int & index)
{
    return cardArea[index]->getIsHighlighted();
}

const std::unique_ptr<Card>& GameArea::getContentOfIdx(const int & index, ClickedArea area)
{
    switch (area)
    {
    case ClickedArea::GAME_AREA:
        return gameArea[index]->getContent();
    case ClickedArea::SIDE_AREA:
        return sideArea[index]->getContent();
    case ClickedArea::DISCARD_PILE:
        return discardPile[index]->getContent();
    default:
        return 0;
    }
}

const std::unique_ptr<Card>& GameArea::getSideContentOfIdx(const int & index)
{
    return cardArea[index]->getContent();
}
