static void
h_wctomb(const struct test *t, char tc)
{
	wchar_t wcs[16 + 2];
	char buf[128];
	char cs[MB_LEN_MAX];
	const char *pcs;
	char *str;
	mbstate_t st;
	mbstate_t *stp = NULL;
	size_t sz, ret, i;

	ATF_REQUIRE_STREQ(setlocale(LC_ALL, "C"), "C");
	ATF_REQUIRE(setlocale(LC_CTYPE, t->locale) != NULL);

	(void)strvis(buf, t->data, VIS_WHITE | VIS_OCTAL);
	(void)printf("Checking sequence: \"%s\"\n", buf);

	ATF_REQUIRE((str = setlocale(LC_ALL, NULL)) != NULL);
	(void)printf("Using locale: %s\n", str);

	if (tc == TC_WCRTOMB_ST) {
		(void)memset(&st, 0, sizeof(st));
		stp = &st;
	}

	wcs[t->wclen] = L'X'; /* poison */
	pcs = t->data;
	sz = mbsrtowcs(wcs, &pcs, t->wclen + 2, NULL);
	ATF_REQUIRE_EQ_MSG(sz, t->wclen, "mbsrtowcs() returned: "
		"%zu, expected: %zu", sz, t->wclen);
	ATF_REQUIRE_EQ(wcs[t->wclen], 0);

	for (i = 0; i < t->wclen + 1; i++) {
		if (tc == TC_WCTOMB)
			ret = wctomb(cs, wcs[i]);
		else
			ret = wcrtomb(cs, wcs[i], stp);

		if (ret == t->mblen[i])
			continue;

		(void)printf("At position %zd:\n", i);
		(void)printf("  expected: %zd\n", t->mblen[i]);
		(void)printf("  got     : %zd\n", ret);
		atf_tc_fail("Test failed");
		/* NOTREACHED */
	}

	(void)printf("Ok.\n");
}