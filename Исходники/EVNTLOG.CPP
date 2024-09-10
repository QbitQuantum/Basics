BOOL COXEventLog::DeleteApplicationLog(LPCTSTR pszApplicationName)
{
	ASSERT_VALID(this);
	ASSERT(pszApplicationName != NULL);

	if (pszApplicationName == NULL || 
		lstrlen(pszApplicationName) <= 0)
	{
		m_ErrorCode = ERROR_INVALID_PARAMETER;
		return(FALSE);
	}

	COXRegistryItem regItem;
	CString log_key_name(_T("\\LocalMachine\\SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"));
	log_key_name += pszApplicationName;
	log_key_name += _T("\\");
	regItem.SetFullRegistryItem(log_key_name);
	if (regItem.Delete() == FALSE)
	{
		m_ErrorCode = regItem.GetLastError();
		return FALSE;
	}

	/*
	** Microsoft has a bug in this area. Even though we deleted the application from the
	** HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\
	** registry area, they don't provide a way to delete the application from the 
	** HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\Sources
	** value. The application name is one of the strings in this REG_MULTI_SZ value. We
	** still need to delete it from there. The names listed in this value appear in the 
	** "Source" combobox of the Event Viewer application View->Filter Events... menu selection.
	*/

	log_key_name = _T("\\LocalMachine\\SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\");
	regItem.SetFullRegistryItem(log_key_name);
	CStringArray sources;
	if (regItem.Open(FALSE) == FALSE ||
		regItem.GetMultiStringValue(sources, _T("Sources")) == FALSE)
	{
		m_ErrorCode = regItem.GetLastError();
		return FALSE;
	}
	
	int index = 0;
	int number_of_sources = PtrToInt(sources.GetSize());
	BOOL application_was_found = FALSE;
	while(index < number_of_sources)
	{
		if (sources[index] == pszApplicationName)
		{
			application_was_found = TRUE;
			sources.RemoveAt(index);
			index = number_of_sources;
		}

		index++;
	}
	if (application_was_found != FALSE)
	{
		regItem.SetMultiStringValue(sources, _T("Sources"));
	}

	return TRUE;
}