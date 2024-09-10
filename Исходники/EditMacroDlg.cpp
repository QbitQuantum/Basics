BOOL CEditMacroDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Rebuild the macro filename
	TCHAR szCurrentDir[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,szCurrentDir);
	CString strPath(szCurrentDir);
	if ( strPath[strPath.GetLength()-1] != '\\' ) {
		// The directory doesn't end with a backslash,
		// so we add one now.
		strPath += '\\';
	} // if
	ASSERT(m_strMacroName.GetLength());
	m_strFile = strPath + m_strMacroName + ".mac";

	// Load the file
	try {
		CFile fileMacro(m_strFile,CFile::modeRead|CFile::shareDenyWrite);

		// Determine the file's length
		DWORD dwSize = fileMacro.GetLength();

		// Read the file
		fileMacro.Read(m_strText.GetBuffer(dwSize),dwSize);
		m_strText.ReleaseBuffer();

		// Close it
		fileMacro.Close();
	} // try
	catch (CFileException* e) {
		// File I/O error
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						e->m_cause,
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("File error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
		EndDialog(IDCANCEL);
	} // catch
	catch (...) {
		// Some other error...
		CString strMsg;
		::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | 
						FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_IGNORE_INSERTS,
						NULL,
						GetLastError(),
						MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
						strMsg.GetBuffer(_MAX_PATH),
						0,
						NULL );
		strMsg.ReleaseBuffer();
		strMsg = _T("Error reading macro file, '") + strMsg + _T("'");

		// Display the string.
		AfxMessageBox(strMsg,MB_OK|MB_ICONERROR);
		EndDialog(IDCANCEL);
	} // catch

	// Set the focus to the edit control
	UpdateData(FALSE);
	CWnd* pEdit = GetDlgItem(IDC_TEXTEDIT);
	pEdit->SetFocus(); // note we set the return value to FALSE below...
	
	return FALSE; // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
//	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}