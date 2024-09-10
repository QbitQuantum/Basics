// Clamping values inside the range should result in the same value.
TEST_F(RangeTests, Clamp_Outside) {
  const Range zero_one(0.0f, 1.0f);
  EXPECT_EQ(0.0f, zero_one.Clamp(-1.0f));
  EXPECT_EQ(1.0f, zero_one.Clamp(1.0000001f));
}