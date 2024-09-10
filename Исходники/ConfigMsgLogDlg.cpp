void CConfigMsgLogDlg::OnTimer(UINT nIDEvent)
{
    if (nIDEvent == m_unDispUpdateTimerId)
    {
        static bool bSwitchDisplay = true;
        CDC* pdc= GetWindowDC();
        pdc->SetTextColor(RGB(253,153,4));
        pdc->SetBkMode(TRANSPARENT);

        if(bSwitchDisplay)
        {
            SetWindowText("");
            pdc->DrawText(m_strCurrWndText,CRect(4,4,400,50),DT_END_ELLIPSIS);
            bSwitchDisplay = false;
        }
        else
        {
            pdc->DrawText(m_strCurrWndText,CRect(4,4,400,50),DT_END_ELLIPSIS);
            SetWindowText(m_strCurrWndText);
            bSwitchDisplay = true;
        }
        ReleaseDC(pdc);
    }
    CDialog::OnTimer(nIDEvent);
}