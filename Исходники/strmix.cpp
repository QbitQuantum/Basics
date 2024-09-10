wchar_t* WINAPI TruncPathStr(wchar_t *Str, int MaxLength)
{
	assert(MaxLength >= 0);

	MaxLength=Max(0, MaxLength);

	if (Str)
	{
		int nLength = (int)wcslen(Str);

		if ((MaxLength > 0) && (nLength > MaxLength) && (nLength >= 2))
		{
			wchar_t *lpStart = nullptr;

			if (*Str && (Str[1] == L':') && IsSlash(Str[2]))
				lpStart = Str+3;
			else
			{
				if ((Str[0] == L'\\') && (Str[1] == L'\\'))
				{
					if ((lpStart = const_cast<wchar_t*>(FirstSlash(Str+2))) )
					{
						wchar_t *lpStart2=lpStart;

						if ((lpStart-Str < nLength) && ((lpStart=const_cast<wchar_t*>(FirstSlash(lpStart2+1)))))
							lpStart++;
					}
				}
			}

			if (!lpStart || (lpStart-Str > MaxLength-5))
				return TruncStr(Str, MaxLength);

			wchar_t *lpInPos = lpStart+3+(nLength-MaxLength);
			wmemmove(lpStart+3, lpInPos, (wcslen(lpInPos)+1));
			wmemcpy(lpStart, L"...", 3);
		}
	}

	return Str;
}