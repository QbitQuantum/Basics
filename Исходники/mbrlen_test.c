ATF_TC_BODY(mbrlen_test, tc)
{
	mbstate_t s;
	size_t len;
	char buf[MB_LEN_MAX + 1];

	/* C/POSIX locale. */
	ATF_REQUIRE(MB_CUR_MAX == 1);

	/* Null wide character, internal state. */
	memset(buf, 0xcc, sizeof(buf));
	buf[0] = 0;
	ATF_REQUIRE(mbrlen(buf, 1, NULL) == 0);

	/* Null wide character. */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 1, &s) == 0);

	/* Latin letter A, internal state. */
	ATF_REQUIRE(mbrlen(NULL, 0, NULL) == 0);
	buf[0] = 'A';
	ATF_REQUIRE(mbrlen(buf, 1, NULL) == 1);

	/* Latin letter A. */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 1, &s) == 1);

	/* Incomplete character sequence. */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 0, &s) == (size_t)-2);

	/* Japanese (EUC) locale. */

	ATF_REQUIRE(strcmp(setlocale(LC_CTYPE, "ja_JP.eucJP"), "ja_JP.eucJP") == 0);
	ATF_REQUIRE(MB_CUR_MAX > 1);

	/* Null wide character, internal state. */
	ATF_REQUIRE(mbrlen(NULL, 0, NULL) == 0);
	memset(buf, 0xcc, sizeof(buf));
	buf[0] = 0;
	ATF_REQUIRE(mbrlen(buf, 1, NULL) == 0);

	/* Null wide character. */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 1, &s) == 0);

	/* Latin letter A, internal state. */
	ATF_REQUIRE(mbrlen(NULL, 0, NULL) == 0);
	buf[0] = 'A';
	ATF_REQUIRE(mbrlen(buf, 1, NULL) == 1);

	/* Latin letter A. */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 1, &s) == 1);

	/* Incomplete character sequence (zero length). */
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 0, &s) == (size_t)-2);

	/* Incomplete character sequence (truncated double-byte). */
	memset(buf, 0xcc, sizeof(buf));
	buf[0] = 0xa3;
	buf[1] = 0x00;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 1, &s) == (size_t)-2);

	/* Same as above, but complete. */
	buf[1] = 0xc1;
	memset(&s, 0, sizeof(s));
	ATF_REQUIRE(mbrlen(buf, 2, &s) == 2);
}