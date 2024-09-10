void test_trunc()
{
    static_assert((std::is_same<decltype(trunc((double)0)), double>::value), "");
    static_assert((std::is_same<decltype(truncf(0)), float>::value), "");
    static_assert((std::is_same<decltype(truncl(0)), long double>::value), "");
    assert(trunc(1) == 1);
}