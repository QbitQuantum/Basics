  // RegQueryValueExW替换
LONG APIENTRY Replace_RegQueryValueExW(HKEY hKey,LPCWSTR lpValueName,LPDWORD lpReserved,LPDWORD lpType,LPBYTE lpData,LPDWORD lpcbData)
{
	LONG nRet;
	__try
	{
		nRet = Real_RegQueryValueExW(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
		if(!HOOK_RegQueryValueEx)
			return nRet;
		if(GetCurrentProcessId() == ExplorerPID)
			return nRet;
		if(GetCurrentProcessId() == RegMonPID)
			return nRet;
		if((PID == 0) || ((GetCurrentProcessId() == PID) && (PID>0)) )
		{
			if(nRet != ERROR_SUCCESS)
				return nRet;

			COPYDATASTRUCT data;
			PARAMS params;
			memset(&params,0,sizeof(PARAMS));
			params.PID = GetCurrentProcessId();
			params.hKey = hKey;
			
			if(lpValueName == NULL || /*lpType == NULL ||*/ lpData == NULL || lpcbData == NULL)
				return nRet;
			
			memcpy(params.buf1, lpValueName, wcslen(lpValueName)*2);
			
			if(lpType == NULL)
				params.type = 0;
			else
				params.type = *lpType;
			
			if(*lpcbData == 0)
			{
				return nRet;
			}
			else if(*lpcbData>MAX_BUF_LEN )
			{
				memcpy(params.buf2, lpData, MAX_BUF_LEN );
				params.cbbuf2 = MAX_BUF_LEN ;
			}
			else
			{
				memcpy(params.buf2, lpData, *lpcbData);
				params.cbbuf2 = *lpcbData;
			}

			params.result = nRet;
			
			data.cbData = sizeof(PARAMS);
			data.lpData =(void *)&params;
			data.dwData = TYPE_RegQueryValueExW;
			SendMessage(g_hWnd, WM_COPYDATA, (WPARAM)g_hWnd, (LPARAM)&data);
		}
		
	}__finally
	{
	};
	return nRet;
}