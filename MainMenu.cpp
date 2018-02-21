#include "MainMenu.h"



MainMenu::MainMenu()
{
}

void MainMenu::initMenu()
{
    //TODO Create the different submenus within the main menu
    Submenu mainMenu;

    Button newGame;
    newGame.setCaption("New Game");
    mainMenu.addButton();
    submenus[SubmenuName::MAIN_MENU] = mainMenu;
}


MainMenu::~MainMenu()
{
}
