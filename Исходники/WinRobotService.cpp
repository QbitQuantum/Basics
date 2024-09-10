BOOL QuerySessionInformationT(DWORD SessionId,WTS_INFO_CLASS WTSInfoClass,T& t)
{
	DWORD buflen = 0;
	LPTSTR	pv = NULL;
	t = T();
	if(!WTSQuerySessionInformation(WTS_CURRENT_SERVER_HANDLE,SessionId,WTSInfoClass,&pv,&buflen))
	{
		return FALSE;
	}
	//if(sizeof(T) > buflen) return FALSE;
	t =  *(T*)pv;
	if(pv)WTSFreeMemory(pv);
	return TRUE;
}