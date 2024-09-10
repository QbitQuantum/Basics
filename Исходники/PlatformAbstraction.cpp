bool EraseItemSafe(const char *szFilename)
{
	char Filename[_MAX_PATH+1];
	SCopy(szFilename, Filename, _MAX_PATH);
	Filename[SLen(Filename)+1]=0;
	SHFILEOPSTRUCTW shs;
	shs.hwnd=0;
	shs.wFunc=FO_DELETE;
	shs.pFrom=GetWideChar(Filename);
	shs.pTo=NULL;
	shs.fFlags=FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_SILENT;
	shs.fAnyOperationsAborted=false;
	shs.hNameMappings=0;
	shs.lpszProgressTitle=NULL;
	return !SHFileOperationW(&shs);
}