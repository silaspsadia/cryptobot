#include <iostream>
#include <cstdlib>
#include <chrono>
#include <time.h>
#include <thread>

#include "Action.h"
#include "Instruction.h"
#include "Balance.h"
#include "SimpleStrategy.h"

// TODO: once we have an actual exchange interface that works, we need to put random functions in a Simulator class
int genRandomDelta() {
  int multiplier[2] = {1, -1};
  return std::rand() % 100 * multiplier[std::rand() % 2];
}

int main() {
  srand(time(NULL));
  // TODO: need to encapsulate and manage global state
  SimpleStrategy ss;
  Balance b1("Silas Sadia");
  b1.depositFiat(100000.00);

  int curPrice = 1000;
  Action curAction = Action::BUY;
  long curIteration = 0;
  float maxTotalValue = 0;

  while (b1.getTotalValue(curPrice) > 0) {
    float delta = (float) genRandomDelta();
    float percentDiff = delta / curPrice * 100;
    curPrice += delta;

    Instruction curInstruction = ss.attemptToMakeTrade(curAction, percentDiff);
    // TODO: need sto extract sell/buy functionality into Exchange interface that works with balance
    b1.executeInstruction(curInstruction, curPrice);

    std::cout << "\nIteration " << curIteration << std::endl;
    std::cout << curInstruction << std::endl;
    std::cout << percentDiff << std::endl;
    std::cout << "Total Value: " << b1.getTotalValue(curPrice) << std::endl;
    std::cout << "\tFiat Value: " << b1.getFiatBalance() << std::endl;
    std::cout << "\tCoin Value: " << b1.getCoinBalance() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    if (curInstruction.getAction() != Action::DO_NOTHING) {
      curAction = curAction == Action::BUY ? Action::SELL : Action::BUY;
    }

    if (b1.getTotalValue(curPrice) > maxTotalValue) {
      maxTotalValue = b1.getTotalValue(curPrice);
    }

    curIteration++;
  }

  std::cout << "####END OF SIMULATION####" << std::endl;
  std::cout << "ITERATIONS: " << curIteration + 1 << std::endl;
  std::cout << "MAX TOTAL VALUE: " << maxTotalValue <<  std::endl;

  return 0;
}
