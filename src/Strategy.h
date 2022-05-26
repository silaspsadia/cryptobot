#pragma once

class Strategy {
    public:
      Strategy(float dt, float utt, float pt, float slt, float ar)
        : dipThreshold_(dt),
          upwardTrendThreshold_(utt),
          profitThreshold_(pt),
          stopLossThreshold_(slt),
          actionRatio_(ar) {}

      virtual Instruction attemptToMakeTrade(Action, float) = 0;
    protected:
      virtual Instruction tryToBuy(float) = 0;
      virtual Instruction tryToSell(float) = 0;

      float dipThreshold_;
      float upwardTrendThreshold_;
      float profitThreshold_;
      float stopLossThreshold_;
      float actionRatio_;
};
