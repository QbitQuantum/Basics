void AFX_CDECL COccManager::UIActivateControl(CWnd* pWndNewFocus)
{
	if (pWndNewFocus == NULL)
		return;

	// Find the nearest control in the window parent chain.
	CWnd* pWndCtrl = pWndNewFocus;
	COleControlContainer* pCtrlCont = NULL;
	COleControlSite* pCtrlSite = NULL;
	while ((pWndCtrl != NULL) &&
		((pCtrlCont = pWndCtrl->m_pCtrlCont) == NULL) &&
		((pCtrlSite = pWndCtrl->m_pCtrlSite) == NULL))
	{
		pWndCtrl = pWndCtrl->GetParent();
	}

	if ((pWndCtrl == NULL) || (pCtrlCont != NULL))
		return;

	// This will UI Activate the control.
	pCtrlSite->SetFocus();

	// Make sure focus gets set to correct child of control, if any.
	if (CWnd::GetFocus() != pWndNewFocus)
		pWndNewFocus->SetFocus();
}