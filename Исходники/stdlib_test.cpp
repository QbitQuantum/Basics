TEST(stdlib, strtold) {
  ASSERT_DOUBLE_EQ(1.23, strtold("1.23", NULL));
}