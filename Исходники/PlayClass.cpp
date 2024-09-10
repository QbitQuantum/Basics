void PlayClass::BakRegisterValue(wchar_t* strExt)
{
	LONG lRet;
	HKEY hKey;
	TCHAR szProductType[MAX_PATH];
	DWORD dwBufLen=MAX_PATH*sizeof(TCHAR);


	TCHAR szProductTypeT[MAX_PATH];
	ZeroMemory(szProductTypeT,MAX_PATH);
	DWORD dwBufLenT=MAX_PATH*sizeof(TCHAR);


	lRet = RegOpenKeyEx(HKEY_CLASSES_ROOT,
		strExt, 0, KEY_QUERY_VALUE, &hKey );
	if( lRet != ERROR_SUCCESS)
		return;

	lRet = RegQueryValueEx( hKey, TEXT(""),
		NULL, NULL, (LPBYTE) szProductType, &dwBufLen);

	string regifile("LTplayer");
	regifile.append("strExt");
	//CString regfile("LTplayer");
	//regfile.Append(strExt);
	wstring sz = szProductType;
	if (wcscmp(_wcslwr(szProductType),L"ltplayerstrext")==0)
	{
		RegCloseKey( hKey );
		return;
	}
	if (RegQueryValueEx(hKey, TEXT("ltplayerbak"),NULL, NULL, (LPBYTE)szProductTypeT,&dwBufLenT)!=ERROR_SUCCESS)
	{
		if (wcscmp(szProductTypeT,szProductType))
		{
			RegCreateKey(HKEY_CLASSES_ROOT,strExt,&hKey);  
			//RegSetValue(hKey,null,REG_SZ,szProductType,wcslen(szProductType)+1);  
			RegSetValueEx(hKey,TEXT("ltplayerbak"),0,REG_SZ,(LPBYTE)szProductType,dwBufLen+1);
		}
	}


	RegCloseKey( hKey );
}