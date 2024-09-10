void CPPageBase::CreateToolTip()
{
    m_wndToolTip.Create(this, TTS_NOPREFIX);
    m_wndToolTip.Activate(TRUE);
    m_wndToolTip.SetMaxTipWidth(300);
    m_wndToolTip.SetDelayTime(TTDT_AUTOPOP, 10000);
    for (CWnd* pChild = GetWindow(GW_CHILD); pChild; pChild = pChild->GetWindow(GW_HWNDNEXT)) {
        CString strToolTip;
        if (strToolTip.LoadString(pChild->GetDlgCtrlID())) {
            m_wndToolTip.AddTool(pChild, strToolTip);
        }
    }
}