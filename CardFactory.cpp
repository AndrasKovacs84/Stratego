#include "CardFactory.h"

std::unique_ptr<Card> CardFactory::CreateInstance(CardType type, Color color)
{
    std::unique_ptr<Card> tempCard = nullptr;
    switch (type) {
    case CardType::FLAG: {
        tempCard = std::unique_ptr<CardFlag>(new CardFlag(color));
        break;
    }
    case CardType::BOMB: {
        tempCard = std::unique_ptr<CardBomb>(new CardBomb(color));
        break;
    }
    case CardType::SPY: {
        tempCard = std::unique_ptr<CardSpy>(new CardSpy(color));
        break;
    }
    case CardType::SCOUT: {
        tempCard = std::unique_ptr<CardScout>(new CardScout(color));
        break;
    }
    case CardType::MINER: {
        tempCard = std::unique_ptr<CardMiner>(new CardMiner(color));
        break;
    }
    case CardType::SARGEANT: {
        tempCard = std::unique_ptr<CardSargeant>(new CardSargeant(color));
        break;
    }
    case CardType::LIEUTENANT: {
        tempCard = std::unique_ptr<CardLieutenant>(new CardLieutenant(color));
        break;
    }
    case CardType::CAPTAIN: {
        tempCard = std::unique_ptr<CardCaptain>(new CardCaptain(color));
        break;
    }
    case CardType::MAJOR: {
        tempCard = std::unique_ptr<CardMajor>(new CardMajor(color));
        break;
    }
    case CardType::COLONEL: {
        tempCard = std::unique_ptr<CardColonel>(new CardColonel(color));
        break;
    }
    case CardType::GENERAL: {
        tempCard = std::unique_ptr<CardGeneral>(new CardGeneral(color));
        break;
    }
    case CardType::MARSHALL: {
        tempCard = std::unique_ptr<CardMarshall>(new CardMarshall(color));
        break;
    }
    }
    return std::move(tempCard);
}