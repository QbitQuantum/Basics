int test_unicode_uppercasing(BYTE* lower, BYTE* upper)
{
	WCHAR* lowerW = NULL;
	int lowerLength;
	WCHAR* upperW = NULL;
	int upperLength;

	lowerLength = ConvertToUnicode(CP_UTF8, 0, (LPSTR) lower, -1, &lowerW, 0);
	upperLength = ConvertToUnicode(CP_UTF8, 0, (LPSTR) upper, -1, &upperW, 0);

	CharUpperBuffW(lowerW, lowerLength);

	if (_wcscmp(lowerW, upperW) != 0)
	{
		printf("Lowercase String:\n");
		string_hexdump((BYTE*) lowerW, lowerLength * 2);

		printf("Uppercase String:\n");
		string_hexdump((BYTE*) upperW, upperLength * 2);

		return -1;
	}

	free(lowerW);
	free(upperW);

	return 0;
}