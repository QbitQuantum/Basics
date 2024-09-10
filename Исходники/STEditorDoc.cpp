HRESULT CSTEditorDoc::GetPages (CStringArray &pages)
{
    TCHAR    szTempName[_MAX_PATH];
    TCHAR    szPath[_MAX_PATH];
    long lLinesPerPage;
    long lLineNum = 0;
    CDC      dcPrint;
    TEXTMETRIC tm;
    CFont Font;
    CFont * pOldFont;
    long lCharsPerLine = 80;

    if (FAILED(AttachPrinterDC(&dcPrint)))
    {
        return (E_FAIL);
    }

    dcPrint.m_bPrinting = TRUE;

    CRect rect;
    rect.SetRect( 0, 0, GetPageWidth (), GetPageHeight () );

    // printing

    lLinesPerPage = GetPrintLinesPerPage(&dcPrint);

    HDC hdcMeta = NULL;
    CDC dcMeta;

    for (LINEDESC * pLine = m_Edit.m_pLine; NULL != pLine; pLine = pLine->pNext)
    {
        bool bSuccess;
        CString strText;

        bSuccess = m_Edit.ExpandLine (pLine, strText);
        ASSERT (bSuccess);

        strText.TrimRight ();

        // if text line is empty make it a line with a single
        // blank character
        if (strText.IsEmpty())
        {
            strText = _T(" ");
        }

        while (!strText.IsEmpty())
        {

            if (hdcMeta == NULL)
            {
                VERIFY(GetTempPath(sizeof(szPath), szPath) != 0);
                VERIFY(GetTempFileName(szPath, _T("pst"), 0, szTempName) != 0);
                pages.Add( szTempName );

                CString strDesc;
                CString strAppl;
                TCHAR*   pBuf;

                strAppl = GetPathName();

                // read documentation of CreateEnhMetaFile() to understand the
                // formatting of this string
                strDesc.Format("STEditor %s Page %d ", strAppl, pLine->iLineNo);
                pBuf = strDesc.GetBuffer(0);
                pBuf[8] = 0;
                pBuf[strDesc.GetLength() - 1] = 0;
                strDesc.ReleaseBuffer();

                hdcMeta = ::CreateEnhMetaFile( dcPrint, szTempName, &rect, strDesc);

                if (!hdcMeta) 
                {
                    return (E_FAIL);
                }

                dcMeta.Attach(hdcMeta);
                dcMeta.m_bPrinting = TRUE;
                dcMeta.SetMapMode (MM_TEXT);

                pOldFont = SelectPrintFont(&dcMeta, &Font);
                dcMeta.GetTextMetrics(&tm);
                CSize tmSize(tm.tmAveCharWidth, tm.tmHeight);
                dcMeta.LPtoHIMETRIC(&tmSize);
                lCharsPerLine = GetPageWidth() / tmSize.cx;
            }

            dcMeta.TextOut(0, lLineNum * tm.tmHeight, strText.Left(lCharsPerLine));
            lLineNum++;
            if (strText.GetLength() > lCharsPerLine)
            {
                strText = strText.Mid(lCharsPerLine);
            }
            else
            {
                strText = _T("");
            }

            if (lLineNum >= lLinesPerPage)
            {
                lLineNum = 0;
                dcMeta.SelectObject(pOldFont);
                Font.DeleteObject();
                dcMeta.Detach();
                DeleteEnhMetaFile (CloseEnhMetaFile(hdcMeta));
                hdcMeta = NULL;
            }
        }
    }

    if (NULL != hdcMeta)
    {
        dcMeta.SelectObject(pOldFont);
        dcMeta.Detach();
        DeleteEnhMetaFile (CloseEnhMetaFile(hdcMeta));
        hdcMeta = NULL;
    }

    return (S_OK);
}