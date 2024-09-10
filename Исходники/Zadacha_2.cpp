void WriteCodeFile()
{
	int numclosed;
	errno_t err;
	UINT8 ch = 0;
	readFilename();

	err = fopen_s(&fcode, "code.txt", "wb");
	if (err == 0)
	{
		printf_s("The file CODE.txt was opened\n");
	}
	else
	{
		printf_s("The file CODE.txt was not opened\n");
		numclosed = _fcloseall();
	}
	while (!feof(fi))
	{

		fscanf_s(fi, "%c", &ch);
		if (feof(fi))
		{
			break;
		}
		if (strchr(rusUp, ch))
		{
			ch = ch - 0xC0 + 0xE0;
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);

		}
		else
		if (strchr(rusDown, ch))
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr(engUp, ch))
		{
			ch = ch - 'A' + 'a';
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr(engDown, ch))
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (strchr("-.,:!?;", ch))
		{
			ch = '.';
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (ch == ' ')
		{
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}
		else
		if (ch == 0xA8 || ch == 0xB8)
		{
			ch = 0xE5;
			fwrite(ArrAlfa[ch].code, ArrAlfa[ch].length, 1, fcode);
		}

	}
	numclosed = _fcloseall();

	system("pause");
}