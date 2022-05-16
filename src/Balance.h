#pragma once
#include <iostream>
#include "Instruction.h"

class Balance {
    public:
      Balance()
        : name_("New Patron"),
          fiatBalance_(0),
          coinBalance_(0) {}
      Balance(std::string name)
        : name_(name),
          fiatBalance_(0),
          coinBalance_(0) {}
      std::string getName();
      float getTotalValue(int);
      float getFiatBalance();
      float getCoinBalance();
      void setName(std::string);
      void depositFiat(float);
      void withdrawFiat(float);
      void depositCoin(float);
      void withdrawCoin(float);
      void executeInstruction(Instruction, int);
    private:
      std::string name_;
      float fiatBalance_;
      float coinBalance_;
};
