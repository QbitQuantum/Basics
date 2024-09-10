TEST(AgradRev,asinh_val) {
  AVAR a = 0.2;
  AVAR f = asinh(a);
  EXPECT_FLOAT_EQ(0.198690110349, f.val());

  AVEC x = createAVEC(a);
  VEC g;
  f.grad(x,g);
  EXPECT_FLOAT_EQ(1.0/sqrt(0.2 * 0.2  + 1.0), g[0]);
}