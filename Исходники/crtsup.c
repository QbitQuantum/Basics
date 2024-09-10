//
//	Compare string with wildcast ignore case.
//
int __cdecl __wcswicmp(const WCHAR *wild, const WCHAR *string) 
{
	const WCHAR *cp = NULL, *mp = NULL;
	
	while ((*string) && (*wild != '*')) 
	{
		if ((__ascii_towlower(*wild) != __ascii_towlower(*string)) && (*wild != '?')) 
			return 0;
		wild++;
		string++;
	}
	
	while (*string) 
	{
		if (*wild == '*') 
		{
			if (!*++wild) 
				return 1;
			mp = wild;
			cp = string+1;
		} 
		else if ((__ascii_towlower(*wild) == __ascii_towlower(*string)) || (*wild == '?')) 
		{
			wild++;
//			cp = string+1;	// '*' requires any symbol (*a != a)
			cp = string;	// '*' doesn't require a symbol (*a == a)
		} 
		else 
		{
			wild = mp;
			string = cp++;
		}
	}	// while (*string) 
	
	while (*wild == '*')
		wild++;

  return !*wild;
}