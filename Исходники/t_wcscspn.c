ATF_TC_BODY(wcscspn, tc)
{
	ATF_CHECK_EQ(wcscspn(L"abcdefghijklmnop", L""), 16);
	ATF_CHECK_EQ(wcscspn(L"abcdefghijklmnop", L"a"), 0);
	ATF_CHECK_EQ(wcscspn(L"abcdefghijklmnop", L"b"), 1);
	ATF_CHECK_EQ(wcscspn(L"abcdefghijklmnop", L"cd"), 2);
	ATF_CHECK_EQ(wcscspn(L"abcdefghijklmnop", L"qrstuvwxyz"), 16);
}