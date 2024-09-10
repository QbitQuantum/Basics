 void init(CtxPtr ctx) override {
   ctx->setTimer("interval_loop", bolt::timeNowMilli());
 }