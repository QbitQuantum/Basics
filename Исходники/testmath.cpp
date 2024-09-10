void testiik::test_div_zero()
{
    double a=rand() %HIGH_LIMIT;
    QVERIFY(std::isinf(M.div(a,0) ));
}