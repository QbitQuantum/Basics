void StringTest::testCompareShort()
{
    cxxtools::String s(L"abcd");

    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abcd")            , 0);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abc")             , 1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abcxyz")          , -1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abd")             , -1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abb")             , 1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("ab")              , 1);

    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abcd", 4)         , 0);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abcxyz", 3)       , 1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abcxyz", 4)       , -1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abd", 3)          , -1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("abb", 3)          , 1);
    CXXTOOLS_UNIT_ASSERT_EQUALS(s.compare("ab", 2)           , 1);

    cxxtools::String x1(L"abc");
    CXXTOOLS_UNIT_ASSERT(x1 == "abc");

    cxxtools::String y1(L"");
    cxxtools::String y2("");
    CXXTOOLS_UNIT_ASSERT(y1 == y2);
    CXXTOOLS_UNIT_ASSERT(y1 == "");
    CXXTOOLS_UNIT_ASSERT(y2 == "");
}