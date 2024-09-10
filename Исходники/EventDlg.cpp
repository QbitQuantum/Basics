bool EventDlg::CopyToClipboard(bool bAll, bool bHeaders)
{
	const PTCHAR  _cediteol = "\r\n";
	if ( !OpenClipboard() )
	{
		AfxMessageBox( "Cannot open the Clipboard" );
		return true;
	}
	// Remove the current Clipboard contents
	if( !EmptyClipboard() )
	{
		AfxMessageBox( "Cannot empty the Clipboard" );
		return true;
	}
	// Get the currently selected data

	int nItem, j, tlen, headeroffset;
	const int ic = m_List.GetItemCount();
	CStringArray a;
	a.SetSize(ic);
	tlen = 0;
	headeroffset = 0;
	if (bHeaders)
	{
		CString s;
		for (j = efhFacility;  j < efhHeaderCount; j++)
		{
			UINT icol = j;  // direct mapping from header id to header string
			s.Append(CFDMSApp::GetFileHeader(CSVFileHeaderIDs(icol)));
			s.AppendChar('\t');
		}
		s.Append(_cediteol);
		a.SetAtGrow(0, s);
		tlen += s.GetLength();
		headeroffset = 1;
	}

	// now for the rows
	for (nItem = 0; nItem < ic; nItem++)
	{
		if (!bAll && !m_List.GetItemState(nItem, LVIS_SELECTED))
			continue;

		CString s = m_List.GetItemText(nItem,0);
		for (j = efhFacility; j < efhHeaderCount; j++)
		{
			if (j == efhDischMonth || j == efhDischYear)  // blend of three columns into one
				continue;
			if (j == efhMeasMonth || j == efhMeasYear)  // blend
				continue;
			UINT icol = ImpEditCol::m_fileheadermap[j];
			if (j == efhDischDay)  //  build combined disch date
			{
				COleDateTime dt = m_List.GetDateTime(nItem, icol);
				s.Append(dt.Format("%d\t%m\t%Y"));
			}
			else
			if (j == efhMeasDay)  // build combined meas date
			{
				COleDateTime dt = m_List.GetDateTime(nItem, icol);
				s.Append(dt.Format("%d\t%m\t%Y"));				
			}
			else
			if (j == efhStatus)  // get status from the related globals
			{
				s.Append("0");  // the status of all entries in an import dialog is always unmeasured
			}
			else
			if (j == efhMeasType)  // convert string to number from the item text
			{
				CString cs;
				cs.Format("%d", tImageToMeasurementType(m_List.GetItemText(nItem,icol)));
				s.Append(cs);
			}
			else
				s.Append(m_List.GetItemText(nItem,icol));
			s.AppendChar('\t');
		}
		s.Append(_cediteol);
		a.SetAtGrow(nItem + headeroffset, s);
		tlen += s.GetLength();
	}

    // Allocate a global memory object for the text. 
	LPTSTR  lptstrCopy; 
	HGLOBAL hglbCopy; 
    hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 
        (tlen + 1) * sizeof(TCHAR)); 
    if (hglbCopy == NULL) 
    { 
        CloseClipboard(); 
        return true; 
    } 

    // Lock the handle and copy the text to the buffer. 
    lptstrCopy = (LPSTR)GlobalLock(hglbCopy);
    lptstrCopy[0] = (TCHAR) 0;    // null character 
	for (nItem = 0; nItem < a.GetCount(); nItem++)
	{
		LPSTR b = a[nItem].GetBuffer();
		size_t l = a[nItem].GetLength() *  sizeof(TCHAR);
		strncat(lptstrCopy, b, l);
	}
    lptstrCopy[tlen] = (TCHAR) 0;    // null character 
    GlobalUnlock(hglbCopy); 

    // Place the handle on the clipboard. 

	// For the appropriate data formats...
	if ( SetClipboardData( CF_TEXT, hglbCopy ) == NULL )
	{
		AfxMessageBox( "Unable to set Clipboard data" );
		CloseClipboard();
		return true;
	}
	CloseClipboard();
	return true;
}