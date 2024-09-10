void KafkaSource::init(CtxPtr ctx) {
  consumer_.start();
  ctx->setTimer("loop", bolt::timeNowMilli());
}