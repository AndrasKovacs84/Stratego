#pragma once
#include <memory>
#include "Card.hpp"
#include "Display.h"

class Field {
public:
    Field();
    Field(size_t x, size_t y, bool isTraversable);
    ~Field() = default;

    size_t getX() const;
    size_t getY() const;
    bool getIsTraversable() const;
    bool getIsHighlighted() const;
    const std::unique_ptr<Card> &getContent() const;

    std::unique_ptr<Card> removeCard();
    void placeCard(std::unique_ptr<Card> cardToPlace);
    void highlight();
    void unhighlight();

    void setIsTraversable(bool isTraversable);

private:
    size_t x;
    size_t y;
    bool isTraversable;
    bool isHighlighted;
    std::unique_ptr<Card> content;
};