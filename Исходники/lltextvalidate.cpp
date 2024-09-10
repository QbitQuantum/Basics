	bool validateAlphaNumSpace(const LLWString &str)
	{
		LLLocale locale(LLLocale::USER_LOCALE);

		bool rv = TRUE;
		S32 len = str.length();
		if(len == 0) return rv;
		while(len--)
		{
			if(!(LLStringOps::isAlnum((char)str[len]) || (' ' == str[len])))
			{
				rv = FALSE;
				break;
			}
		}
		return rv;
	}