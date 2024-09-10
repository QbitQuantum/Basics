void
test_wcsrtombs_1(const char *locale, struct wcsrtombs_test *test)
{
	test_t		t;
	char 		*v;
	mbstate_t	ms;

	t = test_start("wcsrtombs (locale %s)", locale);

	v = setlocale(LC_ALL, locale);
	if (v == NULL) {
		test_failed(t, "setlocale failed: %s", strerror(errno));
	}
	if (strcmp(v, locale) != 0) {
		test_failed(t, "setlocale got %s instead of %s", v, locale);
	}

	for (int i = 0; test[i].mbs[0] != 0; i++) {
		char mbs[32];
		const wchar_t *wcs = test[i].wcs;
		size_t cnt;

		(void) memset(&ms, 0, sizeof (ms));
		(void) memset(mbs, 0, sizeof (mbs));
		cnt = wcsrtombs(mbs, &wcs, sizeof (mbs), &ms);
		if (cnt != strlen(test[i].mbs)) {
			test_failed(t, "incorrect return value: %d != %d",
			    cnt, strlen(test[i].mbs));
		}
		if (strcmp(mbs, test[i].mbs) != 0) {
			test_failed(t, "wrong result: %s != %s",
			    mbs, test[i].mbs);
		}
		if (extra_debug) {
			test_debugf(t, "mbs is %s", mbs);
		}
	}
	test_passed(t);
}