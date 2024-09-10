int
main(int argc, char *argv[])
{
	int i;

	printf("1..2\n");

	/*
	 * C/POSIX locale.
	 */
	assert(btowc(EOF) == WEOF);
	assert(wctob(WEOF) == EOF);
	for (i = 0; i < UCHAR_MAX; i++)
		assert(btowc(i) == (wchar_t)i && i == (int)wctob(i));

	/*
	 * Japanese (EUC) locale.
	 */

	assert(strcmp(setlocale(LC_CTYPE, "ja_JP.eucJP"), "ja_JP.eucJP") == 0);
	assert(MB_CUR_MAX > 1);
	assert(btowc('A') == L'A' && wctob(L'A') == 'A');
	assert(btowc(0xa3) == WEOF && wctob(0xa3c1) == EOF);

	printf("ok 1 - btowc()\n");
	printf("ok 2 - wctob()\n");

	return (0);
}