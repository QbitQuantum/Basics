void SaveMediaInfo(struct MediaInfo *info)
{
	HKEY hKey;
	LONG lRet = RegCreateKey(HKEY_CURRENT_USER, REG_PATH, &hKey);
	if( lRet != ERROR_SUCCESS )
	{
		WriteLog("Faild(%d) to RegCreateKey\n", lRet);
		return ;
	}

	OLECHAR szCLSID[MAX_PATH];
	HRESULT hr = StringFromGUID2(info->m_Id, szCLSID, MAX_PATH);
	assert( SUCCEEDED(hr) );

	lRet = RegSetValueEx(hKey, szCLSID, 0L, REG_BINARY, (CONST BYTE *)info, REG_SIZE);
	if( lRet != ERROR_SUCCESS )
	{
		WriteLog("Faild(%d) to RegSetValueEx\n", lRet);
	}

	RegCloseKey(hKey);
}