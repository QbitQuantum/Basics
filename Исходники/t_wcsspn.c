ATF_TC_BODY(wcsspn, tc)
{
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L""), 0);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"a"), 1);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"b"), 0);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"ab"), 2);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"abc"), 3);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"abce"), 3);
	ATF_CHECK_EQ(wcsspn(L"abcdefghijklmnop", L"abcdefghijklmnop"), 16);
}