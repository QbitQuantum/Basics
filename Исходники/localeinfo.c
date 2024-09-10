/*------------------------------------------------
  get locale information by ANSI
--------------------------------------------------*/
int MyGetLocaleInfoA(int ilang, int codepage,
	LCTYPE lctype, char* dst, int n)
{
	int r;
	LCID locale;
	
	*dst = 0;
	locale = MAKELCID((WORD)ilang, SORT_DEFAULT);
	
	if(GetVersion() & 0x80000000) // 95/98/Me
		r = GetLocaleInfoA(locale, lctype, dst, n);
	else  // NT4/2000/XP
	{
		WCHAR buf[80];
		r = GetLocaleInfoW(locale, lctype, buf, 80);
		if(r)
		{
			int codepage = GetCodePage(GetUserDefaultLangID());
			r = WideCharToMultiByte(codepage, 0, buf, -1, dst, n,
				NULL, NULL);
		}
	}
	
	return r;
}