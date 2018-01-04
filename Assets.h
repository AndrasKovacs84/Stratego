#pragma once
#include <SDL_rect.h>
#include <vector>
#include <map>
#include "UIElement.h"
#include "CardType.h"
#include "Color.h"

class Assets {

public:
    Assets();

    SDL_Rect* getTexturePosition(CardType type, Color color);
    SDL_Rect* getUIElement(UIElement elementName);
private:

struct CardAsset{
    CardType type;
    Color color;
    SDL_Rect textureInAtlas;
};

    std::vector<CardAsset> cardAssets;
    std::map<UIElement, SDL_Rect> UIElements;
};