int main()
{
	WCHAR *text;
	WCHAR temp[1001] = { 0 };
	WCHAR temp2[1001] = { 0 };

	printf("  WI  \n");
	printf("------\n");
	printf("\n");

	int size = 1024;
	//text = (WCHAR *)realloc(NULL, size << 1);
	text = (WCHAR *)calloc(1, (size << 1) + 2);
	text[0] = 0;

	int curl = 1;
	WCHAR *ptr = text;

	while (-1)
	{
		printf("%d: ", curl);
		memset(temp, 0, 1001);
		wscanf(L"%1000[a-zA-Z0-9?,.!()%:- ]", temp);
		fgetws(temp2, (sizeof(temp2)/ sizeof(temp2[0])) - 1, stdin); //NORMAL MAY BE

		if (wcscmp(temp, L":done") == 0)
			break;

		if (wcsncmp(temp, L":line ", 6) == 0)
		{
			swscanf(temp + 6, L"%d", &curl);
			if (curl < 0) return -2;
			if (curl >= (size << 1)) return -3;
			if (curl == 0)
				curl = 1;

			ptr = text;
			for (int i = 0; i < curl; ptr++)
			//for (int i = 0; i < curl || i < sizeof(text) / sizeof(text[0]); ptr++)
				if (*ptr == L'\n')
					i++;

			continue;
		}

		// replace arguments
		WCHAR *ptr2 = temp;
		int cnt = 0;
		while (-2)
		{
			ptr2 = wcschr(ptr2, L'%');
			if (ptr2 == NULL)
				break;

			if (ptr2[1] == L'%')  //%%???
			{
				for (int i = 0; i < wcslen(ptr2); i++)
					ptr2[i] = ptr2[i+1];  //1????
				ptr2--;
			}
			else if (ptr2[1] == L'l')
			{
				cnt++;
				ptr2[1] = L'd';
			}
			else
				for (int i = wcslen(ptr2); i >= 0; i--)
					ptr2[i + 1] = ptr2[i];

			ptr2 += 2;
		}

		for (int i = 0; i < cnt; i++)
			__asm push curl;

		int space = _snwprintf(NULL, 0, temp);

		int temp3 = cnt << 2;
		__asm add esp, temp3;

		// reallocate
		if (((wcslen(text) + space + 1) << 1) > (size << 1) - 2)
		{
			text = (WCHAR *)realloc(text, (wcslen(text) + space + 1) << 1);
			size = wcslen(text) + space + 1;
		}
		
		// move
		for (int i = wcslen(ptr); i >= 0; i--)
			ptr[i + space + 1] = ptr[i];

		for (int i = 0; i < cnt; i++)
			__asm push curl;

		_snwprintf(ptr, space, temp);

		temp3 = cnt << 2;
		__asm add esp, temp3;

		ptr[space] = L'\n';

		ptr += space + 1;
		curl++;
	}

	wprintf(L"\n\n");
	wprintf(L"THE FINAL TEXT\n");
	wprintf(L"==============\n");
	wprintf(L"%s\n\n", text);

	return -14;
}