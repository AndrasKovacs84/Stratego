#pragma once
#include "Card.hpp"
#include "CardType.h"

class CardSargeant: public Card {

public:
    explicit CardSargeant(Color color) : Card(color) {}

    const CardType getType() const override {
        return TYPE;
    }

    unsigned char getMoveDistance() const override {
        return moveDistance;
    }

    bool canDefeat(CardType target) override {
        for (auto& defeatable: defeatables) {
            if(target == defeatable) {
                return true;
            }
        }
        return false;
    }

    static const int getNR_TO_SPAWN() {
        return NR_TO_SPAWN;
    }

private:
    const CardType TYPE = CardType::SARGEANT;
    static const int NR_TO_SPAWN = 4;
    const std::vector<CardType> defeatables = {
            CardType::FLAG,
            CardType::SPY,
            CardType::SCOUT,
            CardType::MINER,
            CardType::SARGEANT
    };

    unsigned char moveDistance = 1;
};