void CResizableComboBox::UpdateHorizontalExtent(LPCTSTR szText)
{
    CClientDC dc(this);
    CFont* pOldFont = dc.SelectObject(GetFont());

    int cx = dc.GetTextExtent(szText, lstrlen(szText)).cx;
    if (cx > m_iExtent)
    {
        m_iExtent = cx;

        SetHorizontalExtent(m_iExtent
            + LOWORD(GetDialogBaseUnits()));
    }

    dc.SelectObject(pOldFont);
}