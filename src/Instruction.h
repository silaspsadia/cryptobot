#pragma once
#include <iostream>

#include "Action.h"

struct Instruction {
  public:
    Instruction()
      : action_(Action::DO_NOTHING),
        percentBalance_(0) {}
    Instruction(Action action, float percentBalance)
      : action_(action),
        percentBalance_(percentBalance) {}
    Action getAction() {
      return action_;
    }
  private:
    Action action_;
    float percentBalance_;
    const char* actionStrings_[3] = { "DO_NOTHING", "BUY", "SELL" };
    friend std::ostream& operator<< (std::ostream &out, const Instruction& data);
};

inline std::ostream& operator<< (std::ostream &out, const Instruction& data) {
  out << "[" << data.actionStrings_[data.action_] << ", " << data.percentBalance_ << "]" << std::endl;
  return out;
}
