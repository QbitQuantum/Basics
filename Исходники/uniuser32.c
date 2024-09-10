/* MAKE_EXPORT DdeQueryStringW_new=DdeQueryStringW */
DWORD WINAPI DdeQueryStringW_new(DWORD idInst, HSZ hsz, LPWSTR pszW, DWORD cchMax, int iCodePage)
{
	ALLOC_WtoA(psz);

	return DdeQueryStringA(idInst, hsz, pszA, cchMax, iCodePage);
}