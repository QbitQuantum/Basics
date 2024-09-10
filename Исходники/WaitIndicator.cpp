void CWaitIndicator::PaintWindow(CDC& dc)
{

    CRect ClientRect;

    // Client Rect Painting
    GetClientRect(&ClientRect);
    CBrush omBrush((COLORREF) GetSysColor(COLOR_ACTIVECAPTION));
    // Load Font Deatils
    dc.SetBkMode(TRANSPARENT);
    CBrush omBkgBrush((COLORREF)GetSysColor(COLOR_ACTIVEBORDER));
    dc.FillRect(ClientRect, &omBkgBrush);
    dc.FrameRect(&ClientRect, &omBrush);

    // Finally Set The text;
    dc.DrawText(m_strTitle, &ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}