// pKey нужен для того чтобы выбрать имя значения, в котором будут храниться линки
void RegConfig::BookmarksGet(RegPath* pKey, BOOL bRemote, TCHAR** ppszBookmarks, DWORD* pnBookmarksCount)
{
	if (bUseInternalBookmarks)
		BookmarksLoadInt(pKey, bRemote);
	else
		BookmarksLoadExt(pKey, bRemote);

	if (ppszBookmarks)
	{
		if (!cchBookmarksLen || !pszBookmarks)
		{
			*ppszBookmarks = (TCHAR*)calloc(2,sizeof(TCHAR));
			if (pnBookmarksCount) *pnBookmarksCount = 0;
		}
		else
		{
			_ASSERTE(pszBookmarks);
			*ppszBookmarks = (TCHAR*)calloc(cchBookmarksLen,sizeof(TCHAR));
			#ifdef _UNICODE
			wmemmove(*ppszBookmarks, pszBookmarks, cchBookmarksLen);
			#else
			WideCharToMultiByte(nAnsiCodePage, 0, pszBookmarks, cchBookmarksLen, *ppszBookmarks, cchBookmarksLen, 0,0);
			#endif
			if (pnBookmarksCount)
				BookmarksLen(pnBookmarksCount);
		}
	}
}