#pragma once
#include <memory>
#include <functional>
#include "Card.hpp"
#include "CardType.h"
#include "Color.h"
#include "CardBomb.hpp"
#include "CardFlag.hpp"
#include "CardSpy.hpp"
#include "CardScout.hpp"
#include "CardMiner.hpp"
#include "CardSargeant.hpp"
#include "CardLieutentant.hpp"
#include "CardCaptain.hpp"
#include "CardMajor.hpp"
#include "CardColonel.hpp"
#include "CardGeneral.hpp"
#include "CardMarshall.hpp"
#include <map>

class CardFactory 
{
public:
    static std::unique_ptr<Card> CreateInstance(CardType type, Color color);
};