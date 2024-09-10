void test(WCHAR *wFileName)
{
	WCHAR lpFileName[MAX_PATH];
	WCHAR lpString[MAX_PATH];

	swprintf_s(lpFileName, MAX_PATH - 1, L"%s:Zone.Identifier", wFileName);
	swprintf_s(lpString, MAX_PATH - 1, L"%d", URLZONE_INTERNET);
	WritePrivateProfileStringW(L"ZoneTransfer", L"ZoneId", lpString, lpFileName);
}