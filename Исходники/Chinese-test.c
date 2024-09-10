void find_unique_chars()
	{
	wchar_t s[1024];

	wprintf(L"Finding unique characters...\n");

	FILE *fp1;
	if((fp1 = fopen("/home/yky/NetBeansProjects/conceptual-keyboard/training-set.txt", "r")) == NULL)
		{ printf("cannot open training-set.txt\n"); exit(1); }

	while (fwscanf(fp1, L"%S", s) > 0) {
		wprintf(s);
		wprintf(L"\n");
		addInChars(s);

		fwscanf(fp1, L"%S", s);
		wprintf(s);
		wprintf(L"\n");
		addOutChars(s);
		}

	fclose(fp1);

	wprintf(inChars);
	wprintf(L"\n");
	wprintf(outChars);
	wprintf(L"\n");
	}