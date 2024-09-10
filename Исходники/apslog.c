VOID
ApsWriteLogEntry(
	__in ULONG ProcessId,
	__in APS_LOG_LEVEL Level,
	__in PSTR Format,
	...
	)
{
	ULONG IsLogging;
	va_list Argument;
	PAPS_LOG_ENTRY Entry;
	CHAR Buffer[APS_LOG_TEXT_LIMIT];

	//
	// Check whether logging's enabled
	//

	IsLogging = InterlockedCompareExchange(&ApsLogObject.Flag, 0, 0);
	if (!IsLogging) {
		return;
	}

	va_start(Argument, Format);
	StringCchVPrintfA(Buffer, MAX_PATH, Format, Argument);
	va_end(Argument);

	Entry = (PAPS_LOG_ENTRY)ApsMalloc(sizeof(APS_LOG_ENTRY));
	Entry->ProcessId = ProcessId;
	Entry->Level = Level;

	GetLocalTime(&Entry->TimeStamp);
	StringCchCopyA(Entry->Text, APS_LOG_TEXT_LIMIT, Buffer);

	//
	// Queue record entry to logging queue, note that this routine can be
	// called concurrently, so logging object's lock must be acquired to
	// protect the log record queue
	//

	EnterCriticalSection(&ApsLogObject.Lock);
	InsertTailList(&ApsLogObject.ListHead, &Entry->ListEntry);
	ApsLogObject.ListDepth += 1;
	LeaveCriticalSection(&ApsLogObject.Lock);

	return;
}