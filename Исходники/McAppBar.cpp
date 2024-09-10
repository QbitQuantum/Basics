void CMcAppBar::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect clientRect;
    GetClientRect(&clientRect);

    CRgn rgn;
    rgn.CreateRectRgnIndirect(&clientRect);
    dc.SelectClipRgn(&rgn,RGN_COPY);

    CMemoryDC	memDc(&dc);
    memDc.FillSolidRect(&clientRect,m_dwBkgColor);

    m_AppCtrl.Draw(&memDc);
}