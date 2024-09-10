void CFileEditCtrl::OnDropFiles(HDROP hDropInfo) 
{
	// handles drag and drop file entry, control must have the
	// WS_EX_ACCEPTFILES extended style set.
	CString szSeperator;
#if defined FEC_NORESOURCESTRINGS
	szSeperator = FEC_IDS_SEPERATOR;
#else
	szSeperator.LoadString(FEC_IDS_SEPERATOR);
#endif
	ASSERT (_tcslen(szSeperator) == 1);			// must be one character only
	szSeperator += _T(" ");						// get the file seperator character
	CString szDroppedFiles;						// buffer to contain all the dropped files

	TCHAR lpstrDropBuffer[_MAX_PATH];
	UINT nDropCount = DragQueryFile(hDropInfo,0xffffffff,NULL,0);
	if (nDropCount && (m_bFindFolder || (!m_bFindFolder && !(m_pCFileDialog->m_ofn.Flags & OFN_ALLOWMULTISELECT))))
		nDropCount = 1;
	if (nDropCount)
	{
		DragQueryFile(hDropInfo, 0, lpstrDropBuffer, _MAX_PATH);
		szDroppedFiles = lpstrDropBuffer;
	}
	for (UINT x = 1; x < nDropCount; x++)
	{
		DragQueryFile(hDropInfo, x, lpstrDropBuffer, _MAX_PATH);
		szDroppedFiles += szSeperator;
		szDroppedFiles += lpstrDropBuffer;
	}
	DragFinish (hDropInfo);
	SetWindowText (szDroppedFiles);
}