ATF_TC_BODY(wcspbrk, tc)
{
	static const wchar_t s[] = L"abcdefghijklmnop";

	ATF_CHECK_EQ(wcspbrk(s, L""), NULL);
	ATF_CHECK_EQ(wcspbrk(s, L"qrst"), NULL);
	ATF_CHECK_EQ(wcspbrk(s, L"a"), s);
	ATF_CHECK_EQ(wcspbrk(s, L"b"), s + 1);
	ATF_CHECK_EQ(wcspbrk(s, L"ab"), s);
	ATF_CHECK_EQ(wcspbrk(s, L"cdef"), s + 2);
	ATF_CHECK_EQ(wcspbrk(s, L"fedc"), s + 2);
}