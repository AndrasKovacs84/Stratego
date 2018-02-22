#include "MainMenu.h"



MainMenu::MainMenu() : topCurrentY(MainMenu::TOP_OPENING_TARGET_Y), bottomCurrentY(MainMenu::BOTTOM_OPENING_TARGET_Y),
    currentTopAnimState(BackgroundAnimState::CLOSING), currentBottomAnimState(BackgroundAnimState::CLOSING) {}

void MainMenu::initMenu()
{
    //TODO Create the different submenus within the main menu

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
    //if (currentAnimState == BackgroundAnimState::NOT_ANIMATED)
    //{
    //    return topCurrentY;
    //}
    //else if (currentAnimState == BackgroundAnimState::CLOSING)
    //{
    //    return getNextTopClosingY();
    //}
    //else if (currentAnimState == BackgroundAnimState::OPENING)
    //{
    //    return getNextTopOpeningY();
    //}
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
        std::cout << "topY: " << topCurrentY << std::endl;
        return topCurrentY;
    }
    if (!top) {
        bottomCurrentY += progressTowards(bottomCurrentY, target);
        if (bottomCurrentY == target) { currentBottomAnimState = BackgroundAnimState::NOT_ANIMATED; }
        std::cout << "target: " << target << " ";
        std::cout << "bottomY: " << bottomCurrentY << std::endl;
        return bottomCurrentY;
    }
}


int MainMenu::progressTowards(int from, int targetY)
{
    double nextY = (targetY - from) / 2.0;
    if (nextY < 0) { nextY = std::floor(nextY); }
    else { nextY = std::ceil(nextY); }
    return static_cast<int>(nextY);
}

int MainMenu::getNextTopOpeningY()
{
    //topCurrentY = (MainMenu::TOP_OPENING_TARGET_Y - topCurrentY) / 2;

    //if (topCurrentY == MainMenu::TOP_OPENING_TARGET_Y)
    //{
    //    setAnimState(BackgroundAnimState::NOT_ANIMATED);
    //}
    //return topCurrentY;
    return 0;
}

int MainMenu::getNextBottomOpeningY()
{
    //bottomCurrentY = (MainMenu::BOTTOM_OPENING_TARGET_Y - bottomCurrentY) / 2;
    //if (bottomCurrentY == MainMenu::BOTTOM_OPENING_TARGET_Y)
    //{
    //    setAnimState(BackgroundAnimState::NOT_ANIMATED);
    //}
    //return bottomCurrentY;
    return 0;
}

int MainMenu::getNextBottomY()
{
    //if (currentAnimState == BackgroundAnimState::NOT_ANIMATED)
    //{
    //    return bottomCurrentY;
    //}
    //else if (currentAnimState == BackgroundAnimState::CLOSING)
    //{
    //    return getNextBottomClosingY();
    //}
    //else if (currentAnimState == BackgroundAnimState::OPENING)
    //{
    //    return getNextBottomOpeningY();
    //}
    return 0;
}

int MainMenu::getNextTopClosingY()
{
    //topCurrentY += (MainMenu::TOP_CLOSING_TARGET_Y - topCurrentY) / 2 - 1;

    //if (topCurrentY == MainMenu::TOP_CLOSING_TARGET_Y)
    //{
    //    setAnimState(BackgroundAnimState::NOT_ANIMATED);
    //}
    //return topCurrentY;
    return 0;
}

int MainMenu::getNextBottomClosingY()
{
    //bottomCurrentY += (MainMenu::BOTTOM_CLOSING_TARGET_Y - bottomCurrentY) / 2 - 1;
    //if (bottomCurrentY == MainMenu::BOTTOM_CLOSING_TARGET_Y)
    //{
    //    setAnimState(BackgroundAnimState::NOT_ANIMATED);
    //}
    //return bottomCurrentY;
    return 0;
}


Submenu MainMenu::initMainMenu()
{
    Submenu mainMenu;

    MenuItem newGame("New Game", []() { States::getInstance()->setCurrentSubmenu(SubmenuName::NEW_GAME); });
    mainMenu.addButton(newGame, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 0);

    MenuItem howTo("How to Play", []() { States::getInstance()->setCurrentSubmenu(SubmenuName::HOW_TO_PLAY); });
    mainMenu.addButton(howTo, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 1);

    MenuItem exit("Exit Game", []() { States::getInstance()->setCurrentSubmenu(SubmenuName::EXIT); });
    mainMenu.addButton(exit, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MAIN_MENU, 4);

    return mainMenu;
}


Submenu MainMenu::initNewGameMenu()
{
    Submenu newGameMenu;

    MenuItem singlePlayer("Single player", []() {
        States::getInstance()->setGameType(GameType::SINGLE_PLAYER);
        States::getInstance()->setGamePhase(GamePhase::CARD_PLACEMENT);
        States::getInstance()->setTurnState(TurnState::INIT);
        States::getInstance()->setUIState(UIState::IN_GAME);
    });
    newGameMenu.addButton(singlePlayer, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 0);

    MenuItem hotseat("Local Hotseat", []() {
        States::getInstance()->setGameType(GameType::HOTSEAT);
        States::getInstance()->setGamePhase(GamePhase::CARD_PLACEMENT);
        States::getInstance()->setTurnState(TurnState::INIT);
        States::getInstance()->setUIState(UIState::IN_GAME);
    });
    newGameMenu.addButton(hotseat, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 1);

    MenuItem multiMenu("Multiplayer", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTIPLAYER);
    });
    newGameMenu.addButton(multiMenu, 2);
    InputParser::getInstance()->registerMenuItem(SubmenuName::NEW_GAME, 2);

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MAIN_MENU);
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
    });
    howToPlay.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::HOW_TO_PLAY, 4);

    return howToPlay;
}

Submenu MainMenu::initExitMenu()
{
    Submenu exitMenu;

    MenuItem confirm("Confirm exit", []() {
        States::getInstance()->setUIState(UIState::QUIT);
    });
    exitMenu.addButton(confirm, 2);
    InputParser::getInstance()->registerMenuItem(SubmenuName::EXIT, 2);

    MenuItem cancel("Cancel", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::MAIN_MENU);
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
    });
    multiMenu.addButton(host, 0);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTIPLAYER, 0);

    MenuItem join("Join game", []() {
        // TODO some way to join... field to input ip?
        States::getInstance()->setCurrentSubmenu(SubmenuName::MULTI_JOIN);
    });
    multiMenu.addButton(join, 1);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTIPLAYER, 1);

    MenuItem back("Back", []() {
        States::getInstance()->setCurrentSubmenu(SubmenuName::NEW_GAME);
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
    });
    multiJoin.addButton(back, 4);
    InputParser::getInstance()->registerMenuItem(SubmenuName::MULTI_JOIN, 4);

    return multiJoin;
}
