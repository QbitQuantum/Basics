// Get the record number to the last record in the log file.
static DWORD GetLastRecordNumber(HANDLE hEventLog, DWORD* pdwRecordNumber)
{
	DWORD status = ERROR_SUCCESS;
	DWORD OldestRecordNumber = 0;
	DWORD NumberOfRecords = 0;

	if (!GetOldestEventLogRecord(hEventLog, &OldestRecordNumber))
	{
		wprintf(L"GetOldestEventLogRecord failed with %lu.\n", status = GetLastError());
		goto cleanup;
	}

	if (!GetNumberOfEventLogRecords(hEventLog, &NumberOfRecords))
	{
		wprintf(L"GetOldestEventLogRecord failed with %lu.\n", status = GetLastError());
		goto cleanup;
	}

	*pdwRecordNumber = OldestRecordNumber + NumberOfRecords - 1;

cleanup:

	return status;
}