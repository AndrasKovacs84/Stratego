#include <iostream>
#include "Assets.h"

Assets::Assets() {

    // Initialising card face images
    for (int i = 0; i <= static_cast<int>(CardType::MARSHALL) ; ++i) {
        CardAsset tempCard;
        tempCard.type = static_cast<CardType>(i);
        tempCard.textureInAtlas.h = 50;
        tempCard.textureInAtlas.w = 50;
        tempCard.textureInAtlas.x = i * 50;
        tempCard.textureInAtlas.y = 520;
        tempCard.color = Color::RED;
        cardAssets.push_back(tempCard);

        tempCard.textureInAtlas.y = 570;
        tempCard.color = Color::BLUE;
        cardAssets.push_back(tempCard);
    }

    SDL_Rect tempRect;

    tempRect.h = 520;
    tempRect.w = 780;
    tempRect.x = 0;
    tempRect.y = 0;
    UIElements[UIElement::BACKGROUND] = tempRect;

    tempRect.h = 50;
    tempRect.w = 50;
    tempRect.x = 650;
    tempRect.y = 520;
    UIElements[UIElement::FIELD_HIGHLIGHT] = tempRect;

    tempRect.h = 50;
    tempRect.w = 50;
    tempRect.x = 600;
    tempRect.y = 520;
    UIElements[UIElement::RED_CARD_BACK] = tempRect;

    tempRect.h = 50;
    tempRect.w = 50;
    tempRect.x = 600;
    tempRect.y = 570;
    UIElements[UIElement::BLUE_CARD_BACK] = tempRect;

    tempRect.h = 30;
    tempRect.w = 80;
    tempRect.x = 0;
    tempRect.y = 620;
    UIElements[UIElement::RESTART_BTN] = tempRect;

    tempRect.h = 30;
    tempRect.w = 80;
    tempRect.x = 0;
    tempRect.y = 650;
    UIElements[UIElement::RESTART_BTN_PRESSED] = tempRect;

    tempRect.h = 30;
    tempRect.w = 80;
    tempRect.x = 80;
    tempRect.y = 620;
    UIElements[UIElement::EXIT_BTN] = tempRect;

    tempRect.h = 30;
    tempRect.w = 80;
    tempRect.x = 80;
    tempRect.y = 650;
    UIElements[UIElement::EXIT_BTN_PRESSED] = tempRect;

    tempRect.h = 250;
    tempRect.w = 500;
    tempRect.x = 0;
    tempRect.y = 680;
    UIElements[UIElement::MAP_OVERLAY_TOP_SHROUDED] = tempRect;

    tempRect.h = 250;
    tempRect.w = 500;
    tempRect.x = 0;
    tempRect.y = 930;
    UIElements[UIElement::MAP_OVERLAY_BOTTOM_SHROUDED] = tempRect;

    tempRect.h = 50;
    tempRect.w = 500;
    tempRect.x = 780;
    tempRect.y = 900;
    UIElements[UIElement::MAP_OVERLAY_FADE_BOTTOM_MAP] = tempRect;

    tempRect.y = 950;
    UIElements[UIElement::MAP_OVERLAY_FADE_TOP_MAP] = tempRect;

    tempRect.h = 280;
    tempRect.w = 250;
    tempRect.x = 500;
    tempRect.y = 620;
    UIElements[UIElement::MSG_WAIT_FOR_BLUE] = tempRect;

    tempRect.y = 900;
    UIElements[UIElement::MSG_WAIT_FOR_RED] = tempRect;

    tempRect.h = 150;
    tempRect.w = 500;
    tempRect.x = 780;
    tempRect.y = 0;
    UIElements[UIElement::VICTORY_COMMON_TOP] = tempRect;

    tempRect.h = 200;
    tempRect.y = 150;
    UIElements[UIElement::VICTORY_BLUE_MID] = tempRect;

    tempRect.y = 350;
    UIElements[UIElement::VICTORY_TIED] = tempRect;

    tempRect.y = 550;
    UIElements[UIElement::VICTORY_RED_MID] = tempRect;

    tempRect.h = 150;
    tempRect.y = 750;
    UIElements[UIElement::VICTORY_COMMON_BOTTOM] = tempRect;

    tempRect.h = 50;
    tempRect.w = 50;
    tempRect.x = 650;
    tempRect.y = 570;
    UIElements[UIElement::AVAILABLE_MOVE] = tempRect;

    tempRect.h = 260;
    tempRect.w = 780;
    tempRect.x = 0;
    tempRect.y = 1180;
    UIElements[UIElement::MENU_BACK_TOP] = tempRect;

    tempRect.h = 260;
    tempRect.w = 780;
    tempRect.x = 0;
    tempRect.y = 1440;
    UIElements[UIElement::MENU_BACK_BOTTOM] = tempRect;

    tempRect.h = 510;
    tempRect.w = 500;
    tempRect.x = 780;
    tempRect.y = 1180;
    UIElements[UIElement::MENU] = tempRect;

    tempRect.h = 50;
    tempRect.w = 270;
    tempRect.x = 780;
    tempRect.y = 1080;
    UIElements[UIElement::MENU_BTN] = tempRect;

    tempRect.h = 50;
    tempRect.w = 270;
    tempRect.x = 780;
    tempRect.y = 1130;
    UIElements[UIElement::MENU_BTN_PRESSED] = tempRect;

    tempRect.h = 520;
    tempRect.w = 780;
    tempRect.x = 0;
    tempRect.y = 1700;
    UIElements[UIElement::SPLASH] = tempRect;

    tempRect.h = 400;
    tempRect.w = 580;
    tempRect.x = 0;
    tempRect.y = 2220;
    UIElements[UIElement::MENU_MSG_BACKGROUND] = tempRect;
}


SDL_Rect *Assets::getTexturePosition(CardType type, Color color) {
    for (int i = 0; i < cardAssets.size() ; ++i) {
        if(cardAssets[i].type == type && cardAssets[i].color == color) {
            return &cardAssets[i].textureInAtlas;
        }
    }
    std::cout << "Could not find specified card texture!" << std::endl;
    return nullptr;
}

SDL_Rect *Assets::getUIElement(UIElement elementName) {
    return &UIElements[elementName];
}