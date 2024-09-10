TEST(AgradFwdLog1pExp,Fvar) {
    using stan::agrad::fvar;
    using stan::math::log1p_exp;
    using std::exp;

    fvar<double> x(0.5,1.0);
    fvar<double> y(1.0,2.0);
    fvar<double> z(2.0,3.0);

    fvar<double> a = log1p_exp(x);
    EXPECT_FLOAT_EQ(log1p_exp(0.5), a.val_);
    EXPECT_FLOAT_EQ(exp(0.5) / (1 + exp(0.5)), a.d_);

    fvar<double> b = log1p_exp(y);
    EXPECT_FLOAT_EQ(log1p_exp(1.0), b.val_);
    EXPECT_FLOAT_EQ(2.0 * exp(1.0) / (1 + exp(1.0)), b.d_);

    fvar<double> a2 = log(1+exp(x));
    EXPECT_FLOAT_EQ(a.d_, a2.d_);

    fvar<double> b2 = log(1+exp(y));
    EXPECT_FLOAT_EQ(b.d_, b2.d_);
}