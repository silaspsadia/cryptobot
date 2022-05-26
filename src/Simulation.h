#pragma once
#include <chrono>
#include <thread>

#include "Action.h"
#include "Balance.h"
#include "Instruction.h"
#include "Strategy.h"

class Simulation {
  public:
    Simulation(Strategy& strategy, Balance& balance, int curPrice)
      : _strategy(strategy),
        _balance(balance),
        _curPrice(curPrice),
        _curAction(Action::BUY),
        _curIteration(0),
        _maxTotalValue(0) {}

    void run();
    void printState();
  private:
    int getRandomDelta();

    Strategy& _strategy;
    Balance& _balance;
    int _curPrice;
    Action _curAction;
    long _curIteration;
    float _maxTotalValue;
};
