#pragma once
#include <iostream>
#include "UIState.h"
#include "GameType.h"
#include "GamePhase.h"
#include "Turn.h"
#include "TurnState.h"
#include "Color.h"

class States
{
public:
    static States* getInstance();
    void initStates();
    void restartStates();

    //Getters
    UIState getUIState();
    GameType getGameType();
    GamePhase getGamePhase();
    Color getPlayerColor();
    Color getOpponentColor();
    TurnState getTurnState();
    void progressTurn();
    void progressTurnState();

    //Setters
    void setUIState(UIState setting);
    void setGameType(GameType gameTypeToSet);
    void setGamePhase(GamePhase gamePhaseToSet);
    void setTurnState(TurnState newState);

private:
    States() {};
    States(States const&) {};
    States& operator=(States const&) {};
    static States instance;

    void flipPlayerColor();
    void gameModeHotseatProgress();

    UIState uiState;
    GameType gameType;
    GamePhase gamePhase;
    Color playerColor;
    TurnState turnState;
};

