#pragma once

#include <vector>
#include "Direction.h"
#include "Field.h"
#include "Coordinate.h"
#include "GameState.h"
#include "Display.h"
#include "Button.h"
#include "InputParser.h"
#include <memory>

class Game 
{

public:
    Game();
    ~Game() = default;
    void start();

private:

    //Game init
    void initButtons(); //TODO some UI init with menu
    //void initGameArea(); //TODO UI init class
    //void initDiscardPile(); //TODO UI init class
    //void initCardArea();    //TODO UI init class

    //Main Game Loop
    void delegateAccordingToGameState();    //TODO will need one of these per game mode
    void populateCardArea();    //TODO GAME area class
    void spawnNrOfTypesOfCards(CardType typeToSpawn, int amountToSpawn, Color color);
    //void placeToNextEmptyFieldInSideArea(std::unique_ptr<Card> cardToPlace);
    //void initCardPositions();

    //void moveCard();
    //bool isCardAreaEmpty();
    void checkIfTied(); //Functions used in it are moved to the GameArea object.

    //Game state progressing functions, they also contain some other actions as well...
    void handleInitInProgress(); //Changes facing of cards and progresses init phase game state
    void handlePlayerMoveStart(); //Changes facing, progresses game state
    void handlePlayerMoveInProgress(); //If only source is set, show possible moves, otherwise resolve battle, progress game state
    void handleWaitPhaseStart(); //Change facing, reveal combatants, progress game state
    void handleWaitForNextPlayer(); //render wait msg, render game area, NO GAME STATE PROGRESS...
    void handleVictory(); //render victory screen, NO GAME STATE PROGRESS...

    //Rendering
    void renderButtons();
    void renderGameArea();
    void renderCardArea();
    void renderDiscardPile();
    void renderAvailableMoves();
    //void clearHighlights();
    //void changeFacingOfCards(Color color, bool faceDown);
    //void revealCombatants();

    //Input
    void handlePlayerClicks(); // get player click from display, delegate to input processing function based on game state, progress game state
    void restartGame(); //clears game area, sets game state
    Color getCurrentPlayerColor(); // returns color according to game state


    //Battle phase input
    //bool playerHasValidMoves(Color color);
    //std::vector<int> gatherNearbyValidFieldIndeces(unsigned char moveDist, int index, Color color);
    //void gatherViableMovesInDir(int index, unsigned char moveDist, Color color, std::vector<int> &result, Direction dir);
    //void resolveBattle();
    void triggerVictory(Color color); //Does nothing but sets game state to victory for color
    //int getNextEmptyDiscardPileIndex();


    std::vector<int> possibleMoves;
    std::unique_ptr<InputParser> input;
    Button restart;
    Button exit;
    ProcessedEvent attacker;
    ProcessedEvent defender;
    ProcessedEvent source;
    ProcessedEvent destination;
    std::unique_ptr<Display> display;
    GameState gameState;
    std::vector<std::unique_ptr<Field>> gameArea;
    std::vector<std::unique_ptr<Field>> cardArea;
    std::vector<std::unique_ptr<Field>> discardPile;

};