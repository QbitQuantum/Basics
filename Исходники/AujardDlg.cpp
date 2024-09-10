BOOL CAujardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//----------------------------------------------------------------------
	//	Logfile initialize
	//----------------------------------------------------------------------
	CTime time=CTime::GetCurrentTime();
	char strLogFile[50];
	sprintf_s(strLogFile, sizeof(strLogFile), "AujardLog-%d-%d-%d.txt", time.GetYear(), time.GetMonth(), time.GetDay());
	m_LogFile.Open( strLogFile, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate | CFile::shareDenyNone );
	m_LogFile.SeekToEnd();

	m_iLogFileDay = time.GetDay();

	if (!m_LoggerRecvQueue.InitailizeMMF(MAX_PKTSIZE, MAX_COUNT, SMQ_LOGGERSEND, FALSE)
		|| !m_LoggerSendQueue.InitailizeMMF(MAX_PKTSIZE, MAX_COUNT, SMQ_LOGGERRECV, FALSE)
		|| !InitializeMMF())
	{
		AfxMessageBox("Unable to initialize shared memory. Ensure Ebenezer is running.");
		AfxPostQuitMessage(0);
		return FALSE;
	}

	CIni ini("Aujard.ini");

	ini.GetString("ODBC", "ACCOUNT_DSN", "KN_online", m_strAccountDSN, sizeof(m_strAccountDSN));
	ini.GetString("ODBC", "ACCOUNT_UID", "knight", m_strAccountUID, sizeof(m_strAccountUID));
	ini.GetString("ODBC", "ACCOUNT_PWD", "knight", m_strAccountPWD, sizeof(m_strAccountPWD));
	ini.GetString("ODBC", "GAME_DSN", "KN_online", m_strGameDSN, sizeof(m_strGameDSN));
	ini.GetString("ODBC", "GAME_UID", "knight", m_strGameUID, sizeof(m_strGameUID));
	ini.GetString("ODBC", "GAME_PWD", "knight", m_strGamePWD, sizeof(m_strGamePWD));

	m_nServerNo = ini.GetInt("ZONE_INFO", "GROUP_INFO", 1);
	m_nZoneNo = ini.GetInt("ZONE_INFO", "ZONE_INFO", 1);

	if (!m_DBAgent.Connect()
		|| !m_DBAgent.LoadItemTable())
	{
		AfxPostQuitMessage(0);
		return FALSE;
	}

	SetTimer( PROCESS_CHECK, 40000, NULL );
	SetTimer( CONCURRENT_CHECK, 300000, NULL );

	DWORD id;
	m_hReadQueueThread = ::CreateThread( NULL, 0, ReadQueueThread, (LPVOID)this, 0, &id);

	CTime cur = CTime::GetCurrentTime();
	CString starttime;
	starttime.Format("Aujard Start : %02d/%02d/%04d %d:%02d\r\n", cur.GetDay(), cur.GetMonth(), cur.GetYear(), cur.GetHour(), cur.GetMinute());
	m_LogFile.Write(starttime, starttime.GetLength());

	return TRUE;  // return TRUE  unless you set the focus to a control
}