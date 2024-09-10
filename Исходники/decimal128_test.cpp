TEST(Decimal128Test, TestDoubleConstructorQuantFailPoorLog10Of2Estimate) {
    double dbl = exp2(1000);
    Decimal128 d(dbl);
    ASSERT_EQUALS(d.toString(), "1.07150860718627E+301");
}