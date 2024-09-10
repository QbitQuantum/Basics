TEST(AgradFwdPow, FvarVar_Double_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using std::log;
  using std::pow;

  fvar<var> x(0.5,1.0);
  double z(1.2);
  fvar<var> a = pow(x,z);

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ((1.2 - 1.0) * 1.2 * pow(0.5,1.2 - 2.0), g[0]);
}