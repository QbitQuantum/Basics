BOOL STDAPICALLTYPE wildcmp(LPCTSTR string, LPCTSTR wild ) 
{
	const TCHAR *cp, *mp;
	cp = mp = NULL;
	
	while ((*string) && (*wild != _T('*'))) 
	{
		if ((_toupper(*wild) != _toupper(*string)) && (*wild != _T('?'))) 
		{
			return FALSE;
		}
		wild++;
		string++;
	}
		
	while (*string) 
	{
		if (*wild == _T('*')) 
		{
			if (!*++wild) 
			{
				return TRUE;
			}
			mp = wild;
			cp = string+1;
		} 
		else 
		if ((_toupper(*wild) == _toupper(*string)) || (*wild == _T('?'))) 
		{
			wild++;
			string++;
		} 
		else 
		{
			wild = mp;
			string = cp++;
		}
	}
		
	while (*wild == _T('*')) 
	{
		wild++;
	}
	return (!*wild)? TRUE : FALSE;
}