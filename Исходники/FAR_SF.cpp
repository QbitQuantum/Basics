FarString PasteFromClipboard()
{
	OSVERSIONINFO WinVer;
	WinVer.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	GetVersionEx (&WinVer);

	HANDLE hClipData;
	if (!OpenClipboard(NULL))
		return(NULL);
	int Unicode=FALSE;
	int Format=0;
	int ReadType=CF_OEMTEXT;
	while ((Format=EnumClipboardFormats(Format))!=0)
	{
		if (Format==CF_UNICODETEXT && WinVer.dwPlatformId==VER_PLATFORM_WIN32_NT)
		{
			Unicode=TRUE;
			break;
		}
		if (Format==CF_TEXT)
		{
			ReadType=CF_TEXT;
			break;
		}
		if (Format==CF_OEMTEXT)
			break;
	}
	FarString ClipText;
	if ((hClipData=GetClipboardData(Unicode ? CF_UNICODETEXT:ReadType))!=NULL)
	{
		int BufferSize;
		char *ClipAddr=(char *)GlobalLock(hClipData);
		if (Unicode)
			BufferSize=lstrlenW((LPCWSTR)ClipAddr)+1;
		else
			BufferSize=strlen(ClipAddr)+1;

		if (Unicode)
		{
			ClipText.SetLength (BufferSize);
			WideCharToMultiByte(CP_OEMCP,0,(LPCWSTR)ClipAddr,-1,ClipText.GetBuffer(),BufferSize,NULL,FALSE);
		}
		else
		{
			ClipText.SetText (ClipAddr, BufferSize);
			if (ReadType==CF_TEXT)
				ClipText = ClipText.ToOEM();
		}
		GlobalUnlock(hClipData);
	}
	CloseClipboard();
	return ClipText;
}