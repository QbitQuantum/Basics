VOID
MspWriteLogEntry(
	IN ULONG ProcessId,
	IN MSP_LOG_LEVEL Level,
	IN PSTR Format,
	...
	)
{
	ULONG IsLogging;
	va_list Argument;
	PMSP_LOG_ENTRY Entry;
	CHAR Buffer[MSP_LOG_TEXT_LIMIT];

	IsLogging = InterlockedCompareExchange(&MspLogObject.Flag, 0, 0);
	if (!IsLogging) {
		return;
	}

	va_start(Argument, Format);
	StringCchVPrintfA(Buffer, MAX_PATH, Format, Argument);
	va_end(Argument);

	Entry = (PMSP_LOG_ENTRY)MspMalloc(sizeof(MSP_LOG_ENTRY));
	Entry->ProcessId = ProcessId;

	GetLocalTime(&Entry->TimeStamp);
	StringCchCopyA(Entry->Text, MSP_LOG_TEXT_LIMIT, Buffer);

	EnterCriticalSection(&MspLogObject.Lock);
	InsertTailList(&MspLogObject.ListHead, &Entry->ListEntry);
	MspLogObject.ListDepth += 1;
	LeaveCriticalSection(&MspLogObject.Lock);

	return;
}