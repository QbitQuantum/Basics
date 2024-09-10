TEST(LoopTest, Sync)
{
  std::atomic_int value = ATOMIC_VAR_INIT(1);

  Future<Nothing> future = loop(
      [&]() {
        return value.load();
      },
      [](int i) -> ControlFlow<Nothing> {
        if (i != 0) {
          return Continue();
        }
        return Break();
      });

  EXPECT_TRUE(future.isPending());

  value.store(0);

  AWAIT_READY(future);
}