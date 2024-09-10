NTSTATUS kuhl_m_event_clear(int argc, wchar_t * argv[])
{
	HANDLE hEventLog;
	PCWCHAR szLog;
	DWORD nbEvents;
	kull_m_string_args_byName(argc, argv, L"log", &szLog, L"Security");

	kprintf(L"Using \"%s\" event log :\n", szLog);
	if(hEventLog = OpenEventLog(NULL, szLog))
	{
		if(GetNumberOfEventLogRecords(hEventLog, &nbEvents))
			kprintf(L"- %u event(s)\n", nbEvents);
		if(ClearEventLog(hEventLog, NULL))
			kprintf(L"- Cleared !\n");
		else PRINT_ERROR_AUTO(L"ClearEventLog");
		if(GetNumberOfEventLogRecords(hEventLog, &nbEvents))
			kprintf(L"- %u event(s)\n", nbEvents);
	}
	else PRINT_ERROR_AUTO(L"OpenEventLog");

	return STATUS_SUCCESS;
}