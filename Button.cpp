
#include "Button.h"


bool Button::isPressedDown() const {
    return pressedDown;
}

void Button::setPosition(const SDL_Rect &position) {
    Button::position = position;
}

void Button::setCaption(std::string caption)
{
    this.caption = caption;
}

const SDL_Rect &Button::getPosition() const {
    return position;
}

void Button::setNormalTexture(UIElement normalTexture) {
    Button::normalTexture = normalTexture;
}

void Button::setPressedDownTexture(UIElement pressedDownTexture) {
    Button::pressedDownTexture = pressedDownTexture;
}

const UIElement &Button::getCurrentTexture() const {
    if(pressedDown) {
        return pressedDownTexture;
    } else {
        return normalTexture;
    }
}

void Button::setPressedDown(bool pressedDown) {
    Button::pressedDown = pressedDown;
}
