#include "MainMenu.h"



MainMenu::MainMenu() : topCurrentY(MainMenu::TOP_OPENING_TARGET_Y), bottomCurrentY(MainMenu::BOTTOM_OPENING_TARGET_Y),
    currentTopAnimState(BackgroundAnimState::CLOSING), currentBottomAnimState(BackgroundAnimState::CLOSING),
    previousSubmenu(SubmenuName::NONE) {}

void MainMenu::initMenu()
{
    submenus[SubmenuName::MAIN_MENU] = initMainMenu();
    submenus[SubmenuName::NEW_GAME] = initNewGameMenu();
    submenus[SubmenuName::HOW_TO_PLAY] = initHowToPlayMenu();
    submenus[SubmenuName::EXIT] = initExitMenu();
    
    submenus[SubmenuName::MULTIPLAYER] = initMultiplayerMenu();

    submenus[SubmenuName::MULTI_HOST] = initMultiHostMenu();
    submenus[SubmenuName::MULTI_JOIN] = initMultiJoinMenu();
}


MainMenu::~MainMenu()
{
}

Submenu & MainMenu::getSubmenu(SubmenuName name)
{
    return submenus[name];
}

int MainMenu::getNextY(bool top)
{
    int target = 0;
    if (currentTopAnimState == BackgroundAnimState::NOT_ANIMATED && top) return topCurrentY; 
    if (currentTopAnimState == BackgroundAnimState::CLOSING && top) target = MainMenu::TOP_CLOSING_TARGET_Y;
    if (currentTopAnimState == BackgroundAnimState::OPENING && top) target = MainMenu::TOP_OPENING_TARGET_Y;

    if (currentBottomAnimState == BackgroundAnimState::NOT_ANIMATED && !top) return bottomCurrentY;
    if (currentBottomAnimState == BackgroundAnimState::CLOSING && !top) target = MainMenu::BOTTOM_CLOSING_TARGET_Y;
    if (currentBottomAnimState == BackgroundAnimState::OPENING && !top) target = MainMenu::BOTTOM_OPENING_TARGET_Y;
    if (top)
    {
        topCurrentY += progressTowards(topCurrentY, target);
        if (topCurrentY == target) { currentTopAnimState = BackgroundAnimState::NOT_ANIMATED; }
        //std::cout << "topY: " << topCurrentY << std::endl;
        return topCurrentY;
    }
    if (!top) {
        bottomCurrentY += progressTowards(bottomCurrentY, target);
        if (bottomCurrentY == target) { currentBottomAnimState = BackgroundAnimState::NOT_ANIMATED; }
        //std::cout << "target: " << target << " ";
        //std::cout << "bottomY: " << bottomCurrentY << std::endl;
        return bottomCurrentY;
    }
}

void MainMenu::setAnimation(BackgroundAnimState animation)
{
    currentTopAnimState = animation;
    currentBottomAnimState = animation;
}

bool MainMenu::isAnimated()
{
    return currentTopAnimState != BackgroundAnimState::NOT_ANIMATED &&
        currentBottomAnimState != BackgroundAnimState::NOT_ANIMATED;
}


int MainMenu::progressTowards(int from, int targetY)
{
    double nextY = (targetY - from) / 10.0;
    if (nextY < 0) { nextY = std::floor(nextY); }
    else { nextY = std::ceil(nextY); }
    return static_cast<int>(nextY);
}



Submenu MainMenu::initMainMenu()
{
    Submenu mainMenu;

    MenuItem newGame("New Game", []() 
    { 
        States::getInstance()->setCurrentSubmenu(SubmenuName::NEW_GAME); 
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    mainMenu.addButton(newGame, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 0);

    MenuItem howTo("How to Play", []() 
    { 
        States::getInstance()->setCurrentSubmenu(SubmenuName::HOW_TO_PLAY); 
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    mainMenu.addButton(howTo, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 1);

    MenuItem exit("Exit Game", []() 
    { 
        States::getInstance()->setCurrentSubmenu(SubmenuName::EXIT); 
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    mainMenu.addButton(exit, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 4);

    return mainMenu;
}


Submenu MainMenu::initNewGameMenu()
{
    Submenu newGameMenu;

    MenuItem singlePlayer("Single player", []() {
        // disabled, since game mode is not implemented
        //States::getInstance()->setGameType(GameType::SINGLE_PLAYER);
        //States::getInstance()->setGamePhase(GamePhase::CARD_PLACEMENT);
        //States::getInstance()->setTurnState(TurnState::RESTART); // clears potentially ongoing game
        //States::getInstance()->setUIState(UIState::IN_GAME);
    });
    newGameMenu.addButton(singlePlayer, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 0);

    MenuItem hotseat("Local Hotseat", []() {
        States::getInstance()->setGameType(GameType::HOTSEAT);
        States::getInstance()->setGamePhase(GamePhase::CARD_PLACEMENT);
        States::getInstance()->setTurnState(TurnState::RESTART); // clears potentially ongoing game
        States::getInstance()->setUIState(UIState::IN_GAME);
    });
    newGameMenu.addButton(hotseat, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 1);

    MenuItem multiMenu("Multiplayer", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTIPLAYER);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    newGameMenu.addButton(multiMenu, 2);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 2);

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MAIN_MENU);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    newGameMenu.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 4);

    return newGameMenu;
}


Submenu MainMenu::initHowToPlayMenu()
{
    Submenu howToPlay;

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MAIN_MENU);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    howToPlay.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::HOW_TO_PLAY, 4);

    std::vector<std::string> message;
    message.emplace_back("The goal of the game is to conquer the enemy player's flag.");
    message.emplace_back("First strategically place the allotted cards from");
    message.emplace_back("the right hand card area to the open game field.");
    message.emplace_back("After both players have placed all their cards, they each");
    message.emplace_back("take turns moving or attacking with their cards.");
    message.emplace_back("Generally the higher value card defeats the lower value one.");
    message.emplace_back("If they are equal, they are both removed.");
    message.emplace_back("The lowest value cards have special rules applied to them:");
    message.emplace_back("1 - Spy - Can defeat the Marshall (10).");
    message.emplace_back("2 - Scout - Can move indefinitely in any one direction.");
    message.emplace_back("3 - Miner - The only card that can disarm the bomb.");
    howToPlay.setMessage(message);

    return howToPlay;
}

Submenu MainMenu::initExitMenu()
{
    Submenu exitMenu;

    MenuItem confirm("Confirm exit", []() {
        States::getInstance()->setUIState(UIState::QUIT);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    exitMenu.addButton(confirm, 2);
    InputParser::getInstance()->registerMenuItem(SubmenuName::EXIT, 2);

    MenuItem cancel("Cancel", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MAIN_MENU);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    exitMenu.addButton(cancel, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::EXIT, 4);

    return exitMenu;

}

Submenu MainMenu::initMultiplayerMenu()
{
    Submenu multiMenu;

    MenuItem host("Host game", []() {
        // TODO Figure how how to do this... be ready and wait for someone to join? something...
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTI_HOST);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    multiMenu.addButton(host, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTIPLAYER, 0);

    MenuItem join("Join game", []() {
        // TODO some way to join... field to input ip?
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTI_JOIN);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    multiMenu.addButton(join, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTIPLAYER, 1);

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::NEW_GAME);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    multiMenu.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTIPLAYER, 4);

    return multiMenu;
}

Submenu MainMenu::initMultiHostMenu()
{
    Submenu multiHost;

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTIPLAYER);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    multiHost.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTI_HOST, 4);

    return multiHost;
}

Submenu MainMenu::initMultiJoinMenu()
{
    Submenu multiJoin;

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTIPLAYER);
        States::getInstance()->setTurnState(TurnState::INIT);
    });
    multiJoin.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTI_JOIN, 4);

    return multiJoin;
}
