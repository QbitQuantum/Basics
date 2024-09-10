TEST(AgradFwdLogDiffExp,FvarVar_FvarVar_2ndDeriv) {
    using stan::agrad::fvar;
    using stan::agrad::var;
    using stan::math::log_diff_exp;
    using std::exp;

    fvar<var> x(9.0,1.3);
    fvar<var> z(6.0,1.0);
    fvar<var> a = log_diff_exp(x,z);

    AVEC y = createAVEC(x.val_,z.val_);
    VEC g;
    a.d_.grad(y,g);
    EXPECT_FLOAT_EQ((1.3 * exp(9.0) * (exp(9.0) - exp(6.0)) - exp(9.0)
                     * (1.3 * exp(9.0) - exp(6.0))) / (exp(9.0) - exp(6.0))
                    / (exp(9.0) - exp(6.0)) ,g[0]);
    EXPECT_FLOAT_EQ((-exp(6.0) * (exp(9.0) - exp(6.0)) + exp(6.0)
                     * (1.3 * exp(9.0) - exp(6.0))) / (exp(9.0) - exp(6.0))
                    / (exp(9.0) - exp(6.0)) ,g[1]);
}