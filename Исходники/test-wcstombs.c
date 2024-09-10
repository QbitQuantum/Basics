int
main(int argc, char *argv[])
{
	wchar_t srcbuf[128];
	char dstbuf[128];

	/*
	 * C/POSIX locale.
	 */

	printf("1..1\n");

	/* Simple null terminated string. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, sizeof(dstbuf)) == 5);
	assert(strcmp(dstbuf, "hello") == 0);
	assert((unsigned char)dstbuf[6] == 0xcc);

	/* Not enough space in destination buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, 4) == 4);
	assert(memcmp(dstbuf, "hell", 4) == 0);
	assert((unsigned char)dstbuf[5] == 0xcc);

	/* Null terminated string, internal dest. buffer */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	assert(wcstombs(NULL, srcbuf, sizeof(dstbuf)) == 5);

	/* Null terminated string, internal state. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, sizeof(dstbuf)) == 5);
	assert(strcmp(dstbuf, "hello") == 0);
	assert((unsigned char)dstbuf[6] == 0xcc);

	/* Null terminated string, internal state, internal dest. buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	assert(wcstombs(NULL, srcbuf, 0) == 5);

	/* Empty source buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	srcbuf[0] = L'\0';
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, sizeof(dstbuf)) == 0);
	assert(dstbuf[0] == L'\0');

	/* Zero length destination buffer. */
	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	wcscpy(srcbuf, L"hello");
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, 0) == 0);
	assert((unsigned char)dstbuf[0] == 0xcc);

	/*
	 * Japanese (EUC) locale.
	 */

	assert(strcmp(setlocale(LC_CTYPE, "ja_JP.eucJP"), "ja_JP.eucJP") == 0);
	assert(MB_CUR_MAX > 1);

	wmemset(srcbuf, 0xcc, sizeof(srcbuf) / sizeof(*srcbuf));
	srcbuf[0] = 0xA3C1;
	srcbuf[1] = 0x0020;
	srcbuf[2] = 0x0042;
	srcbuf[3] = 0x0020;
	srcbuf[4] = 0xA3C3;
	srcbuf[5] = 0x0000;
	memset(dstbuf, 0xcc, sizeof(dstbuf));
	assert(wcstombs(dstbuf, srcbuf, sizeof(dstbuf)) == 7);
	assert(strcmp(dstbuf, "\xA3\xC1 B \xA3\xC3") == 0);
	assert((unsigned char)dstbuf[8] == 0xcc);

	printf("ok 1 - wcstombs()\n");

	return (0);
}