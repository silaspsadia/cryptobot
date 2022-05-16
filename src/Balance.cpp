#include "Balance.h"
#include "Instruction.h"

std::string Balance::getName() {
  return name_;
}

float Balance::getTotalValue(int curPrice) {
  return fiatBalance_ + coinBalance_ * curPrice;
}

float Balance::getFiatBalance() {
  return fiatBalance_;
}

float Balance::getCoinBalance() {
  return coinBalance_;
}

void Balance::depositFiat(float amount) {
  fiatBalance_ += (amount < 0) ? 0 : amount;
}

void Balance::withdrawFiat(float amount) {
  fiatBalance_ -= (amount < 0) ? 0 : amount;
}

void Balance::depositCoin(float amount) {
  coinBalance_ += (amount < 0) ? 0 : amount;
}

void Balance::withdrawCoin(float amount) {
  coinBalance_ -= (amount < 0) ? 0 : amount;
}

void Balance::executeInstruction(Instruction instruction, int curPrice) {
  if (instruction.getAction() == Action::BUY) {
    float fiatToWithdraw = fiatBalance_ / 2;
    float coinsToBuy = fiatToWithdraw / curPrice;
    withdrawFiat(fiatToWithdraw);
    depositCoin(coinsToBuy);
  } else if (instruction.getAction() == Action::SELL) {
    float coinsToSell = coinBalance_ / 2;
    float fiatToDeposit = coinsToSell * curPrice;
    withdrawCoin(coinsToSell);
    depositFiat(fiatToDeposit);
  }
}
