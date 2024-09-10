int change_file_date(char *fname,unsigned long dosdate)
{
	HANDLE hfile;
	hfile=CreateFile(fname,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if(hfile!=INVALID_HANDLE_VALUE){
		FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;
		GetFileTime(hfile,&ftCreate,&ftLastAcc,&ftLastWrite);
		DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
		LocalFileTimeToFileTime(&ftLocal,&ftm);
		SetFileTime(hfile,&ftm,&ftLastAcc,&ftm);
		CloseHandle(hfile);
		return TRUE;
	}