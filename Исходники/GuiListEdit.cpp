void CGuiListEdit::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	CWnd* pWnd = GetWindow(GW_CHILD);
        if (pWnd != NULL)
        {
            pWnd->MoveWindow(0, 0, cx, cy);
            ASSERT(pWnd->GetWindow(GW_HWNDNEXT) == NULL);
		}
	//m_Conta.MoveWindow(0,0,cx,cy);
	// TODO: Add your message handler code here
}