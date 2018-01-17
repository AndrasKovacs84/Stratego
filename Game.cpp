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

    gameArea->initGameArea();
    gameArea->initCardArea();
    gameArea->initDiscardPile();

    while(gameState != GameState::EXIT) {
        Uint32 timePassed = display->getTicks();

        display->handleEvents();
        display->renderBackground();
        renderButtons();
        renderGameArea();

        delegateAccordingToGameState();

        handlePlayerClicks();
        if(!source.isEmpty() && !destination.isEmpty()){
            gameArea->moveCard(source, destination);
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
        gameArea->initCardPositions();
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

Game::Game() {
    gameState = GameState::BLUE_INIT_START;
    //gameArea->initGameArea();
    //gameArea->initCardArea();
    //gameArea->initDiscardPile();
    initButtons();
}

void Game::renderGameArea() {
    int boardSize = gameArea->getSize(ClickedArea::GAME_AREA);
    for (int i = 0; i < boardSize; ++i) {
        int fieldX = gameArea->getXofFieldWithIdx(i, ClickedArea::GAME_AREA);
        int fieldY = gameArea->getYofFieldWithIdx(i, ClickedArea::SIDE_AREA);
        bool highlighted = gameArea->isFieldHighlighted(i);
        if(gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA) == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            int cardX = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextXPos(fieldX);
            int cardY = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextYPos(fieldY);
            int cardW = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextFlipAnimFrameWidth();
            if(gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getIsFaceDown()){
                Color color = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getColor();
                display->renderField(fieldX, fieldY, highlighted, color, cardX, cardY, cardW);
            } else {
                Color color = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getColor();
                CardType type = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getType();
                display->renderField(fieldX, fieldY, highlighted, color, type, cardX, cardY, cardW);
            }
        }
    }
}

void Game::renderCardArea() {
    int cardAreaSize = gameArea->getSize(ClickedArea::SIDE_AREA);
    for (int i = 0; i < cardAreaSize; ++i) {
        int fieldX = gameArea->getXofFieldWithIdx(i, ClickedArea::SIDE_AREA);
        int fieldY = gameArea->getYofFieldWithIdx(i, ClickedArea::SIDE_AREA);
        bool highlighted = gameArea->isSideFieldHighlighted(i);
        if(gameArea->getSideContentOfIdx(i) == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        } else {
            Color color = gameArea->getSideContentOfIdx(i)->getColor();
            CardType type = gameArea->getSideContentOfIdx(i)->getType();
            int cardX = gameArea->getSideContentOfIdx(i)->getNextXPos(fieldX);
            int cardY = gameArea->getSideContentOfIdx(i)->getNextYPos(fieldY);
            int cardW = gameArea->getSideContentOfIdx(i)->getNextFlipAnimFrameWidth();
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
        gameArea->placeToNextEmptyFieldInSideArea(std::move(tempCard));
    }
}

void Game::handlePlayerClicks() {
    if(!display->isEventQueueEmpty()) {
        ProcessedEvent event = display->getEventFromQueue();
        if(event.exitBtn) {gameState = GameState::EXIT;}
        if(event.restartBtn) {restartGame();}

        if(gameState == GameState::RED_INIT_IN_PROGRESS ||
            gameState == GameState::BLUE_INIT_IN_PROGRESS){
            input->evaluateInitPhaseClickEvent(event, gameArea, source, destination, getCurrentPlayerColor());
        } else if(gameState == GameState::BLUE_MOVE_IN_PROGRESS ||
                gameState == GameState::RED_MOVE_IN_PROGRESS) {
            if(event.getClickedArea() == ClickedArea::GAME_AREA) {
                input->evaluateBattlePhaseClickEvent(event, gameArea, possibleMoves, source, destination, attacker, defender, getCurrentPlayerColor(), gameState);
            }
        } else if(gameState == GameState::WAITING_FOR_BLUE && event.getClickedArea() == ClickedArea::GAME_AREA) {
            gameArea->clearHighlights();
            gameState = GameState::BLUE_MOVE_START;
        } else if(gameState == GameState::WAITING_FOR_RED && event.getClickedArea() == ClickedArea::GAME_AREA) {
            gameArea->clearHighlights();
            gameState = GameState::RED_MOVE_START;
        }

    }
}


void Game::restartGame() {
    gameArea->resetGameArea();
    gameState = GameState::BLUE_INIT_START;
    gameArea->clearHighlights();
    source.empty();
}

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

void Game::triggerVictory(Color winner) {
    if(winner == Color::RED) {
        gameState = GameState::RED_WINS;
    } else if(winner == Color::BLUE) {
        gameState = GameState::BLUE_WINS;
    }
}

void Game::renderDiscardPile() {
    int fieldX, fieldY, discardPileSize;
    CardType typeToRender;
    Color cardColor;
    discardPileSize = gameArea->getSize(ClickedArea::DISCARD_PILE);
    for (int i = 0; i < discardPileSize; ++i) {
        //fieldX = discardPile[i]->getX();
        fieldX = gameArea->getXofFieldWithIdx(i, ClickedArea::DISCARD_PILE);
        //fieldY = discardPile[i]->getY();
        fieldY = gameArea->getYofFieldWithIdx(i, ClickedArea::DISCARD_PILE);
        //if(discardPile[i]->getContent() != nullptr) {
        if(gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE) != nullptr) {
            typeToRender = gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE)->getType();
            cardColor = gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE)->getColor();
            int cardX = gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE)->getNextXPos(fieldX);
            int cardY = gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE)->getNextYPos(fieldY);
            int cardW = gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE)->getNextFlipAnimFrameWidth();
            display->renderField(fieldX, fieldY, false, cardColor, typeToRender, cardX, cardY, cardW);
        }
    }
}

void Game::renderAvailableMoves() {
    int x, y;
    if(!possibleMoves.empty()) {
        for (int i = 0; i < possibleMoves.size(); ++i) {
            x = gameArea->getXofFieldWithIdx(possibleMoves[i], ClickedArea::GAME_AREA);
            y = gameArea->getYofFieldWithIdx(possibleMoves[i], ClickedArea::GAME_AREA);
            display->renderAvailableMove(x, y);
        }
    }
}

void Game::checkIfTied() {
    if(!gameArea->playerHasValidMoves(Color::RED) &&
            !gameArea->playerHasValidMoves(Color::BLUE)) {
        gameState = GameState::TIED;
    }
}

void Game::handlePlayerMoveInProgress() 
{
    checkIfTied();
    Color currentPlayerColor = getCurrentPlayerColor();
    if(!source.isEmpty()) {
        unsigned char moveDist;
        moveDist = gameArea->getContentOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->getMoveDistance();
        possibleMoves = gameArea->gatherNearbyValidFieldIndeces(moveDist, source.fieldIndex, currentPlayerColor);
    }

    if(gameState == GameState::BLUE_MOVE_IN_PROGRESS) {
        if(!gameArea->playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAIT_FOR_RED_START;
        gameArea->resolveBattle(attacker, defender); //TODO needs attacker and defender as parameters?

    } else if(gameState == GameState::RED_MOVE_IN_PROGRESS) {
        if(!gameArea->playerHasValidMoves(getCurrentPlayerColor())) gameState = GameState::WAIT_FOR_BLUE_START;
        gameArea->resolveBattle(attacker, defender);
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
              gameArea->isCardAreaEmpty()) {
        gameArea->changeFacingOfCards(Color::BLUE, true);
        gameState = GameState::RED_INIT_START;

    } else if(gameState == GameState::RED_INIT_IN_PROGRESS &&
              gameArea->isCardAreaEmpty()) {
        gameArea->changeFacingOfCards(Color::RED, true);
        gameArea->changeFacingOfCards(Color::BLUE, true);
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

void Game::handleWaitPhaseStart() {
    if(gameState == GameState::WAIT_FOR_BLUE_START) {
        gameArea->changeFacingOfCards(Color::RED, true);
        gameArea->revealCombatants(attacker, defender);

    } else if(gameState == GameState::WAIT_FOR_RED_START) {
        gameArea->changeFacingOfCards(Color::BLUE, true);
        gameArea->revealCombatants(attacker, defender);
    }
    possibleMoves.clear();
    if(gameState == GameState::WAIT_FOR_BLUE_START) gameState = GameState::WAITING_FOR_BLUE;
    if(gameState == GameState::WAIT_FOR_RED_START) gameState = GameState::WAITING_FOR_RED;
}

void Game::handlePlayerMoveStart() {
    if(gameState == GameState::BLUE_MOVE_START) {
        gameArea->changeFacingOfCards(Color::BLUE, false);
        gameState = GameState::BLUE_MOVE_IN_PROGRESS;

    } else if(gameState == GameState::RED_MOVE_START) {
        gameArea->changeFacingOfCards(Color::RED, false);
        gameState = GameState::RED_MOVE_IN_PROGRESS;
    }
}
