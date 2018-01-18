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

    States::getInstance()->initStates();

    gameArea = std::unique_ptr<GameArea>(new GameArea());

    while (States::getInstance()->getUIState() != UIState::QUIT) {
        Uint32 timePassed = display->getTicks();

        display->handleEvents();
        display->renderBackground();
        renderButtons();
        renderGameArea();

        delegateAccordingToGameState();
        handlePlayerClicks();

        if (!source.isEmpty() && !destination.isEmpty()) {
            gameArea->moveCard(source, destination);
        }

        display->renderPresent();

        Uint32 timestep = 16;
        while (timePassed + timestep > display->getTicks()) {
            display->delay();
        }
    }
    display->clean();
}

void Game::delegateAccordingToGameState() {
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    TurnState currentTurnState = States::getInstance()->getTurnState();

    if (currentPhase == GamePhase::CARD_PLACEMENT)
    {
        if (currentTurnState == TurnState::INIT)
        {
            populateCardArea();
            gameArea->initCardPositions();
            States::getInstance()->progressTurnState();
        }
        else
        {
            handleInitInProgress();
        }
    }
    else if (currentPhase == GamePhase::PLAYER_MOVE)
    {
        if (currentTurnState == TurnState::INIT)
        {
            handlePlayerMoveStart();
            States::getInstance()->progressTurnState();
        }
        else
        {
            handlePlayerMoveInProgress();
        }

    }
    else if (currentPhase == GamePhase::WAITING_FOR_PLAYER)
    {
        if (currentTurnState == TurnState::INIT)
        {
            handleWaitPhaseStart();
            States::getInstance()->progressTurnState();
        }
        else
        {
            handleWaitForNextPlayer();
        }
    }
    else if (currentPhase == GamePhase::VICTORY || 
        currentPhase == GamePhase::TIED)
    {
        handleVictory();
    }
}

void Game::populateCardArea() {
    //for (int i = 0; i <= static_cast<int>(CardType::MARSHALL) ; ++i) {
    for (int i = 0; i <= static_cast<int>(CardType::SCOUT); ++i) {
        auto currentTypeToSpawn = static_cast<CardType>(i);
        int amountToSpawn;
        Color colorToSpawnWith = States::getInstance()->getPlayerColor();

        switch (currentTypeToSpawn) {
        case CardType::FLAG: {
            amountToSpawn = CardFlag::getNR_TO_SPAWN();
            spawnNrOfTypesOfCards(CardType::FLAG, amountToSpawn, colorToSpawnWith);
            break;
        }
        case CardType::BOMB: {
            amountToSpawn = CardBomb::getNR_TO_SPAWN();
            amountToSpawn = 2;
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
            amountToSpawn = 1;
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
}

Game::Game() {
    //gameState = GameState::BLUE_INIT_START;
    //gameArea->initGameArea();
    //gameArea->initCardArea();
    //gameArea->initDiscardPile();
    initButtons();
}

void Game::renderGameArea() {
    int boardSize = gameArea->getSize(ClickedArea::GAME_AREA);
    for (int i = 0; i < boardSize; ++i) {
        int fieldX = gameArea->getXofFieldWithIdx(i, ClickedArea::GAME_AREA);
        int fieldY = gameArea->getYofFieldWithIdx(i, ClickedArea::GAME_AREA);
        bool highlighted = gameArea->isFieldHighlighted(i);
        if (gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA) == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        }
        else {
            int cardX = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextXPos(fieldX);
            int cardY = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextYPos(fieldY);
            int cardW = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getNextFlipAnimFrameWidth();
            if (gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getIsFaceDown()) {
                Color color = gameArea->getContentOfIdx(i, ClickedArea::GAME_AREA)->getColor();
                display->renderField(fieldX, fieldY, highlighted, color, cardX, cardY, cardW);
            }
            else {
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
        if (gameArea->getSideContentOfIdx(i) == nullptr) {
            display->renderField(fieldX, fieldY, highlighted);
        }
        else {
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
        switch (typeToSpawn) {
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
    if (!display->isEventQueueEmpty()) {
        ProcessedEvent event = display->getEventFromQueue();
        GamePhase currentPhase = States::getInstance()->getGamePhase();

        if (event.exitBtn) { States::getInstance()->setUIState(UIState::QUIT); }
        if (event.restartBtn) { restartGame(); }

        if (currentPhase == GamePhase::CARD_PLACEMENT) //Do I need to check if INIT?
        {
            input->evaluateInitPhaseClickEvent(event, gameArea, source, destination);
        }
        else if (currentPhase == GamePhase::PLAYER_MOVE) //Do I need to check if INIT?
        {
            if (event.getClickedArea() == ClickedArea::GAME_AREA) {
                input->evaluateBattlePhaseClickEvent(event, gameArea, possibleMoves, source, destination, attacker, defender);
            }
        }
        //TODO Make it so clicking anywhere progresses turn
        else if (currentPhase == GamePhase::WAITING_FOR_PLAYER && event.getClickedArea() == ClickedArea::GAME_AREA)
        {
            gameArea->clearHighlights();
            States::getInstance()->progressTurn();
        }
    }
}


void Game::restartGame() {
    gameArea->resetGameArea();
    States::getInstance()->restartStates();
    gameArea->clearHighlights();
    source.empty();
}

void Game::renderDiscardPile() {
    int fieldX, fieldY, discardPileSize;
    CardType typeToRender;
    Color cardColor;
    discardPileSize = gameArea->getSize(ClickedArea::DISCARD_PILE);
    for (int i = 0; i < discardPileSize; ++i) {
        fieldX = gameArea->getXofFieldWithIdx(i, ClickedArea::DISCARD_PILE);
        fieldY = gameArea->getYofFieldWithIdx(i, ClickedArea::DISCARD_PILE);
        if (gameArea->getContentOfIdx(i, ClickedArea::DISCARD_PILE) != nullptr) {
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
    if (!possibleMoves.empty()) {
        for (int i = 0; i < possibleMoves.size(); ++i) {
            x = gameArea->getXofFieldWithIdx(possibleMoves[i], ClickedArea::GAME_AREA);
            y = gameArea->getYofFieldWithIdx(possibleMoves[i], ClickedArea::GAME_AREA);
            display->renderAvailableMove(x, y);
        }
    }
}

void Game::checkIfTied() {
    if (!gameArea->playerHasValidMoves(Color::RED) &&
        !gameArea->playerHasValidMoves(Color::BLUE)) {
        States::getInstance()->setGamePhase(GamePhase::TIED);
    }
}

void Game::handlePlayerMoveInProgress()
{
    checkIfTied();
    Color currentPlayerColor = States::getInstance()->getPlayerColor();
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    if (!source.isEmpty()) {
        unsigned char moveDist;
        moveDist = gameArea->getContentOfIdx(source.fieldIndex, ClickedArea::GAME_AREA)->getMoveDistance();
        //TODO Gathers nearby valid indeces every single frame! Correct it!
        possibleMoves = gameArea->gatherNearbyValidFieldIndeces(moveDist, source.fieldIndex, currentPlayerColor);
    }

    //Check if player can move, if not, skip him
    if (currentPhase == GamePhase::PLAYER_MOVE)
    {
        if (!gameArea->playerHasValidMoves(currentPlayerColor)) { States::getInstance()->progressTurn(); }
        gameArea->resolveBattle(attacker, defender); 

    }
    renderGameArea();
    renderDiscardPile();
    if (!possibleMoves.empty()) renderAvailableMoves();
}

void Game::handleWaitForNextPlayer() {
    checkIfTied();
    renderDiscardPile();
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    Color playerColor = States::getInstance()->getPlayerColor();
    if (currentPhase == GamePhase::WAITING_FOR_PLAYER)
    {
        if (playerColor == Color::BLUE)
        {
            display->renderWaitMsg(Color::BLUE);
        }
        else
        {
            display->renderWaitMsg(Color::RED);
        }
    }
    renderGameArea();
}

void Game::handleInitInProgress() {
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    Color playerColor = States::getInstance()->getPlayerColor();
    if (currentPhase == GamePhase::CARD_PLACEMENT)
    {
        display->renderMapOverlay(playerColor);
        renderCardArea();
        if (gameArea->isCardAreaEmpty())
        {
            gameArea->changeFacingOfCards(playerColor, true);
            States::getInstance()->progressTurn();
            States::getInstance()->setTurnState(TurnState::INIT);
            //When progressing from red init, figure out where to set cards to face up/down
        }
    }
}

void Game::handleVictory() {
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    Color playerColor = States::getInstance()->getPlayerColor();
    Color opponentColor = States::getInstance()->getOpponentColor();
    if (currentPhase == GamePhase::VICTORY)
    {
        display->renderVictory(opponentColor);
    }
    else if (currentPhase == GamePhase::TIED)
    {
        display->renderVictory();
    }
}

void Game::handleWaitPhaseStart() {
    GamePhase currentPhase = States::getInstance()->getGamePhase();
    Color opponentColor = States::getInstance()->getOpponentColor();
    if (currentPhase == GamePhase::WAITING_FOR_PLAYER)
    {
        gameArea->changeFacingOfCards(opponentColor, true);
        gameArea->revealCombatants(attacker, defender);
    }
    possibleMoves.clear();
    States::getInstance()->setTurnState(TurnState::IN_PROGRESS);
}

void Game::handlePlayerMoveStart() {
    Color playerColor = States::getInstance()->getPlayerColor();
    gameArea->changeFacingOfCards(playerColor, false);
}
