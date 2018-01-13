#include <SDL_events.h>
#include "Game.h"
#include "CardBomb.hpp"
#include "CardFlag.hpp"
#include "CardSpy.hpp"
#include "CardScout.hpp"
#include "CardMiner.hpp"
#include "CardSargeant.hpp"
#include "CardLieutentant.hpp"
#include "CardCaptain.hpp"
#include "CardMajor.hpp"
#include "CardColonel.hpp"
#include "CardGeneral.hpp"
#include "CardMarshall.hpp"
#include <algorithm>

void Game::start() {

    display = std::unique_ptr<Display>(new Display());
    display->init("Stratego", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 780, 520, false);

    while(gameState != GameState::EXIT) {
        Uint32 timePassed = display->getTicks();

        display->handleEvents();
        display->renderBackground();
        renderButtons();
        renderGameArea();

        delegateAccordingToGameState();

        handlePlayerClicks();
        if(!source.isEmpty() && !destination.isEmpty()){
            moveCard();
        }

        display->renderPresent();

        Uint32 timestep = 16;
        while(timePassed + timestep > display->getTicks()){
            display->delay();
        }
    }
    display->clean();
}

void Game::delegateAccordingToGameState() {
    if(gameState == GameState::BLUE_INIT_START ||
       gameState == GameState::RED_INIT_START) {
        populateCardArea();
        initCardPositions();
    } else if(gameState == GameState::BLUE_INIT_IN_PROGRESS ||
              gameState == GameState::RED_INIT_IN_PROGRESS) {
        handleInitInProgress();
    } else if(gameState == GameState::BLUE_MOVE_START ||
              gameState == GameState::RED_MOVE_START) {
        handlePlayerMoveStart();
    } else if(gameState == GameState::RED_MOVE_IN_PROGRESS ||
              gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        handlePlayerMoveInProgress();
    } else if(gameState == GameState::WAIT_FOR_BLUE_START ||
              gameState == GameState::WAIT_FOR_RED_START) {
        handleWaitPhaseStart();
    } else if(gameState == GameState::WAITING_FOR_BLUE ||
              gameState == GameState::WAITING_FOR_RED) {
        handleWaitForNextPlayer();
    } else if(gameState == GameState::RED_WINS ||
              gameState == GameState::BLUE_WINS ||
              gameState == GameState::TIED) {
        handleVictory();
    }

}

void Game::populateCardArea() {
    for (int i = 0; i <= static_cast<int>(CardType::MARSHALL) ; ++i) {
    //for (int i = 0; i <= static_cast<int>(CardType::SCOUT) ; ++i) {
        auto currentTypeToSpawn = static_cast<CardType >(i);
        int amountToSpawn;
        Color colorToSpawnWith;
        if(gameState == GameState::BLUE_INIT_START) {
            colorToSpawnWith = Color::BLUE;
        } else if (gameState == GameState::RED_INIT_START){
            colorToSpawnWith = Color::RED;
        }

        switch (currentTypeToSpawn) {
            case CardType::FLAG: {
                amountToSpawn = CardFlag::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::FLAG, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::BOMB: {
                amountToSpawn = CardBomb::getNR_TO_SPAWN();
                //amountToSpawn = 2;
                spawnNrOfTypesOfCards(CardType::BOMB, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SPY: {
                amountToSpawn = CardSpy::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::SPY, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SCOUT: {
                amountToSpawn = CardScout::getNR_TO_SPAWN();
                //amountToSpawn = 1;
                spawnNrOfTypesOfCards(CardType::SCOUT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MINER: {
                amountToSpawn = CardMiner::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MINER, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::SARGEANT: {
                amountToSpawn = CardSargeant::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::SARGEANT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::LIEUTENANT: {
                amountToSpawn = CardLieutenant::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::LIEUTENANT, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::CAPTAIN: {
                amountToSpawn = CardCaptain::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::CAPTAIN, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MAJOR: {
                amountToSpawn = CardMajor::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MAJOR, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::COLONEL: {
                amountToSpawn = CardColonel::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::COLONEL, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::GENERAL: {
                amountToSpawn = CardGeneral::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::GENERAL, amountToSpawn, colorToSpawnWith);
                break;
            }
            case CardType::MARSHALL: {
                amountToSpawn = CardMarshall::getNR_TO_SPAWN();
                spawnNrOfTypesOfCards(CardType::MARSHALL, amountToSpawn, colorToSpawnWith);
                break;
            }
        }

    }

    if(gameState == GameState::BLUE_INIT_START) {
        gameState = GameState::BLUE_INIT_IN_PROGRESS;
    } else {
        gameState = GameState::RED_INIT_IN_PROGRESS;
    }
}

//void Game::moveCard() {
//
//    std::unique_ptr<Card> tempCard;
//    if(source.getClickedArea() == ClickedArea::GAME_AREA) {
//        tempCard = gameArea[source.fieldIndex]->removeCard();
//        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
//        gameArea[source.fieldIndex]->unhighlight();
//
//    } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
//        tempCard = cardArea[source.sideAreaIndex]->removeCard();
//        gameArea[destination.fieldIndex]->placeCard(std::move(tempCard));
//        cardArea[source.sideAreaIndex]->unhighlight();
//    }
//
//    if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
//        gameState = GameState::WAIT_FOR_RED_START;
//        gameArea[source.fieldIndex]->highlight();
//        gameArea[destination.fieldIndex]->highlight();
//    }
//
//    if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
//        gameState = GameState::WAIT_FOR_BLUE_START;
//        gameArea[source.fieldIndex]->highlight();
//        gameArea[destination.fieldIndex]->highlight();
//    }
//
//    source.empty();
//    destination.empty();
//
//}

Game::Game() {
    gameState = GameState::BLUE_INIT_START;
    initGameArea();
    initCardArea();
    initButtons();
    initDiscardPile();
}

//void Game::initGameArea() {
//    size_t x, y;
//    for (int i = 0; i < 10; ++i) {
//        y = 10 + 50 * static_cast<size_t >(i);
//        for (int j = 0; j < 10; ++j) {
//            x = 10 + 50 * static_cast<size_t>(j);
//            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
//			newField->unhighlight();
//            gameArea.emplace_back(std::move(newField));
//        }
//    }
//    //Creating western lake
//    gameArea[42]->setIsTraversable(false);
//    gameArea[43]->setIsTraversable(false);
//    gameArea[52]->setIsTraversable(false);
//    gameArea[53]->setIsTraversable(false);
//
//    //Creating eastern lake
//    gameArea[46]->setIsTraversable(false);
//    gameArea[47]->setIsTraversable(false);
//    gameArea[56]->setIsTraversable(false);
//    gameArea[57]->setIsTraversable(false);
//}


//void Game::initCardArea() {
//    size_t x, y;
//    for (int i = 0; i < 8; ++i) {
//        y = 110 + 50 * static_cast<size_t >(i);
//        for (int j = 0; j < 5; ++j) {
//            x = 520 + 50 * static_cast<size_t>(j);
//            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
//			newField->unhighlight();
//            cardArea.emplace_back(std::move(newField));
//        }
//    }
//}

void Game::renderGameArea() {
    for (int i = 0; i < gameArea.size(); ++i) {
        int fieldX = gameArea[i]->getX();
        int fieldY = gameArea[i]->getY();
        bool highlighted = gameArea[i]->getIsHighlighted();
        if(gameArea[i]->getContent() == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            int cardX = gameArea[i]->getContent()->getNextXPos(fieldX);
            int cardY = gameArea[i]->getContent()->getNextYPos(fieldY);
            int cardW = gameArea[i]->getContent()->getNextFlipAnimFrameWidth();
            if(gameArea[i]->getContent()->getIsFaceDown()){
                Color color = gameArea[i]->getContent()->getColor();
                display->renderField(fieldX, fieldY, highlighted, color, cardX, cardY, cardW);
            } else {
                Color color = gameArea[i]->getContent()->getColor();
                CardType type = gameArea[i]->getContent()->getType();
                display->renderField(fieldX, fieldY, highlighted, color, type, cardX, cardY, cardW);
            }
        }
    }
}

void Game::renderCardArea() {
    for (int i = 0; i < cardArea.size(); ++i) {
        int fieldX = cardArea[i]->getX();
        int fieldY = cardArea[i]->getY();
        bool highlighted = cardArea[i]->getIsHighlighted();
        if(cardArea[i]->getContent() == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            Color color = cardArea[i]->getContent()->getColor();
            CardType type = cardArea[i]->getContent()->getType();
            int cardX = cardArea[i]->getContent()->getNextXPos(fieldX);
            int cardY = cardArea[i]->getContent()->getNextYPos(fieldY);
            int cardW = cardArea[i]->getContent()->getNextFlipAnimFrameWidth();
            display->renderField(fieldX, fieldY, highlighted, color, type, cardX, cardY, cardW);
        }
    }
}

void Game::renderButtons() {
    display->renderButton(restart.getPosition(), restart.getCurrentTexture());
    display->renderButton(exit.getPosition(), exit.getCurrentTexture());
}

void Game::initButtons() {

    SDL_Rect btnPos;
    btnPos.h = 30;
    btnPos.w = 80;
    btnPos.x = 550;
    btnPos.y = 65;
    restart.setPosition(btnPos);
    restart.setNormalTexture(UIElement::RESTART_BTN);
    restart.setPressedDownTexture(UIElement::RESTART_BTN_PRESSED);
    restart.setPressedDown(false);

    btnPos.x = 660;
    exit.setPosition(btnPos);
    exit.setNormalTexture(UIElement::EXIT_BTN);
    exit.setPressedDownTexture(UIElement::EXIT_BTN_PRESSED);
    exit.setPressedDown(false);
}

void Game::spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color) {
    std::unique_ptr<Card> tempCard;
    for (int i = 0; i < amountToSpawn; ++i) {
        switch (typeToSpawn){
            case CardType::FLAG: {
                tempCard = std::unique_ptr<CardFlag>(new CardFlag(color));
                break;
            }
            case CardType::BOMB: {
                tempCard = std::unique_ptr<CardBomb>(new CardBomb(color));
                break;
            }
            case CardType::SPY: {
                tempCard = std::unique_ptr<CardSpy>(new CardSpy(color));
                break;
            }
            case CardType::SCOUT: {
                tempCard = std::unique_ptr<CardScout>(new CardScout(color));
                break;
            }
            case CardType::MINER: {
                tempCard = std::unique_ptr<CardMiner>(new CardMiner(color));
                break;
            }
            case CardType::SARGEANT: {
                tempCard = std::unique_ptr<CardSargeant>(new CardSargeant(color));
                break;
            }
            case CardType::LIEUTENANT: {
                tempCard = std::unique_ptr<CardLieutenant>(new CardLieutenant(color));
                break;
            }
            case CardType::CAPTAIN: {
                tempCard = std::unique_ptr<CardCaptain>(new CardCaptain(color));
                break;
            }
            case CardType::MAJOR: {
                tempCard = std::unique_ptr<CardMajor>(new CardMajor(color));
                break;
            }
            case CardType::COLONEL: {
                tempCard = std::unique_ptr<CardColonel>(new CardColonel(color));
                break;
            }
            case CardType::GENERAL: {
                tempCard = std::unique_ptr<CardGeneral>(new CardGeneral(color));
                break;
            }
            case CardType::MARSHALL: {
                tempCard = std::unique_ptr<CardMarshall>(new CardMarshall(color));
                break;
            }
        }
        placeToNextEmptyFieldInSideArea(std::move(tempCard));
    }
}

//void Game::placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace) {
//    for (int j = 0; j < cardArea.size() ; ++j) {
//        if(cardArea[j]->getContent() == nullptr) {
//            cardArea[j]->placeCard(std::move(cardToPlace));
//        }
//    }
//}

void Game::handlePlayerClicks() {
    if(!display->isEventQueueEmpty()) {
        ProcessedEvent event = display->getEventFromQueue();
        if(event.exitBtn) {gameState = GameState::EXIT;}
        if(event.restartBtn) {restartGame();}

        if(gameState == GameState::RED_INIT_IN_PROGRESS ||
            gameState == GameState::BLUE_INIT_IN_PROGRESS){
            input->evaluateInitPhaseClickEvent(event, gameArea, cardArea, source, destination, getCurrentPlayerColor());
        } else if(gameState == GameState::BLUE_MOVE_IN_PROGRESS ||
                gameState == GameState::RED_MOVE_IN_PROGRESS) {
            if(event.getClickedArea() == ClickedArea::GAME_AREA) {
                input->evaluatBattlePhaseClickEvent(event, gameArea, possibleMoves, source, destination, attacker, defender, getCurrentPlayerColor(), gameState);
            }
        } else if(gameState == GameState::WAITING_FOR_BLUE && event.getClickedArea() == ClickedArea::GAME_AREA) {
            clearHighlights();
            gameState = GameState::BLUE_MOVE_START;
        } else if(gameState == GameState::WAITING_FOR_RED && event.getClickedArea() == ClickedArea::GAME_AREA) {
            clearHighlights();
            gameState = GameState::RED_MOVE_START;
        }

    }
}


void Game::restartGame() {
    for (int i = 0; i < gameArea.size(); ++i) {
        gameArea[i]->removeCard();
    }
    for (int j = 0; j < cardArea.size(); ++j) {
        cardArea[j]->removeCard();
    }
    gameState = GameState::BLUE_INIT_START;
    clearHighlights();
    if(source.getClickedArea() == ClickedArea::GAME_AREA) {
        gameArea[source.fieldIndex]->unhighlight();
    } else if(source.getClickedArea() == ClickedArea::SIDE_AREA) {
        cardArea[source.sideAreaIndex]->unhighlight();
    }
    source.empty();
}

//bool Game::isCardAreaEmpty() {
//    for (int i = 0; i < cardArea.size(); ++i) {
//        if(cardArea[i]->getContent() != nullptr) {
//            return false;
//        }
//    }
//    return true;
//}

//void Game::changeFacingOfCards(Color color, bool faceDown){
//    int delay = 0;
//    for (int i = 0; i < gameArea.size(); ++i) {
//        if(gameArea[i]->getContent() != nullptr) {
//            delay += 3;
//            if(gameArea[i]->getContent()->getColor() == color) {
//                if(faceDown) {
//                    gameArea[i]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_DOWN, delay, 25);
//                } else if(!faceDown){
//                    gameArea[i]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, delay, 25);
//                }
//            }
//        }
//    }
//}

Color Game::getCurrentPlayerColor() {
    if(gameState == GameState::BLUE_INIT_START ||
       gameState == GameState::BLUE_INIT_IN_PROGRESS ||
       gameState == GameState::BLUE_MOVE_START ||
       gameState == GameState::BLUE_MOVE_IN_PROGRESS ||
       gameState == GameState::WAITING_FOR_BLUE ) {
        return Color::BLUE;
    }
    return Color::RED;
}


//bool Game::playerHasValidMoves(Color currentPlayerColor) {
//    unsigned char moveDist;
//    std::vector<int> validMoveIndeces;
//    for (int i = 0; i < gameArea.size(); ++i) {
//        if(gameArea[i]->getContent() != nullptr) {
//            if(gameArea[i]->getContent()->getColor() == currentPlayerColor) {
//                moveDist = gameArea[i]->getContent()->getMoveDistance();
//                validMoveIndeces = gatherNearbyValidFieldIndeces(moveDist, i, currentPlayerColor);
//                if(validMoveIndeces.size() > 0){
//                    return true;
//                }
//            }
//        }
//    }
//    return false;
//}

//std::vector<int> Game::gatherNearbyValidFieldIndeces(unsigned char moveDist, int index, Color currentPlayerColor) {
//    std::vector<int> result;
//    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::NORTH);
//    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::EAST);
//    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::SOUTH);
//    gatherViableMovesInDir(index, moveDist, currentPlayerColor, result, Direction::WEST);
//    return result;
//}

//void Game::gatherViableMovesInDir(int index, unsigned char moveDist, Color currentPlayerColor, std::vector<int> &result, Direction dir) {
//
//    int gameAreaDiameter = 10;
//    int rightEdge = ((index / gameAreaDiameter)*gameAreaDiameter) + gameAreaDiameter -1;
//    int leftEdge = ((index / gameAreaDiameter)*gameAreaDiameter);
//
//    int nextIndex;
//
//
//    for (int i = 1; i <= moveDist; ++i) {
//        if(dir == Direction::EAST) {
//            nextIndex = index + i;
//            if(nextIndex > rightEdge) break;
//        } else if(dir == Direction::SOUTH) {
//            nextIndex = index + (i * gameAreaDiameter);
//            if(nextIndex > 99) break;
//        } else if(dir == Direction::WEST) {
//            nextIndex = index - i;
//            if(nextIndex < leftEdge) break;
//        } else if(dir == Direction::NORTH) {
//            nextIndex = index - (i * gameAreaDiameter);
//            if(nextIndex < 0) break;
//        }
//
//        if (gameArea[nextIndex]->getContent() == nullptr) {
//            if( gameArea[nextIndex]->getIsTraversable()) {
//                result.emplace_back(nextIndex);
//            } else {
//                break;
//            }
//        } else if (gameArea[nextIndex]->getContent()->getColor() != currentPlayerColor) {
//            result.emplace_back(nextIndex);
//            break;
//        } else {
//            break;
//        }
//    }
//}

//void Game::clearHighlights() {
//    for (int i = 0; i < gameArea.size(); ++i) {
//        if(gameArea[i]->getIsHighlighted()) {
//            gameArea[i]->unhighlight();
//        }
//    }
//}

//void Game::revealCombatants() {
//    if(attacker.fieldIndex != -1 && defender.fieldIndex != -1) {
//        gameArea[attacker.fieldIndex]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, 1, 25);
//        gameArea[defender.fieldIndex]->getContent()->setCurrentFlipAnim(FlipAnimState::TURNING_FACE_UP, 1, 25);
//    }
//}

//void Game::resolveBattle() {
//    if(attacker.isEmpty() || defender.isEmpty()) return;
//    std::unique_ptr<Card> tempCard;
//    if(gameArea[attacker.fieldIndex]->getContent()->getType() ==
//            gameArea[defender.fieldIndex]->getContent()->getType()) {
//
//        tempCard = gameArea[attacker.fieldIndex]->removeCard();
//        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
//
//        tempCard = gameArea[defender.fieldIndex]->removeCard();
//        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
//
//    } else if (gameArea[attacker.fieldIndex]->getContent()->canDefeat(gameArea[defender.fieldIndex]->getContent()->getType())) {
//        if(gameArea[defender.fieldIndex]->getContent()->getType() == CardType::FLAG) {
//            Color winnerColor = gameArea[attacker.fieldIndex]->getContent()->getColor();
//            triggerVictory(winnerColor);
//        }
//
//        tempCard = gameArea[defender.fieldIndex]->removeCard();
//        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
//
//        tempCard = gameArea[attacker.fieldIndex]->removeCard();
//        gameArea[defender.fieldIndex]->placeCard(std::move(tempCard));
//    } else {
//        tempCard = gameArea[attacker.fieldIndex]->removeCard();
//        discardPile[getNextEmptyDiscardPileIndex()]->placeCard(std::move(tempCard));
//    }
//    attacker.empty();
//    defender.empty();
//}

void Game::triggerVictory(Color winner) {
    if(winner == Color::RED) {
        gameState = GameState::RED_WINS;
    } else if(winner == Color::BLUE) {
        gameState = GameState::BLUE_WINS;
    }
}

//void Game::initDiscardPile() {
//    size_t x, y;
//    for (int i = 0; i < 16; ++i) {
//        y = 110 + 25 * static_cast<size_t >(i);
//        for (int j = 0; j < 5; ++j) {
//            x = 520 + 50 * static_cast<size_t>(j);
//            std::unique_ptr<Field> newField = std::unique_ptr<Field>(new Field(x, y, true));
//			newField->unhighlight();
//            discardPile.emplace_back(std::move(newField));
//        }
//    }
//}

void Game::renderDiscardPile() {
    int fieldX, fieldY;
    CardType typeToRender;
    Color cardColor;
    for (int i = 0; i < discardPile.size(); ++i) {
        fieldX = discardPile[i]->getX();
        fieldY = discardPile[i]->getY();
        if(discardPile[i]->getContent() != nullptr) {
            typeToRender = discardPile[i]->getContent()->getType();
            cardColor = discardPile[i]->getContent()->getColor();
            int cardX = discardPile[i]->getContent()->getNextXPos(fieldX);
            int cardY = discardPile[i]->getContent()->getNextYPos(fieldY);
            int cardW = discardPile[i]->getContent()->getNextFlipAnimFrameWidth();
            display->renderField(fieldX, fieldY, false, cardColor, typeToRender, cardX, cardY, cardW);
        }
    }
}

//int Game::getNextEmptyDiscardPileIndex() {
//    for (int i = 0; i < discardPile.size(); ++i) {
//        if(discardPile[i]->getContent() == nullptr) {
//            return i;
//        }
//    }
//}

void Game::renderAvailableMoves() {
    int x, y;
    if(!possibleMoves.empty()) {
        for (int i = 0; i < possibleMoves.size(); ++i) {
            x = gameArea[possibleMoves[i]]->getX();
            y = gameArea[possibleMoves[i]]->getY();
            display->renderAvailableMove(x, y);
        }
    }
}

void Game::checkIfTied() {
    if(!playerHasValidMoves(Color::RED) &&
            !playerHasValidMoves(Color::BLUE)) {
        gameState = GameState::TIED;
    }
}

void Game::handlePlayerMoveInProgress() {

    checkIfTied();
    Color currentPlayerColor = getCurrentPlayerColor();
    if(!source.isEmpty()) {
        unsigned char moveDist;
        moveDist = gameArea[source.fieldIndex]->getContent()->getMoveDistance();
        possibleMoves = gatherNearbyValidFieldIndeces(moveDist, source.fieldIndex, currentPlayerColor);
    }

    if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        if(!playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAIT_FOR_RED_START;
        resolveBattle();

    } else if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
        if(!playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAIT_FOR_BLUE_START;
        resolveBattle();
    }
    renderGameArea();
    renderDiscardPile();
    if(!possibleMoves.empty()) renderAvailableMoves();
}

void Game::handleWaitForNextPlayer() {
    checkIfTied();
    renderDiscardPile();
    if(gameState == GameState::WAITING_FOR_BLUE) {
        display->renderWaitMsg(Color::BLUE);

    } else if(gameState == GameState::WAITING_FOR_RED) {
        display->renderWaitMsg(Color::RED);
    }
    renderGameArea();
}

void Game::handleInitInProgress() {
    if(gameState == GameState::BLUE_INIT_IN_PROGRESS) {
        display->renderMapOverlay(Color::BLUE);
        renderCardArea();
    }

    if(gameState == GameState::RED_INIT_IN_PROGRESS) {
        display->renderMapOverlay(Color::RED);
        renderCardArea();
    }

    if(gameState == GameState::BLUE_INIT_IN_PROGRESS &&
              isCardAreaEmpty()) {
        changeFacingOfCards(Color::BLUE, true);
        gameState = GameState::RED_INIT_START;

    } else if(gameState == GameState::RED_INIT_IN_PROGRESS &&
              isCardAreaEmpty()) {
        changeFacingOfCards(Color::RED, true);
        changeFacingOfCards(Color::BLUE, true);
        gameState = GameState::WAIT_FOR_BLUE_START;
    }
}

void Game::handleVictory() {
    if(gameState == GameState::BLUE_WINS) {
        display->renderVictory(GameState::BLUE_WINS);
    } else if(gameState == GameState::RED_WINS) {
        display->renderVictory(GameState::RED_WINS);
    } else if(gameState == GameState::TIED) {
        display->renderVictory(GameState::TIED);
    }
}

//void Game::initCardPositions() {
//    int x, y;
//    for (int i = 0; i < cardArea.size() ; ++i) {
//        if(cardArea[i]->getContent() != nullptr) {
//            x = cardArea[i]->getX();
//            y = cardArea[i]->getY();
//            cardArea[i]->getContent()->setCurrentX(x);
//            cardArea[i]->getContent()->setCurrentY(y);
//        }
//    }
//}

void Game::handleWaitPhaseStart() {
    if(gameState == GameState::WAIT_FOR_BLUE_START) {
        changeFacingOfCards(Color::RED, true);
        revealCombatants();

    } else if(gameState == GameState::WAIT_FOR_RED_START) {
        changeFacingOfCards(Color::BLUE, true);
        revealCombatants();
    }
    possibleMoves.clear();
    if(gameState == GameState::WAIT_FOR_BLUE_START) gameState = GameState::WAITING_FOR_BLUE;
    if(gameState == GameState::WAIT_FOR_RED_START) gameState = GameState::WAITING_FOR_RED;
}

void Game::handlePlayerMoveStart() {
    if(gameState == GameState::BLUE_MOVE_START) {
        changeFacingOfCards(Color::BLUE, false);
        gameState = GameState::BLUE_MOVE_IN_PROGRESS;

    } else if(gameState == GameState::RED_MOVE_START) {
        changeFacingOfCards(Color::RED, false);
        gameState = GameState::RED_MOVE_IN_PROGRESS;
    }
}


