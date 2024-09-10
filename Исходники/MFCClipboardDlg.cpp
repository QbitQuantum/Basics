void CMFCClipboardDlg::OnBnClickedCopyButton()
{
	/////////////////////////////////////////////////////////////////////////
	// 1. Get text from edit control.
	// 

	CString strData;
	m_editSource.GetWindowTextW(strData);

	int len = strData.GetLength();

	if (len <= 0)
		return;


	/////////////////////////////////////////////////////////////////////////
	// 2. Open and empty clipboard. (OpenClipboard, EmptyClipboard)
	// 

	if (!OpenClipboard())
		return;

	EmptyClipboard(); 


	/////////////////////////////////////////////////////////////////////////
	// 3. Create global buffer. (GlobalAlloc)
	// 

	HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (len + 1));
	
	if (hglbCopy == NULL) 
    { 
        CloseClipboard(); 
        return; 
    }


	/////////////////////////////////////////////////////////////////////////
	// 4. Lock the buffer. (GlobalLock)
	// 

	char* lptstrCopy = (char*)GlobalLock(hglbCopy); 


	/////////////////////////////////////////////////////////////////////////
	// 5. Copy text to the buffer. (strcpy)
	// 

	strcpy(lptstrCopy, (CStringA)strData);


	/////////////////////////////////////////////////////////////////////////
	// 6. Unlock the buffer. (GlobalUnlock)
	// 

	GlobalUnlock(hglbCopy); 


	/////////////////////////////////////////////////////////////////////////
	// 7. Set buffer data to clipboard. (SetClipboardData)
	// 

	SetClipboardData(CF_TEXT, hglbCopy); 


	/////////////////////////////////////////////////////////////////////////
	// 8. Close clipboard. (CloseClipboard)
	// 

	CloseClipboard(); 	
}