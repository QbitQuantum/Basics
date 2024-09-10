CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TIP, pParent)
{
char fullfilename[MAX_PATH];
char filename [MAX_PATH];
char * p;

  // look for tips.txt in the same directory as the executable file
  if (GetModuleFileName (NULL, fullfilename, sizeof (fullfilename)))
   {

// remove last part of file name to get working directory

    strcpy (filename, fullfilename);

    p = strrchr (filename, '\\');
    if (p)
      *p = 0;

    strcat (filename, "\\tips.txt");
    }
  else
    strcpy (filename, "tips.txt");

	//{{AFX_DATA_INIT(CTipDlg)
	m_bStartup = TRUE;
	//}}AFX_DATA_INIT

	// We need to find out what the startup and file position parameters are
	// If startup does not exist, we assume that the Tips on startup is checked TRUE.
	CWinApp* pApp = AfxGetApp();
	m_bStartup = !App.db_get_int("control", szIntStartup, 0);
	UINT iFilePos = App.db_get_int("control", szIntFilePos, 0);

	// Now try to open the tips file
	m_pStream = fopen(filename, "r");
	if (m_pStream == NULL) 
	{
		m_strTip.LoadString(CG_IDS_FILE_ABSENT);
		return;
	} 

	// If the timestamp in the INI file is different from the timestamp of
	// the tips file, then we know that the tips file has been modified
	// Reset the file position to 0 and write the latest timestamp to the
	// ini file
	struct _stat buf;
	_fstat(_fileno(m_pStream), &buf);
	CString strCurrentTime = ctime(&buf.st_ctime);
	strCurrentTime.TrimRight();
	CString strStoredTime = 
		App.db_get_string("control", szTimeStamp, "");
	if (strCurrentTime != strStoredTime) 
	{
		iFilePos = 0;
		App.db_write_string("control", szTimeStamp, strCurrentTime);
	}

	if (fseek(m_pStream, iFilePos, SEEK_SET) != 0) 
	{
		AfxMessageBox(CG_IDP_FILE_CORRUPT);
	}
	else 
	{
		GetNextTipString(m_strTip);
	}
}