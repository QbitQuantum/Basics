ATF_TC_BODY(wcsnrtombs_test, tc)
{
	wchar_t srcbuf[128];
	char dstbuf[128];
	wchar_t *src;
	mbstate_t s;

	/* C/POSIX locale. */

	/* Simple null terminated string. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, sizeof(dstbuf),
	    &s) == 5);
	ATF_REQUIRE(strcmp(dstbuf, "hello") == 0);
	ATF_REQUIRE((unsigned char)dstbuf[6] == 0xcc);
	ATF_REQUIRE(src == NULL);

	/* Simple null terminated string, stopping early. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 4, sizeof(dstbuf),
	    &s) == 4);
	ATF_REQUIRE(memcmp(dstbuf, "hell", 4) == 0);
	ATF_REQUIRE((unsigned char)dstbuf[5] == 0xcc);
	ATF_REQUIRE(src == srcbuf + 4);

	/* Not enough space in destination buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, 4,
	    &s) == 4);
	ATF_REQUIRE(memcmp(dstbuf, "hell", 4) == 0);
	ATF_REQUIRE((unsigned char)dstbuf[5] == 0xcc);
	ATF_REQUIRE(src == srcbuf + 4);

	/* Null terminated string, internal dest. buffer */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(NULL, (const wchar_t **)&src, 6, sizeof(dstbuf),
	    &s) == 5);

	/* Null terminated string, internal dest. buffer, stopping early. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(NULL, (const wchar_t **)&src, 4, sizeof(dstbuf),
	    &s) == 4);

	/* Null terminated string, internal state. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, sizeof(dstbuf),
	    NULL) == 5);
	ATF_REQUIRE(strcmp(dstbuf, "hello") == 0);
	ATF_REQUIRE((unsigned char)dstbuf[6] == 0xcc);
	ATF_REQUIRE(src == NULL);

	/* Null terminated string, internal state, internal dest. buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	src = srcbuf;
	ATF_REQUIRE(wcsnrtombs(NULL, (const wchar_t **)&src, 6, 0, NULL) == 5);

	/* Empty source buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	srcbuf[0] = L'\0';
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 1, sizeof(dstbuf),
	    &s) == 0);
	ATF_REQUIRE(dstbuf[0] == L'\0');

	/* Zero length destination buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, 0, &s) == 0);
	ATF_REQUIRE((unsigned char)dstbuf[0] == 0xcc);

	/* Zero length source buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 0, sizeof(dstbuf),
	    &s) == 0);
	ATF_REQUIRE((unsigned char)dstbuf[0] == 0xcc);
	ATF_REQUIRE(src == srcbuf);

	/*
	 * Japanese (EUC) locale.
	 */

	ATF_REQUIRE(strcmp(setlocale(LC_CTYPE, "ja_JP.eucJP"), "ja_JP.eucJP") == 0);
	ATF_REQUIRE(MB_CUR_MAX > 1);

	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	srcbuf[0] = 0xA3C1;
	srcbuf[1] = 0x0020;
	srcbuf[2] = 0x0042;
	srcbuf[3] = 0x0020;
	srcbuf[4] = 0xA3C3;
	srcbuf[5] = 0x0000;
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, sizeof(dstbuf),
	    &s) == 7);
	ATF_REQUIRE(strcmp(dstbuf, "\xA3\xC1 B \xA3\xC3") == 0);
	ATF_REQUIRE((unsigned char)dstbuf[8] == 0xcc);
	ATF_REQUIRE(src == NULL);

	/* Stopping early. */
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	src = srcbuf;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(wcsnrtombs(dstbuf, (const wchar_t **)&src, 6, 6,
	    &s) == 5);
	ATF_REQUIRE(memcmp(dstbuf, "\xA3\xC1 B ", 5) == 0);
	ATF_REQUIRE((unsigned char)dstbuf[5] == 0xcc);
	ATF_REQUIRE(src == srcbuf + 4);
}