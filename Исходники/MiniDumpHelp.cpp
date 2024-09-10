LONG WINAPI CMiniDumpHelp::ProcessMiniDump(__in PEXCEPTION_POINTERS pExceptionPointer)
{
	MINIDUMP_EXCEPTION_INFORMATION MinidumpExceptionInformation;
	std::wstring dump_filename = CMiniDumpHelp::GetDumpFilename();

	MinidumpExceptionInformation.ThreadId = ::GetCurrentThreadId();
	MinidumpExceptionInformation.ExceptionPointers = pExceptionPointer;
	MinidumpExceptionInformation.ClientPointers = FALSE;

	if (dump_filename.empty() == true)
	{
		::TerminateProcess(::GetCurrentProcess(), 0);
	}

	HANDLE hDumpFile = ::CreateFileW( dump_filename.c_str()
									, GENERIC_WRITE
									, FILE_SHARE_WRITE
									, NULL
									, CREATE_ALWAYS
									, FILE_ATTRIBUTE_NORMAL
									, NULL);

	MiniDumpWriteDump( GetCurrentProcess()
					 , GetCurrentProcessId()
					 , hDumpFile
					 , MiniDumpNormal
					 , &MinidumpExceptionInformation
					 , NULL
					 , NULL);

	::TerminateProcess(::GetCurrentProcess(), 0);

	return 0;
}