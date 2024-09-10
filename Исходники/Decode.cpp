void SplitTag(const char* filename, wchar_t** title, wchar_t** artist)
{
	wchar_t* name = GetFileName(filename);
	if (name == NULL)
		return;

	wchar_t* p = name + wcslen(name);	
	while (p > name)
	{
		if (*p == '.')
		{
			wmemset(p, 0, 1);
			break;
		}
		else
			p--;
	}
	
	wchar_t* t = NULL;
	wchar_t* a = NULL;	
	Split(name, L"-", &t, &a);
	SAFE_DELETE_ARRAY(name);
	DWORD length = 0;
	
	if (a != NULL)
	{
		length = wcslen(a);
		*artist = new wchar_t[length + 1];
		wmemset(*artist, 0, length + 1);
		StrNCat(*artist, a, length + 1);
		SAFE_DELETE_ARRAY(a);
	}

	if (t != NULL)
	{
		SplitTitle(t, title);
		SAFE_DELETE_ARRAY(t);
	}
}