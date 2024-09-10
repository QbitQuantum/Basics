void CSmcView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CSmcDoc* pDoc = GetDocument();
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
        ASSERT(m_nStartSelectY>=0);
        POSITION pos = m_strList.FindIndex(ScrollIndex+m_nStartSelectY);
        ASSERT(pos);
        int i = m_nStartSelectY;
        do { 
            CString tmpStr = m_strList.GetAt(pos);
            char* ptr = (LPSTR)(LPCSTR)tmpStr;
            int count = 0;
//            if (i == m_nStartSelectY && i == m_nEndSelectY) {
                // Skip to StartX character
                while ( count < m_nStartSelectX && *ptr){
                    if ( *ptr == 0x1B ){
                        ptr = SkipAnsi(ptr);
                    }
                    else {
                        count++;
                        ptr++;
                    }
                } 
                
//            }
            // characters skipped now copy nessesary info to string
            do {
                if ( *ptr == '\n' /*|| *ptr == '\r'*/ ) {
                    ptr++;
                    continue;
                }
                if ( *ptr == 0x1B ) {
                    ptr = SkipAnsi(ptr);
                    continue;
                }
                if ( i == m_nEndSelectY && count >= m_nEndSelectX ) 
                    break;
                ResultStr+= *ptr++;
                count++;
            } while ( *ptr );
            if ( i != m_nEndSelectY ) 
                ResultStr +="\r\n";
            i++;
            pos = m_strList.FindIndex(ScrollIndex+i);
        } while ( i<=m_nEndSelectY && pos );
        // Put to clipboard
		if (strlen(ResultStr) != 0)
		{
			VERIFY(OpenClipboard());

			VERIFY(EmptyClipboard());

			LCID lc = GetUserDefaultLCID();
			HANDLE hData = GlobalAlloc(GMEM_ZEROINIT, sizeof(lc) );
			LCID* pLc = (LCID*)GlobalLock(hData);
			*pLc = lc;
			GlobalUnlock(hData);
			SetClipboardData(CF_LOCALE, hData);
			hData = GlobalAlloc(GMEM_ZEROINIT, ResultStr.GetLength()+1 );
			char* buff = (char*)GlobalLock(hData);
			strcpy (buff, (LPSTR)(LPCSTR)ResultStr);
			GlobalUnlock(hData);
			SetClipboardData(CF_TEXT, hData);
			CloseClipboard();
		}
    }
	CView::OnLButtonUp(nFlags, point);
}