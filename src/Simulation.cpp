#include <iostream>
#include <cstdlib>
#include <time.h>

#include "Simulation.h"
#include "Strategy.h"

int Simulation::getRandomDelta() {
  int multiplier[2] = {1, -1};
  return std::rand() % 100 * multiplier[std::rand() % 2];
}

void Simulation::run() {
  srand(time(NULL));
  while (_balance.getTotalValue(_curPrice) > 0) {
    float delta = (float) Simulation::getRandomDelta();
    float percentDiff = delta / _curPrice * 100;
    _curPrice += delta;

    Instruction curInstruction = _strategy.attemptToMakeTrade(_curAction, percentDiff);
    // TODO: need sto extract sell/buy functionality into Exchange interface that works with balance
    _balance.executeInstruction(curInstruction, _curPrice);

    std::cout << "\nIteration " << _curIteration << std::endl;
    std::cout << curInstruction << std::endl;
    std::cout << percentDiff << std::endl;
    std::cout << "Total Value: " << _balance.getTotalValue(_curPrice) << std::endl;
    std::cout << "\tFiat Value: " << _balance.getFiatBalance() << std::endl;
    std::cout << "\tCoin Value: " << _balance.getCoinBalance() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (curInstruction.getAction() != Action::DO_NOTHING) {
      _curAction = _curAction == Action::BUY ? Action::SELL : Action::BUY;
    }

    if (_balance.getTotalValue(_curPrice) > _maxTotalValue) {
      _maxTotalValue = _balance.getTotalValue(_curPrice);
    }

    _curIteration++;
  }
}

void Simulation::printState() {
  std::cout << "END OF SIMULATION" << std::endl;
  std::cout << "Iterations: " << _curIteration << std::endl;
  std::cout << "Max Account Valu: " << _maxTotalValue << std::endl;
}
