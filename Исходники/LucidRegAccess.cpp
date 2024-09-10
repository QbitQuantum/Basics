void setLucidRegValue(const CString csSectionPath, const CString csKey, CString csValue)
{
	HKEY myKey;
	DWORD varType = REG_SZ; //the value's a REG_SZ type
	DWORD buffSize = 1024;
	DWORD dwDisp;

	char pBuf[1024] = {'\0'};
	const int nLen = csValue.GetLength();
	strcpy(pBuf, csValue.GetBuffer(nLen));

	// if the Section Path doesn't exist then create it
	if (RegOpenKeyEx(HKEY_CURRENT_USER,csSectionPath, 0, KEY_WRITE, &myKey)) {
		RegCreateKeyEx(HKEY_CURRENT_USER, csSectionPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &myKey, &dwDisp);
	}
	RegSetValueExA(myKey,csKey,0,varType,(const BYTE *)pBuf,sizeof(pBuf));
	RegCloseKey(myKey);
	csValue.ReleaseBuffer();
}