void logThread(void *dummy)
{
	SetProcessPriorityBoost	(GetCurrentProcess(),TRUE);

	logWindow = CreateDialog(
		HINSTANCE(GetModuleHandle(0)),
	 	MAKEINTRESOURCE(IDD_LOG),
		0, logDlgProc );
	if (!logWindow) {
		R_CHK			(GetLastError());
	};
	SetWindowPos(logWindow,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);
	hwLog		= GetDlgItem(logWindow, IDC_LOG);
	hwProgress	= GetDlgItem(logWindow, IDC_PROGRESS);
	hwInfo		= GetDlgItem(logWindow, IDC_INFO);
	hwStage		= GetDlgItem(logWindow, IDC_STAGE);
	hwTime		= GetDlgItem(logWindow, IDC_TIMING);
	hwPText		= GetDlgItem(logWindow, IDC_P_TEXT);
	hwPhaseTime	= GetDlgItem(logWindow, IDC_PHASE_TIME);

	SendMessage(hwProgress, PBM_SETRANGE,	0, MAKELPARAM(0, 1000)); 
	SendMessage(hwProgress, PBM_SETPOS,		0, 0); 

	Msg("\"LevelBuilder v4.1\" beta build\nCompilation date: %s\n",__DATE__);
	{
		char tmpbuf[128];
		Msg("Startup time: %s",_strtime(tmpbuf));
	}

	BOOL		bHighPriority	= FALSE;
	string256	u_name;
	unsigned long		u_size	= sizeof(u_name)-1;
	GetUserName	(u_name,&u_size);
	_strlwr		(u_name);
	if ((0==xr_strcmp(u_name,"oles"))||(0==xr_strcmp(u_name,"alexmx")))	bHighPriority	= TRUE;

	// Main cycle
	u32		LogSize = 0;
	float	PrSave	= 0;
	while (TRUE)
	{
		SetPriorityClass	(GetCurrentProcess(),IDLE_PRIORITY_CLASS);	// bHighPriority?NORMAL_PRIORITY_CLASS:IDLE_PRIORITY_CLASS

		// transfer data
		while (!csLog.TryEnter())	{
			_process_messages	( );
			Sleep				(1);
		}
		if (progress>1.f)		progress = 1.f;
		else if (progress<0)	progress = 0;

		BOOL bWasChanges = FALSE;
		char tbuf		[256];
		csLog.Enter		();
		if (LogSize!=LogFile->size())
		{
			bWasChanges		= TRUE;
			for (; LogSize<LogFile->size(); LogSize++)
			{
				const char *S = *(*LogFile)[LogSize];
				if (0==S)	S = "";
				SendMessage	( hwLog, LB_ADDSTRING, 0, (LPARAM) S);
			}
			SendMessage		( hwLog, LB_SETTOPINDEX, LogSize-1, 0);
			//FlushLog		( );
		}
		csLog.Leave		();
		if (_abs(PrSave-progress)>EPS_L) {
			bWasChanges = TRUE;
			PrSave = progress;
			SendMessage		( hwProgress, PBM_SETPOS, u32(progress*1000.f), 0);

			// timing
			if (progress>0.005f) {
				u32 dwCurrentTime = timeGetTime();
				u32 dwTimeDiff	= dwCurrentTime-phase_start_time;
				u32 secElapsed	= dwTimeDiff/1000;
				u32 secRemain		= u32(float(secElapsed)/progress)-secElapsed;
				xr_sprintf(tbuf,
					"Elapsed: %s\n"
					"Remain:  %s",
					make_time(secElapsed).c_str(),
					make_time(secRemain).c_str()
					);
				SetWindowText	( hwTime, tbuf );
			} else {
				SetWindowText	( hwTime, "" );
			}

			// percentage text
			xr_sprintf(tbuf,"%3.2f%%",progress*100.f);
			SetWindowText	( hwPText, tbuf );
		}

		if (bStatusChange) {
			bWasChanges		= TRUE;
			bStatusChange	= FALSE;
			SetWindowText	( hwInfo,	status);
		}
		if (bWasChanges) {
			UpdateWindow	( logWindow);
			bWasChanges		= FALSE;
		}
		csLog.Leave			();

		_process_messages	();
		if (bClose)			break;
		Sleep				(200);
	}

	// Cleanup
	DestroyWindow(logWindow);
}