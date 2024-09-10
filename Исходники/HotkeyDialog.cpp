void CHotkeyDialog::OnBnClickedOk()
{
	UINT mod, vkey;

	CString modifierstring;
	modifier.GetLBText(modifier.GetCurSel(),modifierstring);
	CString vkeystr;
	vchar.GetLBText(vchar.GetCurSel(),vkeystr);
	mod = szKeyToIdent(modifierstring);
	vkey = szKeyToIdent(vkeystr);

	UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), 100);
	BOOL m_isKeyRegistered = RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), 100,
	mod, vkey);

	CLaunchyDlg* main_dlg = (CLaunchyDlg*) AfxGetMainWnd();

	if (!m_isKeyRegistered) {
		AfxMessageBox(_T("Sorry, this hotkey will not work, please choose another"));
		// ReRegister the old hot key
		UnregisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), 100);
		BOOL m_isKeyRegistered = RegisterHotKey(AfxGetMainWnd()->GetSafeHwnd(), 100,
		main_dlg->options->mod_key, main_dlg->options->vkey);
	}
	else {
		// Save the new hot key to ini
		main_dlg->options->vkey = vkey;
		main_dlg->options->mod_key = mod;
		OnOK();
	}
}