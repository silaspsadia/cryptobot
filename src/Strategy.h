#pragma once

class Strategy {
    public:
      Strategy(float dt, float utt, float pt, float slt, float ar)
        : dipThreshold_(dt),
          upwardTrendThreshold_(utt),
          profitThreshold_(pt),
          stopLossThreshold_(slt),
          actionRatio_(ar) {}

      Instruction attemptToMakeTrade(Action, float);
    protected:
      Instruction tryToBuy(float);
      Instruction tryToSell(float);

      float dipThreshold_;
      float upwardTrendThreshold_;
      float profitThreshold_;
      float stopLossThreshold_;
      float actionRatio_;
};
