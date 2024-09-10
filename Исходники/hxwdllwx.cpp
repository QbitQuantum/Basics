LONG WINAPI myImmGetCompositionStringW(HIMC hIMC, DWORD dwIndex, LPVOID lpBuf, DWORD dwBufLen)
{
	LONG myReturn=0;
	LONG tempLen=0;
	int StrBufLen=0;
	if (dwIndex==GCS_RESULTSTR && g_HOOKflag)
	{
		memset(g_IMEString,0,256);
		tempLen=254;
		g_myHOOK2.HookStatus(false);
		ImmGetCompositionStringW(hIMC,GCS_RESULTSTR,g_IMEString,tempLen);
		g_myHOOK2.HookStatus(true);
		g_IMEString[254]=0;
		g_IMEString[255]=0;
		if (lstrcmpW((wchar_t *)g_IMEString,(wchar_t *)g_StringBuf1)!=0)
		{
			memset(g_StringBuf1,0,256);
			lstrcpyW((wchar_t *)g_StringBuf1,(wchar_t *)g_IMEString);
			WCharToMByte((wchar_t *)g_StringBuf1,g_IMEString,256);
			SendMessage(g_hMainhWnd,WM_HXWDLLWX_QQBTX,0,0);
			memset(g_StringBuf2,0,256);
			MByteToWChar(g_IMEString,(wchar_t *)g_StringBuf2,128);
		}
		if (lpBuf==NULL || dwBufLen==0)
		{
			myReturn=lstrlenW((wchar_t *)g_StringBuf2)*2;
		}
		else
		{
			StrBufLen=lstrlenW((wchar_t *)g_StringBuf2)*2;
			memset(lpBuf,0,dwBufLen);
			if (dwBufLen>=StrBufLen) 
			{
				dwBufLen=StrBufLen;
				myReturn=StrBufLen;
			}
			else
			{
				myReturn=0;
			}
			memcpy(lpBuf,g_StringBuf2,dwBufLen);
		}
	}
	else
	{
		g_myHOOK2.HookStatus(false);
		myReturn=ImmGetCompositionStringW(hIMC,dwIndex,lpBuf,dwBufLen);
		g_myHOOK2.HookStatus(true);
	}
	return myReturn;
}