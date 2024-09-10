void CTestClockDlg::OnSize(UINT nType, int cx, int cy)
{
    if (m_bInit == TRUE)
    {
        SetRadius(cx, cy);
        SetCenterPoint(cx, cy);
        SetGradationPoints();

        m_nHourGradSize = MulDiv(DEFAULT_HOUR_GRAD_SIZE, m_nRadius, m_nRadiusOrg);
        m_nMinuteGradSize = MulDiv(DEFAULT_MINUTE_GRAD_SIZE, m_nRadius, m_nRadiusOrg);
        m_nSecondHandSize = MulDiv(DEFAULT_SECOND_HAND_SIZE, m_nRadius, m_nRadiusOrg);
        m_nCenterPointSize = MulDiv(DEFAULT_CENTER_POINT_SIZE, m_nRadius, m_nRadiusOrg);

        SetClockHandPoints();

        // Set position of the 'OK' and 'Cancel' button

        CRect rect;
        CRect rectBtnOk;
        CRect rectBtnOkToMove;
        CRect rectBtnCancel;
        CRect rectBtnCancelToMove;

        GetClientRect(rect);
        ClientToScreen(rect);

        m_btnOk.GetWindowRect(rectBtnOk);
        ScreenToClient(rectBtnOk);

        m_btnCancel.GetWindowRect(rectBtnCancel);
        ScreenToClient(rectBtnCancel);

        rectBtnOkToMove.right = rect.Width() - m_marginBtnOk.right;
        rectBtnOkToMove.bottom = rect.Height() - m_marginBtnOk.bottom;
        rectBtnOkToMove.left = rectBtnOkToMove.right - rectBtnOk.Width();
        rectBtnOkToMove.top = rectBtnOkToMove.bottom - rectBtnOk.Height();

        rectBtnCancelToMove.right = rect.Width() - m_marginBtnCancel.right;
        rectBtnCancelToMove.bottom = rect.Height() - m_marginBtnCancel.bottom;
        rectBtnCancelToMove.left = rectBtnCancelToMove.right - rectBtnCancel.Width();
        rectBtnCancelToMove.top = rectBtnCancelToMove.bottom - rectBtnCancel.Height();

        HDWP hdwp = ::BeginDeferWindowPos(2);
        if (hdwp)
            hdwp = DeferWindowPos(hdwp, m_btnOk.GetSafeHwnd(), HWND_TOP, rectBtnOkToMove.left, rectBtnOkToMove.top, rectBtnOkToMove.Width(), rectBtnOkToMove.Height(), SWP_NOZORDER);
        if (hdwp)
            DeferWindowPos(hdwp, m_btnCancel.GetSafeHwnd(), HWND_TOP, rectBtnCancelToMove.left, rectBtnCancelToMove.top, rectBtnCancelToMove.Width(), rectBtnCancelToMove.Height(), SWP_NOZORDER);
        if (hdwp)
            EndDeferWindowPos(hdwp);

        Invalidate();
        UpdateWindow();
    }

    CDialog::OnSize(nType, cx, cy);
}