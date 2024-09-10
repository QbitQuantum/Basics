void CColorBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    // TODO: Add your message handler code here and/or call default

    char tchBuffer[256];
    RECT rect;
    TEXTMETRIC tm;
    int i;
    int OffSet;
    PropertyStruct * tPS;

    if ( (
                lpDrawItemStruct->CtlType == ODT_LISTBOX)
            && (lpDrawItemStruct->CtlID == IDC_COLORLIST)
            && (lpDrawItemStruct->itemID != -1)
       ) {

        GetTextMetrics( lpDrawItemStruct->hDC, &tm);
        OffSet = tm.tmHeight * 2;

        switch ( lpDrawItemStruct->itemAction ) {
        case ODA_DRAWENTIRE:

            tPS = (PropertyStruct *)lpDrawItemStruct->itemData;

            sprintf ( tchBuffer, "%2d:", tPS->RowNum );

//			OffSet = LOWORD(GetTextExtent( lpDrawItemStruct->hDC, tchBuffer, 5 ));

            SetBkColor ( lpDrawItemStruct->hDC, RGB(255,255,255) );
            SetTextColor ( lpDrawItemStruct->hDC, RGB(0,0,0) );

            TextOut(lpDrawItemStruct->hDC,
                    lpDrawItemStruct->rcItem.left,
                    lpDrawItemStruct->rcItem.top,
                    tchBuffer,
                    3
                   );

            m_ColorList.GetText( lpDrawItemStruct->itemID, tchBuffer );

            for ( i = strlen ( tchBuffer ); i < 75; ++i ) {
                tchBuffer[i] = ' ';
            }
            tchBuffer[i] = 0;

            SetBkColor ( lpDrawItemStruct->hDC, tPS->BkColor );
            SetTextColor ( lpDrawItemStruct->hDC, tPS->TextColor );

            TextOut(lpDrawItemStruct->hDC,
                    lpDrawItemStruct->rcItem.left + OffSet,
                    lpDrawItemStruct->rcItem.top,
                    tchBuffer,
                    strlen(tchBuffer)
                   );

            if ( lpDrawItemStruct->itemState & ODS_SELECTED ) {
                rect.left = lpDrawItemStruct->rcItem.left;
                rect.top = lpDrawItemStruct->rcItem.top;
                rect.right = lpDrawItemStruct->rcItem.left + OffSet;
                rect.bottom = lpDrawItemStruct->rcItem.bottom;

                InvertRect(lpDrawItemStruct->hDC, &rect);
            }

            break;

        case ODA_SELECT:

            rect.left = lpDrawItemStruct->rcItem.left;
            rect.top = lpDrawItemStruct->rcItem.top;
            rect.right = lpDrawItemStruct->rcItem.left + OffSet;
            rect.bottom = lpDrawItemStruct->rcItem.bottom;

            InvertRect(lpDrawItemStruct->hDC, &rect);

            break;
        }

    }

    if ( nIDCtl == IDC_DISP ) {

        TEXTMETRIC m_TM;
        HGDIOBJ tFont;
        LOGFONT tLOGFONT;
        int tPointSize;
        int tFontWeight;
        memset ( &tLOGFONT, 0, sizeof(tLOGFONT) );

        CGenedocDoc *pDoc = ((CGenedocView *)m_pParent)->GetDocument();

        tFontWeight = pDoc->m_UserVars.m_FontWeight;

        tPointSize = pDoc->m_UserVars.m_FontSize;


        strcpy ( tLOGFONT.lfFaceName, "Courier New" );
        tLOGFONT.lfWeight = tFontWeight;
        tLOGFONT.lfHeight = -MulDiv( tPointSize , GetDeviceCaps(lpDrawItemStruct->hDC, LOGPIXELSY), 72);

        tFont = CreateFontIndirect( &tLOGFONT );

        HGDIOBJ oFont = SelectObject( lpDrawItemStruct->hDC, tFont);


        GetTextMetrics( lpDrawItemStruct->hDC, &m_TM );

        MoveToEx ( lpDrawItemStruct->hDC,
                   lpDrawItemStruct->rcItem.left,
                   lpDrawItemStruct->rcItem.top,
                   NULL
                 );

        LineTo ( lpDrawItemStruct->hDC,
                 lpDrawItemStruct->rcItem.left,
                 lpDrawItemStruct->rcItem.bottom - 1
               );

        LineTo ( lpDrawItemStruct->hDC,
                 lpDrawItemStruct->rcItem.right - 1,
                 lpDrawItemStruct->rcItem.bottom - 1
               );

        LineTo ( lpDrawItemStruct->hDC,
                 lpDrawItemStruct->rcItem.right - 1,
                 lpDrawItemStruct->rcItem.top
               );

        LineTo ( lpDrawItemStruct->hDC,
                 lpDrawItemStruct->rcItem.left,
                 lpDrawItemStruct->rcItem.top
               );

        int hx = (lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left) / 2;
        int hy = (lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top) / 2;
        hx -= m_TM.tmAveCharWidth / 2;
        hy -= (m_TM.tmHeight - m_TM.tmInternalLeading) / 2;

        SetBkColor( lpDrawItemStruct->hDC, m_BackColor );
        SetTextColor( lpDrawItemStruct->hDC, m_TextColor );
        // RECT

        TextOut (
            lpDrawItemStruct->hDC,
            lpDrawItemStruct->rcItem.left + hx,
            lpDrawItemStruct->rcItem.top + hy,
            "G", 1
        );


        if ( oFont != NULL ) {
            SelectObject( lpDrawItemStruct->hDC, oFont);
        }

    }

    // Was commented
    // CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}