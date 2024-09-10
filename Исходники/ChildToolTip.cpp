BOOL CChildToolTip::EnableToolTips(CWnd *pWnd, BOOL bEnable, BOOL UseDlgIDs)
{
	if (bEnable) {
		if (m_ToolTip != NULL)
			return(TRUE);		// already enabled, nothing to do
		m_ToolTip = new CToolTipCtrl;
		if (!m_ToolTip->Create(pWnd))
			return(FALSE);
		// iterate over our child controls, adding them to tooltip
		CWnd	*p = pWnd->GetWindow(GW_CHILD);
		while (p != NULL) {
			if (UseDlgIDs) {
				int	nID = p->GetDlgCtrlID();
				if (nID != -1) {
       				if (!m_ToolTip->AddTool(p, nID))
						return(FALSE);
				}
			} else {
       			if (!m_ToolTip->AddTool(p))
					return(FALSE);
			}	
			p = p->GetWindow(GW_HWNDNEXT);
		}
	} else {
		if (m_ToolTip == NULL)
			return(TRUE);		// already disabled, nothing to do
		delete m_ToolTip;
		m_ToolTip = NULL;
	}
	return(TRUE);
}