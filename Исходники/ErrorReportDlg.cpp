LRESULT CErrorReportDlg::OnEraseBkgnd(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    CDCHandle dc((HDC)wParam);

    RECT rcClient;
    GetClientRect(&rcClient);

    RECT rc;
    CStatic statUpperHorzLine = GetDlgItem(IDC_UPPERHORZ);
    statUpperHorzLine.GetWindowRect(&rc);
    ScreenToClient(&rc);

    COLORREF cr = GetSysColor(COLOR_3DFACE);
    CBrush brush;
    brush.CreateSolidBrush(cr);  

    RECT rcHeading = {0, 0, rcClient.right, rc.bottom};
    dc.FillRect(&rcHeading, (HBRUSH)GetStockObject(WHITE_BRUSH));

    RECT rcBody = {0, rc.bottom, rcClient.right, rcClient.bottom};
    dc.FillRect(&rcBody, brush);

    rcHeading.left = 60;
    rcHeading.right -= 10;

    CString sHeading;
    sHeading.Format(Utility::GetINIString(g_CrashInfo.m_sLangFileName, _T("MainDlg"), _T("HeaderText")), g_CrashInfo.m_sAppName);
    dc.SelectFont(m_HeadingFont);
    dc.DrawTextEx(sHeading.GetBuffer(0), sHeading.GetLength(), &rcHeading, 
        DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);  

    if(m_HeadingIcon)
    {
        ICONINFO ii;
        m_HeadingIcon.GetIconInfo(&ii);
        dc.DrawIcon(16, rcHeading.bottom/2 - ii.yHotspot, m_HeadingIcon);
    }

    return TRUE;
}