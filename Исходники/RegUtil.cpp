HKEY RegUtil::startMonitoring(tstring regkey_name, tstring dword_name, HKEY hBase, HANDLE hEvent, BOOL bWatchSubtree, DWORD dwNotifyFilter, BOOL bAsynchronous)
{
	// the purpose of this function is to setup notifcation via a semaphore when a registry key has 
	// been modified 
	// its original purpose was to let us change the logging levels without having to poll the registry keys
	bool bResult=false;
	HKEY hKey=NULL;
	LONG  lResult=0L;

	REGSAM samDesired;
	samDesired = KEY_NOTIFY;

	// this is a bit odd but bear with me
	// we try to open the key normally - this normally will vary depending on if we are a win32 or win64 bit program
	// if we can open it we are happy - otherwise we try it explicitly as win64 and win32
	// this is the part of the key we can always count on - if we are installed

	lResult= RegOpenKeyEx(hBase,
							_T("SOFTWARE\\OPSWAT\\URL Filtering Agent"),
							0,
							samDesired,
							&hKey);

	if (lResult==ERROR_SUCCESS)
	{
		lResult = RegNotifyChangeKeyValue(
			hKey, // since this does not seem to work with keys from the 64bit hive I suspect we are seeing an issue caused by reflection issues
			TRUE,
			REG_NOTIFY_CHANGE_NAME|REG_NOTIFY_CHANGE_ATTRIBUTES|REG_NOTIFY_CHANGE_LAST_SET|REG_NOTIFY_CHANGE_SECURITY,
			hEvent,
			bAsynchronous
			);
		if (lResult==ERROR_SUCCESS)
		{
			bResult = true;
		}
	}
	return hKey;
}