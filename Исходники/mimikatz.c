int wmain(int argc, wchar_t * argv[])
{
	int i, status = STATUS_SUCCESS;
#ifndef _WINDLL
	wchar_t input[0xff];
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stderr), _O_U8TEXT);
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleTitle(MIMIKATZ L" " MIMIKATZ_VERSION L" " MIMIKATZ_ARCH);
	SetConsoleCtrlHandler(HandlerRoutine, TRUE);
#endif
	kprintf(L"\n"
		L"  .#####.   " MIMIKATZ_FULL L"\n"
		L" .## ^ ##.  \n"
		L" ## / \\ ##  /* * *\n"
		L" ## \\ / ##   Benjamin DELPY `gentilkiwi` ( [email protected] )\n"
		L" '## v ##'   http://blog.gentilkiwi.com/mimikatz             (oe.eo)\n"
		L"  '#####'                                    with %3u modules * * */\n\n", sizeof(mimikatz_modules) / sizeof(KUHL_M *));
	
	mimikatz_initOrClean(TRUE);
	for(i = MIMIKATZ_AUTO_COMMAND_START ; (i < argc) && (status != STATUS_FATAL_APP_EXIT) ; i++)
	{
		kprintf(L"\n" MIMIKATZ L"(" MIMIKATZ_AUTO_COMMAND_STRING L") # %s\n", argv[i]);
		status = mimikatz_dispatchCommand(argv[i]);
	}
#ifndef _WINDLL
	while (status != STATUS_FATAL_APP_EXIT)
	{
		kprintf(L"\n" MIMIKATZ L" # "); fflush(stdin);
		if(wscanf_s(L"%[^\n]s", input, sizeof(input)) == 1)
		{
			kprintf_inputline(L"%s\n", input);
			status = mimikatz_dispatchCommand(input);
		}
	}
#endif
	mimikatz_initOrClean(FALSE);
	return STATUS_SUCCESS;
}