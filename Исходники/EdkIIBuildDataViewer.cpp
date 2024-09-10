///////////////////////////////////////////////////////////////////////////////
// ProcessCommandLine
//
// In non-dialog based app, this function would be in CWinApp module, and
// would be called from InitInstance() like this:
//          ProcessCommandLine(__argc, __argv);
//
BOOL CEDKIIBuildDataViewerApp::ProcessCommandLine(int argc, TCHAR *argv[])
{
#if OUTPUT_USAGE_TO_CONSOLE > 0
	FILE	*fh_stdout = NULL;
	BOOL	bDialog = (AfxGetMainWnd() != NULL);
	if (!bDialog) {
		AttachConsole(ATTACH_PARENT_PROCESS);
		int		hCrt = _open_osfhandle((intptr_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
		if (hCrt != -1) {
			fh_stdout = _fdopen(hCrt, "w");
			FILE	*stdoutOld = stdout;
			*stdout = *fh_stdout;
			int		i = setvbuf(stdout, NULL, _IONBF, 0);
		}
	}
#endif

	CString		errorStr;

	// In the following loop you would set/unset any global command 
	// line flags and option arguments (usually in the CWinApp object) 
	// as each option was found in the command line.  
	//
	// In general it is probably best to let ProcessCommandLine's caller
	// sort out the command line arguments that were used, and whether 
	// they are consistent.  In ProcessCommandLine, you want to save the
	// options and the arguments, doing any conversion (atoi, etc.) that
	// is necessary.
	//
	// Normally you would have a case statement for each option letter.

	int c;
	while ((c = getopt(argc, argv, _T("l:s:dih"))) != EOF)
	{
		switch (c)
		{
			case _T('l'):
				{
					FILE	*fp;
					_tfopen_s(&fp, optarg, _T("rt"));
					if (fp == NULL) {
#if OUTPUT_USAGE_TO_CONSOLE == 0
						CString msg;
						msg.Format(_T("ERROR: build log %s couldn't be opened for read\n"), optarg);
						AfxMessageBox(msg, MB_ICONERROR);
#else
						wprintf(_T("\n\nERROR: build log %s couldn't be opened for read\n"), optarg);
#endif
						return FALSE;
					}

					fclose(fp);
					m_commandLineData.buildLog = optarg;
				}
				break;

			case _T('s'):
				{
					FILE	*fp;
					_tfopen_s(&fp, optarg, _T("wt"));
					if (fp == NULL) {
#if OUTPUT_USAGE_TO_CONSOLE == 0
						CString msg;
						msg.Format(_T("ERROR: source list file %s couldn't be opened for write\n"), optarg);
						AfxMessageBox(msg, MB_ICONERROR);
#else
						wprintf(_T("\n\nERROR: source list file %s couldn't be opened for write\n"), optarg);
#endif
						return FALSE;
					}

					fclose(fp);
					m_commandLineData.sourceFileList = optarg;
				}
				break;

			case _T('d'):
				m_commandLineData.bSourceUseDoxygenFormat = TRUE;
				break;

			case _T('i'):
				m_commandLineData.bSourceIncludeInf = TRUE;
				break;

			case _T('?'):
#if OUTPUT_USAGE_TO_CONSOLE == 0
				errorStr.Format(_T("ERROR: illegal option %s\n\n"), argv[optind-1]);
#else
				errorStr.Format(_T("\n\nERROR: illegal option %s\n\n"), argv[optind-1]);
#endif

			case _T('h'):
#if OUTPUT_USAGE_TO_CONSOLE == 0
				// output help to dialog
				{
					CString str;
					str.Format(_T("%s"), m_pszExeName);
					CString msg;
					if (!errorStr.IsEmpty())
						msg = errorStr;
					msg += _T("Usage: ") + str + _T(" -l buildLog [-s] sourceFileList [-d] [-i]\n");
					msg += _T("-l buildLog\tfilename for BIOS build log to open\n");
					msg += _T("-s sourceFileList\tfilename for source list file to create\n");
					msg += _T("-d\t\tsource list file, use doxygen format\n");
					msg += _T("-i\t\tsource list file, include INF files\n");
					msg += _T("\nApp errorlevel is 0 for ERROR, or 1 for SUCCESS\n");
					if (!errorStr.IsEmpty())
						AfxMessageBox(msg, MB_ICONERROR);
					else
						AfxMessageBox(msg, MB_ICONINFORMATION);
				}
#else
				// output help to console
				{
					if (!errorStr.IsEmpty())
						wprintf(_T("%s"), errorStr.GetBuffer());
					wprintf(_T("Usage: %s -l buildLog [-s] sourceFileList [-d] [-i]\n"), m_pszExeName);
					wprintf(_T("-l buildLog        filename for BIOS build log to open\n"));
					wprintf(_T("-s sourceFileList  filename for source list file to create\n"));
					wprintf(_T("-d                 source list file, use doxygen format\n"));
					wprintf(_T("-i                 source list file, include INF files\n"));
					wprintf(_T("\nApp errorlevel is 0 for ERROR, or 1 for SUCCESS\n"));
				}
#endif
				return FALSE;
				break;
				
			default:
				break;
		}
	}

	// ensure all necessary command line parameters have been specified
	if (argc > 1 && (m_commandLineData.buildLog.IsEmpty() || m_commandLineData.sourceFileList.IsEmpty())) {
#if OUTPUT_USAGE_TO_CONSOLE == 0
		AfxMessageBox(_T("ERROR: must specify build log and source list filenames"), MB_ICONERROR);
#else
		wprintf(_T("\n\nERROR: must specify build log and source list filenames\n"));
#endif
		m_commandLineData.bCommandLineActive = FALSE;
		return FALSE;
	}
	// if command line parameters have been specified, then set flag to TRUE
	if (argc > 1)
		m_commandLineData.bCommandLineActive = TRUE;

#if OUTPUT_USAGE_TO_CONSOLE > 0
	if (fh_stdout != NULL) {
		fclose(fh_stdout);
		FreeConsole();
	}
#endif

	// all options processed, return success
	return TRUE;
}