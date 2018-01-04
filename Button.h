#pragma once
#include <SDL_rect.h>
#include "UIElement.h"

class Button {
public:
    bool isPressedDown() const;

    const SDL_Rect &getPosition() const;
    const UIElement &getCurrentTexture() const;

    void setNormalTexture(UIElement normalTexture);
    void setPressedDownTexture(UIElement pressedDownTexture);
    void setPosition(const SDL_Rect &position);

    void setPressedDown(bool pressedDown);

private:
    SDL_Rect position;
    bool pressedDown;
    UIElement normalTexture;
    UIElement pressedDownTexture;
};