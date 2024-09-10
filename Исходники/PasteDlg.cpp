/**
 * @brief Paste the bytes.
 * @param [in] hDlg Handle to dialog.
 * @return TRUE if paste succeeded, FALSE if failed.
 */
BOOL PasteDlg::Apply(HWND hDlg)
{
	bPasteAsText = (IsDlgButtonChecked(hDlg, IDC_PASTE_BINARY) == BST_CHECKED);
	iPasteTimes = GetDlgItemInt(hDlg, IDC_PASTE_TIMES, 0, TRUE);
	if (iPasteTimes <= 0)
	{
		LangString atleastOnce(IDS_PASTE_ATLEAST_ONCE);
		MessageBox(hDlg, atleastOnce, MB_ICONERROR);
		return FALSE;
	}
	iPasteSkip = GetDlgItemInt(hDlg, IDC_PASTE_SKIPBYTES, 0, TRUE);
	HWND hwndEdit1 = GetDlgItem(hDlg, IDC_PASTE_CLIPBOARD);
	int destlen = GetWindowTextLength(hwndEdit1) + 1;
	TCHAR *pcPastestring = new TCHAR[destlen];
	destlen = GetWindowText(hwndEdit1, pcPastestring, destlen);
	if (!bPasteAsText)
	{
		BYTE *pc = 0;
		destlen = create_bc_translation(&pc, pcPastestring,
			_tcslen(pcPastestring), iCharacterSet, iBinaryMode);
		delete [] pcPastestring;
		pcPastestring = (TCHAR *) pc;
	}
	if (destlen == 0)
	{
		LangString zeroLenArray(IDS_PASTE_WAS_EMPTY);
		MessageBox(hDlg, zeroLenArray, MB_ICONERROR);
		delete [] pcPastestring;
		return FALSE;
	}

	// Choose to paste as Unicode text or ansi text regardless of build configuration,
	// TODO: UI not yet implemented.
	// ex) bool bPasteAsUnicode = IsDlgButtonChecked(hDlg, IDC_PASTE_AS_UNICODE))
	bool bPasteAsUnicode = false;
	BYTE *pasteData = (BYTE*) pcPastestring;
	int pasteSize = destlen * sizeof TCHAR;

	if (bPasteAsUnicode)
	{
		pasteData = new BYTE[destlen * sizeof WCHAR];
		pasteSize = WideCharToMultiByte(CP_ACP, 0, pcPastestring, destlen,
				(LPSTR) pasteData, destlen, NULL, NULL);
		if ( pasteSize > 0 ) {
			delete [] pcPastestring;
			pcPastestring = (TCHAR *) pasteData; // delete me later.
		}
	}

	WaitCursor wc1;
	if (bSelected || IsDlgButtonChecked(hDlg, IDC_PASTE_INSERT))
	{
		// Insert at iCurByte. Bytes there will be pushed up.
		if (bSelected)
		{
			iCurByte = iGetStartOfSelection();
			int iEndByte = iGetEndOfSelection();
			m_dataArray.RemoveAt(iCurByte, iEndByte - iCurByte + 1);//Remove extraneous data
			bSelected = false; // Deselect
		}
		int i = iCurByte;
		for (int k = 0 ; k < iPasteTimes ; k++)
		{
			if (!m_dataArray.InsertAtGrow(i, pasteData, 0, destlen))
			{
				LangString noMem(IDS_PASTE_NO_MEM);
				MessageBox(hDlg, noMem, MB_ICONERROR);
				break;
			}
			i += destlen + iPasteSkip;
		}
		iFileChanged = TRUE;
		bFilestatusChanged = true;
		resize_window();
	}
	else
	{
		// Overwrite.
		// Enough space for writing?
		// m_dataArray.GetLength()-iCurByte = number of bytes from including curbyte to end.
		if (m_dataArray.GetLength() - iCurByte < (iPasteSkip + destlen) * iPasteTimes)
		{
			LangString noSpace(IDS_PASTE_NO_SPACE);
			MessageBox(hDlg, noSpace, MB_ICONERROR);
			delete [] pcPastestring;
			return TRUE;
		}
		// Overwrite data.
		for (int k = 0 ; k < iPasteTimes ; k++)
		{
			for (int i = 0 ; i < destlen ; i++)
			{
				m_dataArray[iCurByte + k * (iPasteSkip + destlen) + i] = pasteData[i];
			}
		}
		iFileChanged = TRUE;
		bFilestatusChanged = true;
		repaint();
	}
	delete [] pcPastestring;
	return TRUE;
}