// Notify of a change in the specified registry key/hive
bool RegKey::NotifyChange(LPCTSTR pszKeyName, DWORD dwNotifyfilter, bool bWatchSubKeys /* = false */, HANDLE hEvent /* = NULL */, HKEY hBaseKey /* = HKEY_CURRENT_USER */)
{
	if (pszKeyName == NULL)
	{
		iLastErrorCode_ = ERROR_BAD_ARGUMENTS;
		return false;
	}

	if (!OpenKey(pszKeyName, false, hBaseKey, NULL))
		return false;

	LONG lRetValue = ERROR_SUCCESS;

	if (hEvent == NULL)
		lRetValue = RegNotifyChangeKeyValue(hTheKey_, bWatchSubKeys, dwNotifyfilter, hEvent, FALSE);
	else
		lRetValue = RegNotifyChangeKeyValue(hTheKey_, bWatchSubKeys, dwNotifyfilter, hEvent, TRUE);

	if (lRetValue == ERROR_CALL_NOT_IMPLEMENTED) // NT ONLY
	{
		iLastErrorCode_ = ERROR_CALL_NOT_IMPLEMENTED;
		return false;
	}

	if (lRetValue != ERROR_SUCCESS)
	{
		iLastErrorCode_ = GetLastError();
		return false;
	}

	iLastErrorCode_ = ERROR_SUCCESS;
	return true;
}