void CPatchPageDlg::EnableControls(bool Enable)
{
	CWnd	*pFirstCtrl = GetWindow(GW_CHILD);
	ASSERT(pFirstCtrl != NULL);	// need at least one control
	// if requested state differs from first control's enable state
	if (Enable != (pFirstCtrl->IsWindowEnabled() != 0))
		CWinAppCK::EnableChildWindows(*this, Enable);	// iterate controls
}