#include <iostream>

#include "Action.h"
#include "Instruction.h"
#include "Balance.h"
#include "SimpleStrategy.h"
#include "Simulation.h"

int main() {
  SimpleStrategy ss;

  Balance b1("Silas Sadia");
  b1.depositFiat(100000.00);

  int startingPrice = 1000;

  Simulation simulation(ss, b1, startingPrice);
  simulation.run();
  simulation.printState();

  return 0;
}
