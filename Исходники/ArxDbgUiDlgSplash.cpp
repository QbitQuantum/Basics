void
ArxDbgUiDlgSplash::processTextLine(CString& str, UINT dlgItemId, int& numLines, int ht)
{
    CWnd* wnd = GetDlgItem(dlgItemId);
    ASSERT(wnd != NULL);
    if (wnd) {
        if (str.IsEmpty()) {
            wnd->SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOZORDER);
        }
        else {
            wnd->SetWindowPos(NULL, kBorderX, m_picHeight+(kBorderY)+(numLines*ht),
                            m_picWidth, ht, SWP_NOZORDER);
            wnd->SetWindowText(str);
            numLines++;
        }
    }
}