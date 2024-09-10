ATF_TC_BODY(mbsnrtowcs, tc)
{
	size_t i;
	const struct test *t;
	mbstate_t state;
	wchar_t buf[64];
	const char *src;
	size_t len;

	for (i = 0; i < __arraycount(tests); ++i) {
		t = &tests[i];
		ATF_REQUIRE_STREQ(setlocale(LC_ALL, "C"), "C");
		ATF_REQUIRE(setlocale(LC_CTYPE, t->locale) != NULL);
		memset(&state, 0, sizeof(state));
		src = t->data;
		len = mbsnrtowcs(buf, &src, t->limit,
		    __arraycount(buf), &state);
		ATF_REQUIRE_EQ(src, t->data + t->limit);
		ATF_REQUIRE_EQ(len, t->output1_len);
		ATF_REQUIRE(wmemcmp(t->output1, buf, len) == 0);
		len = mbsnrtowcs(buf, &src, strlen(src) + 1,
		    __arraycount(buf), &state);
		ATF_REQUIRE_EQ(len, strlen(t->data) - t->limit);
		ATF_REQUIRE(wmemcmp(t->output2, buf, len + 1) == 0);
		ATF_REQUIRE_EQ(src, NULL);
	}
}