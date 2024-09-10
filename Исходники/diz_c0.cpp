int WINAPI GetCustomDataW(const wchar_t *FilePath, wchar_t **CustomData)
{
	*CustomData = NULL;
	
	const wchar_t* pszSlash = wcsrchr(FilePath, L'\\');
	if (!pszSlash || pszSlash <= FilePath) return FALSE;
	if (pszSlash[1] == 0) return FALSE; // Если хотят диз именно для папки - то нужно без слеша
	string  strPath(FilePath, pszSlash-FilePath);
	
	// оптимизацией чтения диз-файла занимается сам diz
	if (diz.Read(strPath) == 0)
	{
		// Если диз пустой - сразу выходим
		return FALSE;
	}

	
	const wchar_t* pszDiz = diz.GetDizTextAddr(pszSlash+1, L"", 0/*???*/);
	//if (!pszDiz || pszDiz[0] == 0) -- ConvertNameToShort занимает очень много времени
	//{
	//	string strShort;
	//	ConvertNameToShort(FilePath, strShort);
	//	pszDiz = diz.GetDizTextAddr(pszSlash+1, strShort, 0/*???*/);
	//}
	if (!pszDiz || pszDiz[0] == 0)
	{
		return FALSE;
	}
	
	size_t nLen = wcslen(pszDiz)+1;
	*CustomData = (wchar_t*)malloc(nLen*2);
	wcscpy(*CustomData, pszDiz);
	// Заменить некоторые символы
	wchar_t* pszTab = wcspbrk(*CustomData, L"\t");
	while (pszTab)
	{
		*pszTab = L' ';
		pszTab = wcspbrk(pszTab+1, L"\t");
	}

	return TRUE;
}