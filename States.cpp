#include "States.h"

States States::instance;

States * States::getInstance()
{
    return &instance;
}

void States::initStates()
{
    uiState = UIState::MENU;
    currentSubmenu = SubmenuName::MAIN_MENU;
    gameType = GameType::HOTSEAT;
    gamePhase = GamePhase::CARD_PLACEMENT;
    playerColor = Color::BLUE;
    turnState = TurnState::INIT;
}

void States::restartStates()
{
    gamePhase = GamePhase::CARD_PLACEMENT;
    playerColor = Color::BLUE;
    turnState = TurnState::INIT;
}

UIState States::getUIState()
{
    return uiState;
}

SubmenuName States::getCurrentSubmenu()
{
    return currentSubmenu;
}

GameType States::getGameType()
{
    return gameType;
}

GamePhase States::getGamePhase()
{
    return gamePhase;
}

Color States::getPlayerColor()
{
    return playerColor;
}

Color States::getOpponentColor()
{
    if (playerColor == Color::BLUE)
    {
        return Color::RED;
    }
    else
    {
        return Color::BLUE;
    }
}

TurnState States::getTurnState()
{
    return turnState;
}

void States::progressTurn()
{
    if (gameType == GameType::HOTSEAT)
    {
        gameModeHotseatProgress();
    }

}

void States::progressTurnState()
{
    turnState = TurnState::IN_PROGRESS;
}

void States::setUIState(UIState setting)
{
    uiState = setting;
}

void States::setCurrentSubmenu(SubmenuName submenu)
{
    currentSubmenu = submenu;
}

void States::setGameType(GameType gameTypeToSet)
{
    gameType = gameTypeToSet;
}

void States::setGamePhase(GamePhase gamePhaseToSet)
{
    gamePhase = gamePhaseToSet;
}

void States::setTurnState(TurnState newState)
{
    turnState = newState;
}

void States::flipPlayerColor()
{
    if (playerColor == Color::BLUE)
    {
        playerColor = Color::RED;
    }
    else
    {
        playerColor = Color::BLUE;
    }
}

void States::gameModeHotseatProgress()
{
    if (gamePhase == GamePhase::CARD_PLACEMENT)
    {
        if (playerColor == Color::RED)
        {
            gamePhase = GamePhase::PLAYER_MOVE;
            turnState = TurnState::INIT;
        }
        flipPlayerColor();
        turnState = TurnState::INIT;
    }
    else if (gamePhase == GamePhase::PLAYER_MOVE)
    {
        flipPlayerColor();
        gamePhase = GamePhase::WAITING_FOR_PLAYER;
        turnState = TurnState::INIT;
    }
    else if (gamePhase == GamePhase::WAITING_FOR_PLAYER)
    {
        gamePhase = GamePhase::PLAYER_MOVE;
        turnState = TurnState::INIT;
    }
}
