// Initialization code
AUX_DATA::AUX_DATA()
{
	// Cache various target platform version information
	DWORD dwVersion = ::GetVersion();
	nWinVer = (LOBYTE(dwVersion) << 8) + HIBYTE(dwVersion);
	bWin95 = (dwVersion & 0x80000000) != 0;
	bWin4 = (BYTE)dwVersion >= 4;
	bNotWin4 = 1 - bWin4;   // for convenience
	bSmCaption = bWin4;
	bMarked4 = FALSE;

	// determine various metrics based on EXE subsystem version mark
	if (bWin4)
		bMarked4 = (GetProcessVersion(0) >= 0x00040000);

	// Cached system metrics (updated in CWnd::OnWinIniChange)
	UpdateSysMetrics();

	// Cached system values (updated in CWnd::OnSysColorChange)
	hbrBtnFace = NULL;
	UpdateSysColors();

	// Standard cursors
	hcurWait = ::LoadCursor(NULL, IDC_WAIT);
	hcurArrow = ::LoadCursor(NULL, IDC_ARROW);
	ASSERT(hcurWait != NULL);
	ASSERT(hcurArrow != NULL);
	hcurHelp = NULL;    // loaded on demand

	// cxBorder2 and cyBorder are 2x borders for Win4
	cxBorder2 = bWin4 ? CX_BORDER*2 : CX_BORDER;
	cyBorder2 = bWin4 ? CY_BORDER*2 : CY_BORDER;

	// allocated on demand
	hbmMenuDot = NULL;
	hcurHelp = NULL;
}