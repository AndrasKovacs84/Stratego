#include "Field.h"

Field::Field(size_t x, size_t y, bool isTraversable) : x(x), y(y), isTraversable(isTraversable) {}

size_t Field::getX() const {
    return x;
}

size_t Field::getY() const {
    return y;
}

bool Field::getIsTraversable() const {
    return isTraversable;
}

bool Field::getIsHighlighted() const {
    return isHighlighted;
}

const std::unique_ptr<Card> &Field::getContent() const {
    return content;
}

std::unique_ptr<Card> Field::removeCard() {
    return std::move(content);
}

void Field::placeCard(std::unique_ptr<Card> cardToPlace) {
    content = std::move(cardToPlace);
}

Field::Field() {

}

void Field::highlight() {
    isHighlighted = true;
}

void Field::unhighlight() {
    isHighlighted = false;
}

void Field::setIsTraversable(bool isTraversable) {
    Field::isTraversable = isTraversable;
}
