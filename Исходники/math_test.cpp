TEST(math, yn) {
  ASSERT_FLOAT_EQ(-HUGE_VAL, yn(4, 0.0));
  ASSERT_FLOAT_EQ(-33.278423, yn(4, 1.0));
}