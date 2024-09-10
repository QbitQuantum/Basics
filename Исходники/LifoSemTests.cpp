TEST(LifoSem, shutdown_race) {
  long seed = folly::randomNumberSeed() % 10000;
  LOG(INFO) << "seed=" << seed;

  bool shutdownWon = false;
  bool shutdownLost = false;
  for (int pass = 0; pass < 1000; ++pass) {
    DSched sched(DSched::uniformSubset(seed + pass, 1, 1 + (pass % 50)));

    DLifoSem a;
    int waitCount = 0;
    auto thr = DSched::thread([&]{
      try {
        while (true) {
          a.wait();
          ++waitCount;
        }
      } catch (ShutdownSemError& x) {
        // expected
        EXPECT_TRUE(a.isShutdown());
      }
    });
    EXPECT_TRUE(!a.isShutdown());
    a.shutdown();
    EXPECT_TRUE(a.isShutdown());
    a.post();
    DSched::join(thr);
    EXPECT_EQ(1, waitCount + a.valueGuess());
    if (waitCount == 0) {
      shutdownWon = true;
    } else {
      shutdownLost = true;
    }
  }
  EXPECT_TRUE(shutdownWon);
  EXPECT_TRUE(shutdownLost);
}