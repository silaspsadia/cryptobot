#pragma once
#include "Strategy.h"

class SimpleStrategy : public Strategy {
  public:
    SimpleStrategy()
      : Strategy(
          -2.5,   // dip threshold
          1.5,    // upward trend threshold
          1.25,   // profit threshold
          -2.00,  // stop loss threshold
          0.50    // action ratio
        ) {}

    Instruction attemptToMakeTrade(Action curAction, float percentDiff) {
      if (curAction == Action::BUY) {
        return tryToBuy(percentDiff);
      } else {
        return tryToSell(percentDiff);
      }
    }

  private:
    Instruction tryToBuy(float percentDiff) {
      if (percentDiff >= upwardTrendThreshold_ || percentDiff <= dipThreshold_) {
        return Instruction(Action::BUY, actionRatio_);
      }
      return Instruction();
    }

    Instruction tryToSell(float percentDiff) {
      if (percentDiff >= profitThreshold_ || percentDiff <= stopLossThreshold_) {
        return Instruction(Action::SELL, actionRatio_);
      }
      return Instruction();
    }
};
