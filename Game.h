#pragma once

#include <vector>
#include "Direction.h"
#include "Field.h"
#include "GameState.h"
#include "Display.h"
#include "Button.h"
#include "InputHandler.h"
#include "GameArea.h"
#include "States.h"
#include "MainMenu.h"
#include "CardFactory.h"
#include "ProcessedEvent.hpp"
#include <memory>

class Game 
{

public:
    Game();
    ~Game() = default;
    void start();

private:

    static const size_t FPS = 60;

    //Game init
    void initButtons(); 

    //Main Game Loop
    void delegateAccordingToGameState(); 
    void populateCardArea();    
    //void spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color);
    void checkIfTied(); //Functions used in it are moved to the GameArea object.

    //Game state progressing functions, they also contain some other actions as well...
    void handleInitInProgress();
    void handlePlayerMoveStart();
    void handlePlayerMoveInProgress();
    void handleWaitPhaseStart(); 
    void handleWaitForNextPlayer(); 
    void handleVictory(); 

    //Rendering
    void renderInOrder();
    void renderButtons();
    void renderMapOverlay();
    void renderGameArea(bool isAnimated);
    void renderCardArea(bool isAnimated);
    void renderDiscardPile(bool isAnimated);
    void renderAvailableMoves();

    //Input
    void handlePlayerClicks();
    void restartGame();

    std::vector<int> possibleMoves;
    std::unique_ptr<InputHandler> input;
    Button restart;
    Button exit;
    ProcessedEvent attacker;
    ProcessedEvent defender;
    ProcessedEvent source;
    ProcessedEvent destination;
    std::unique_ptr<Display> display;
    std::unique_ptr<GameArea> gameArea;
    std::unique_ptr<MainMenu> mainMenu;

};