int _tmain(int argc, _TCHAR* argv[])
{
	char bufOut[CMD_SIZE] = {0};
	TCHAR bufCmd[CMD_SIZE] = {0};
	TCHAR *intext = NULL;
	if(argc == 1)
		wcsncat_s(bufCmd, L"qrcode.exe -h", CMD_SIZE);
	else
		wcsncat_s(bufCmd, L"qrcode.exe", CMD_SIZE);

	int i;
	for(i = 1; i < argc; i++)
	{
		if(!IsOption(argv[i]))
			break;

		wcsncat_s(bufCmd, L" ", CMD_SIZE);
		wcsncat_s(bufCmd, argv[i], CMD_SIZE);
		if(IsOptionWithParameter(argv[i]) && (i + 1 < argc))
		{
			i++;
			wcsncat_s(bufCmd, L" ", CMD_SIZE);
			wcsncat_s(bufCmd, argv[i], CMD_SIZE);
		}
	}

	if(i < argc)
	{
		wcsncat_s(bufCmd, L" \"", CMD_SIZE);
		wcsncat_s(bufCmd, argv[i], CMD_SIZE);
		wcsncat_s(bufCmd, L"\"", CMD_SIZE);
	}
	else
	{
		intext = readStdin();
		wcsncat_s(bufCmd, L" \"", CMD_SIZE);
		wcsncat_s(bufCmd, intext, CMD_SIZE);
		wcsncat_s(bufCmd, L"\"", CMD_SIZE);
	}

	DWORD len = ::WideCharToMultiByte(CP_UTF8, 0, bufCmd, wcslen(bufCmd), bufOut, CMD_SIZE, NULL, NULL);

	STARTUPINFOA si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	// Start the child process. 
	if( !CreateProcessA( NULL,   // No module name (use command line)
						bufOut,        // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						TRUE,          // Set handle inheritance to FALSE
						0,
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi )           // Pointer to PROCESS_INFORMATION structure
	) 
	{
		return FALSE;
	}

	// Wait until child process exits.
	WaitForSingleObject( pi.hProcess, INFINITE );
	
	// Close process and thread handles. 
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );

	return 0;
}