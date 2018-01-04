#pragma once
#include <map>
#include <vector>
#include <cmath>
#include "FlipAnimState.h"
#include "CardType.h"
#include "Color.h"

class Card {

public:
    explicit Card(Color color) : color(color) {}
    virtual bool canDefeat(CardType target) = 0;
    virtual const CardType getType() const = 0;
    virtual unsigned char getMoveDistance() const = 0;

    bool getIsFaceDown() const {
        return isFaceDown;
    }

    void setIsFaceDown(bool isFaceDown) {
        Card::isFaceDown = isFaceDown;
    }

    Color getColor() const {
        return color;
    }

    int getCurrentX() const {
        return currentX;
    }

    void setCurrentX(int currentX) {
        Card::currentX = currentX;
    }

    int getCurrentY() const {
        return currentY;
    }

    void setCurrentY(int currentY) {
        Card::currentY = currentY;
    }

    int getNextXPos(int destinationX) {
        double step;
        if(currentX < destinationX) {
            step = destinationX - currentX;
            currentX += std::ceil(step / 30);
        } else if(currentX > destinationX) {
            step = currentX - destinationX;
            currentX -= std::ceil(step / 30);
        }
        return currentX;
    }

    int getNextYPos(int destinationY) {
        double step;
        if(currentY < destinationY) {
            step = destinationY - currentY;
            currentY += std::ceil(step / 30);
        } else if(currentY > destinationY) {
            step = currentY - destinationY;
            currentY -= std::ceil(step / 30);
        }
        return currentY;
    }

    FlipAnimState getCurrentFlipState() {
        return currentFlipState;
    }

    void setCurrentFlipAnim(FlipAnimState state, int delay, int animLength) {
        currentFlipState = state;
        delayFrames = delay;
        animFrames = animLength;
    }

    int getNextFlipAnimFrameWidth() {
        if (delayFrames > 0) {
            delayFrames--;
            return 50;
        } else {
            if (animFrames > -25 && currentFlipState != FlipAnimState::NOT_ANIMATED) {
                animFrames--;
            }
            if (animFrames == 0) {
                if (currentFlipState == FlipAnimState::TURNING_FACE_DOWN) isFaceDown = true;
                if (currentFlipState == FlipAnimState::TURNING_FACE_UP) isFaceDown = false;
            }
            if(animFrames == -25) {
                currentFlipState = FlipAnimState::NOT_ANIMATED;
                animFrames = 25;
            }
            return abs(animFrames)*2;
        }
    }

protected:
    int currentX;
    int currentY;

    FlipAnimState currentFlipState = FlipAnimState::NOT_ANIMATED;
    int delayFrames = 0;
    int animFrames = 50;

    bool isFaceDown = false;
    Color color;
};