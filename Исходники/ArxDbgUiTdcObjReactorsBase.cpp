BOOL
ArxDbgUiTdcObjReactorsBase::PreTranslateMessage(MSG* pMsg) 
{
    if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN)) {
        CWnd *pWnd = GetFocus();
        if (pWnd != NULL) {
            UINT nID = pWnd->GetDlgCtrlID();
            if (nID == ARXDBG_BN_ATTACH_ENT) {
                ::PostMessage(m_attachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_ENT) {
                ::PostMessage(m_detachEntButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_SEL_ENTS) {
                ::PostMessage(m_detachSelectedEntsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
            if (nID == ARXDBG_BN_DETACH_SEL_OBJS) {
                ::PostMessage(m_detachSelectedObjsButton.m_hWnd, BM_CLICK, 0, 0);
                return TRUE;
            }
        }
    }
	
	return CAcUiTabChildDialog::PreTranslateMessage(pMsg);
}