#pragma once
#include "Card.hpp"
#include "CardType.h"

class CardMiner: public Card {

public:
    explicit CardMiner(Color color) : Card(color) {}

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
    const CardType TYPE = CardType::MINER;
    static const int NR_TO_SPAWN = 5;
    const std::vector<CardType> defeatables = {
            CardType::BOMB,
            CardType::FLAG,
            CardType::SPY,
            CardType::SCOUT,
            CardType::MINER
    };

    unsigned char moveDistance = 1;
};