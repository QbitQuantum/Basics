TEST(FutureTest, UndiscardableFuture)
{
  Promise<int> promise;

  Future<int> f = undiscardable(promise.future());

  f.discard();

  EXPECT_TRUE(f.hasDiscard());
  EXPECT_FALSE(promise.future().hasDiscard());

  promise.set(42);

  AWAIT_ASSERT_EQ(42, f);
}