void CStatusLabel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CString str;
    GetWindowText(str);
    CRect clientRect;
    GetClientRect(&clientRect);

    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);
    dc.SetTextColor(0xffffff);
    dc.SetBkColor(0);
    CFont* old = dc.SelectObject(&m_font);
    const UINT style = DT_SINGLELINE | DT_NOPREFIX | (m_fAddEllipses ? DT_END_ELLIPSIS : 0);
    CRect textRect(clientRect);
    dc.DrawText(str, textRect, style | DT_CALCRECT);
    if (m_fRightAlign) {
        textRect.MoveToX(clientRect.Width() - textRect.Width());
    }
    textRect.MoveToY((clientRect.Height() - textRect.Height()) / 2);
    dc.DrawText(str, textRect, style);
    dc.ExcludeClipRect(textRect);
    dc.FillSolidRect(clientRect, 0);
    dc.SelectObject(&old);
    dc.Detach();
}