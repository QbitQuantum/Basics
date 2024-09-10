static void RegisterExt(LPCTSTR lpszExt, LPCTSTR lpszProgID, UINT nIDTypeName,
	LPCTSTR* rglpszSymbols, LPCTSTR* rglpszExtRegister,
	LPCTSTR* rglpszRegister, int nIcon)
{
	// don't overwrite anything with the extensions
	CString strWhole;
	VERIFY(strWhole.LoadString(nIDTypeName));
	CString str;
	AfxExtractSubString(str, strWhole, DOCTYPE_PROGID);

	rglpszSymbols[1] = lpszProgID;
	rglpszSymbols[4] = str;
	rglpszSymbols[6] = lpszExt;
	TCHAR buf[10];
	wsprintf(buf, _T("%d"), nIcon);
	rglpszSymbols[7] = buf;
	// check for .ext and progid
	CKey key;
	if (!key.Open(HKEY_CLASSES_ROOT, lpszExt)) // .ext doesn't exist
		RegisterHelper(rglpszExtRegister, rglpszSymbols, TRUE);
	key.Close();
	if (!key.Open(HKEY_CLASSES_ROOT, lpszProgID)) // ProgID doesn't exist (i.e. txtfile)
		RegisterHelper(rglpszRegister, rglpszSymbols, TRUE);
}