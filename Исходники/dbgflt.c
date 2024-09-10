ULONG __cdecl
DbgPrintEntry(
    __in PCHAR Format,
	...
	)
{
	PDBG_OUTPUTA Filter;
	PBTR_FILTER_RECORD Record;
	BTR_PROBE_CONTEXT Context;
	DBGPRINT Routine;
	size_t Length;
	ULONG UserLength;
	va_list arg;
	PULONG_PTR Sp;
	ULONG Result;
	char format[512];
	char buffer[512];
	
	BtrFltGetContext(&Context);
	Routine = Context.Destine;

	//
	// N.B. Maximum support 16 arguments
	//

	Sp = (PULONG_PTR)&Format + 1;
	Result = (*Routine)(Format, Sp[0], Sp[1], Sp[2], Sp[3], Sp[4],
			   Sp[5], Sp[6], Sp[7], Sp[8], Sp[9], 
			   Sp[10], Sp[11], Sp[12], Sp[13], Sp[14]);

	BtrFltSetContext(&Context);

	__try {

		va_start(arg, Format);
		StringCchVPrintfA(format, 512, Format, arg);
		StringCchPrintfA(buffer, 512, "%s", format);
		Length = strlen(buffer) + 1;
		va_end(arg);

		UserLength = FIELD_OFFSET(DBG_OUTPUTA, Text[Length]);
		Record = BtrFltAllocateRecord(UserLength, DbgUuid, _DbgPrint);
		if (!Record) {
			return Result;
		}

		Filter = FILTER_RECORD_POINTER(Record, DBG_OUTPUTA);
		Filter->Length = Length;
		StringCchCopyA(Filter->Text, Length, buffer);

		BtrFltQueueRecord(Record);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		if (Record) {
			BtrFltFreeRecord(Record);
		}		
	}

	return Result;
}