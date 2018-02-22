#pragma once
#include <iostream>

#include "UIState.h"
#include "SubmenuName.h"
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
    SubmenuName getCurrentSubmenu();
    SubmenuName getPreviousSubmenu();
    GameType getGameType();
    GamePhase getGamePhase();
    Color getPlayerColor();
    Color getOpponentColor();
    TurnState getTurnState();
    void progressTurn();
    void progressTurnState();

    //Setters
    void setUIState(UIState setting);
    void setCurrentSubmenu(SubmenuName submenu);
    void setGameType(GameType gameTypeToSet);
    void setGamePhase(GamePhase gamePhaseToSet);
    void setTurnState(TurnState newState);

    void clearSubmenus();

private:
    States() {};
    States(States const&) {};
    States& operator=(States const&) {};
    static States instance;

    void flipPlayerColor();
    void gameModeHotseatProgress();

    UIState uiState;
    SubmenuName currentSubmenu;
    SubmenuName previousSubmenu;
    GameType gameType;
    GamePhase gamePhase;
    Color playerColor;
    TurnState turnState;
};

