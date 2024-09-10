ULONG
RspInitialize(
	IN PWSTR StoragePath	
	)
{
	ULONG Status;
	ULONG Length;
	SYSTEMTIME Time;
	WCHAR Buffer[MAX_PATH];

	Status = S_OK;
	RtlZeroMemory(&RspStorage, sizeof(RSP_STORAGE));
	RtlZeroMemory(&RspIndex, sizeof(RSP_INDEX));
	RtlZeroMemory(&RspView, sizeof(RSP_VIEW));

	InitializeListHead(&RspRecordList);
	InitializeListHead(&RspCallbackList);
	InitializeListHead(&RspProbeGroupList);
	InitializeListHead(&RspAddOnGroupList);

	RspHostThreadId = GetCurrentThreadId();
	
	if (WorkMode == CaptureMode) {

		PspGetFilePath(RspStoragePath, MAX_PATH - 1);
		StringCchCat(RspStoragePath, MAX_PATH - 1, L"\\log");

		if (CreateDirectory(RspStoragePath, NULL) != TRUE) {
			if (GetLastError() != ERROR_ALREADY_EXISTS) {
				return S_FALSE;
			}															
		}

		StringCchCopy(Buffer, MAX_PATH, RspStoragePath);
		Length = (ULONG)wcsnlen_s(Buffer, MAX_PATH);

		GetLocalTime(&Time);
		StringCchPrintf(Buffer + Length, MAX_PATH - Length, L"\\dprobe-%02d%02d%02d%02d%02d.dtl", 
						Time.wMonth, Time.wDay, Time.wHour, Time.wMinute, Time.wSecond);

		Status = RspCreateCache(Buffer);
		SspInitialize();

	} else {

		Status = RspLoadCache(StoragePath);
		SspInitialize();
		SspLoadStackTraceDatabase();
	}

	return Status;
}