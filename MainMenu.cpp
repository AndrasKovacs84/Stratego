#include "MainMenu.h"



MainMenu::MainMenu()
{
}

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
