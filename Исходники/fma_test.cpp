TEST(AgradRev,fma_vvd_defaultpolicy) {
  AVAR a = 3.0;
  AVAR b = 5.0;
  double c = 7.0;
  AVAR f = fma(a,b,c);
  EXPECT_FLOAT_EQ(3.0 * 5.0 + 7.0, f.val());
  
  AVEC x = createAVEC(a,b);
  VEC grad_f;
  f.grad(x,grad_f);
  EXPECT_FLOAT_EQ(5.0,grad_f[0]);
  EXPECT_FLOAT_EQ(3.0,grad_f[1]);
}  