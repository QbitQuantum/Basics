FLT_PREOP_CALLBACK_STATUS
NPPreCreate (
    __inout PFLT_CALLBACK_DATA Data,
    __in PCFLT_RELATED_OBJECTS FltObjects,
    __deref_out_opt PVOID *CompletionContext
    )
{
    NTSTATUS status;
    PFLT_FILE_NAME_INFORMATION nameInfo;
    ANSI_STRING ansiStr;

    UNREFERENCED_PARAMETER( FltObjects );
    UNREFERENCED_PARAMETER( CompletionContext );
    PAGED_CODE();

    __try
    {
        status = FltGetFileNameInformation( Data,
                                            FLT_FILE_NAME_NORMALIZED |
                                            FLT_FILE_NAME_QUERY_DEFAULT,
                                            &nameInfo );
        if ( !NT_SUCCESS( status ) )
            leave;

        status = FltParseFileNameInformation( nameInfo );
        if ( !NT_SUCCESS( status ) )
            leave;
        RtlUnicodeStringToAnsiString(&ansiStr, &nameInfo->Name, TRUE);
        PT_DBG_PRINT( PTDBG_TRACE_OPERATION_STATUS,
                     ("minifilter0!NPPretCreate: create [%Z]\n", &ansiStr) );
        RtlFreeAnsiString( &ansiStr );
		FltReleaseFileNameInformation( nameInfo );
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        DbgPrint("NPPreCreate EXCEPTION_EXECUTE_HANDLER\n");
    }
    return FLT_PREOP_SUCCESS_WITH_CALLBACK;
}