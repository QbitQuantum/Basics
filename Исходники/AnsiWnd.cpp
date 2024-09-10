void CAnsiWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if ( m_bSelected ) {
        ReleaseCapture();
        m_bSelected = FALSE;
        InvalidateRect(NULL, FALSE);
        UpdateWindow();
        pDoc->m_bFrozen = FALSE;

        // Well, start forming text for Clipboard
        CString ResultStr;

        // Good, getting reall numbers of strings
        int ScrollIndex = GetScrollPos(SB_VERT)+1;
        m_nStartSelectY = max(0, m_nStartSelectY);
        POSITION pos = m_strList.FindIndex(ScrollIndex+m_nStartSelectY);
        ASSERT(pos);
        int i = m_nStartSelectY;
        do { 
            CString tmpStr = m_strList.GetAt(pos);
            const wchar_t* ptr = tmpStr;
            int count = 0;
            if (pDoc->m_bRectangleSelection || i == m_nStartSelectY) {
                // Skip to StartX character
                while ( count < m_nStartSelectX && *ptr){
                    if ( *ptr == L'\x1B' ){
                        ptr = SkipAnsi(ptr);
                    }
                    else {
                        count++;
                        ptr++;
                    }
                } 
                
            }
            // characters skipped now copy nessesary info to string
            do {
                if ( *ptr == L'\n' ) {
                    ptr++;
                    continue;
                }
                if ( *ptr == L'\x1B' ) {
                    ptr = SkipAnsi(ptr);
                    continue;
                } //* en: do not even try
				if ( !(*ptr))
					break;
                if ( count > m_nEndSelectX && (pDoc->m_bRectangleSelection || i == m_nEndSelectY)) 
                    break;
                ResultStr+= *ptr++;
                count++;
            } while ( *ptr );
            if ( i != m_nEndSelectY ) 
                ResultStr +=L"\r\n";
            i++;
            pos = m_strList.FindIndex(ScrollIndex+i);
        } while ( i<=m_nEndSelectY && pos );
        // Put to clipboard
		if (wcslen(ResultStr) != 0)
		{
			VERIFY(OpenClipboard());

			VERIFY(EmptyClipboard());

			HANDLE hData;

			hData = GlobalAlloc(GMEM_ZEROINIT, (ResultStr.GetLength()+1)*sizeof(wchar_t) );
			wchar_t* buff = (wchar_t*)GlobalLock(hData);
			wcscpy (buff, ResultStr);
			GlobalUnlock(hData);
			SetClipboardData(CF_UNICODETEXT, hData);
			CloseClipboard();
		}
    }
	CWnd::OnLButtonUp(nFlags, point);
}