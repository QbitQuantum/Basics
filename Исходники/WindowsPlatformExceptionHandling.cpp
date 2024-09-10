/**
 * Add a minidump to the Windows Error Report
 *
 * Note this has to be a minidump (and not a microdump) for the dbgeng functions to work correctly
 */
static void AddMiniDump( HREPORT ReportHandle, EXCEPTION_POINTERS* ExceptionInfo )
{
#if 0
	// This doesn't work in x64
	WER_EXCEPTION_INFORMATION WerExceptionInfo = { ExceptionInfo, FALSE };
	Result = WerReportAddDump( ReportHandle, GetCurrentProcess(), GetCurrentThread(), WerDumpTypeMiniDump, &WerExceptionInfo, NULL, 0 );
#else
	FString MinidumpFileName = FString::Printf( TEXT( "%sDump%d.dmp" ), *FPaths::GameLogDir(), FDateTime::UtcNow().GetTicks() );
	HANDLE DumpHandle = CreateFileW( *MinidumpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if( DumpHandle != INVALID_HANDLE_VALUE )
	{
		MINIDUMP_EXCEPTION_INFORMATION DumpExceptionInfo = { 0 };
		DumpExceptionInfo.ThreadId = GetCurrentThreadId();
		DumpExceptionInfo.ExceptionPointers = ExceptionInfo;
		DumpExceptionInfo.ClientPointers = true;

		MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), DumpHandle, MiniDumpNormal, &DumpExceptionInfo, NULL, NULL );
		CloseHandle( DumpHandle );

		WerReportAddFile( ReportHandle, *MinidumpFileName, WerFileTypeMinidump, WER_FILE_ANONYMOUS_DATA ); 
	}
#endif
}