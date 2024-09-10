TEST(AgradFwdFabs,FvarFvarDouble) {
  using stan::agrad::fvar;
  using std::fabs;

  fvar<fvar<double> > x;
  x.val_.val_ = 1.5;
  x.val_.d_ = 2.0;

  fvar<fvar<double> > a = fabs(x);

  EXPECT_FLOAT_EQ(fabs(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(2.0, a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 1.5;
  y.d_.val_ = 2.0;  

  a = fabs(y);
  EXPECT_FLOAT_EQ(fabs(1.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(2.0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}