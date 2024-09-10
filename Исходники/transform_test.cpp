TEST(prob_transform, positive_f) {
  EXPECT_FLOAT_EQ(log(0.5), stan::prob::positive_free(0.5));
}