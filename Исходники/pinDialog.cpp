bool pinDialogPriv::doDialog() {
	if (IDOK == DialogBoxParam(params.m_hInst,MAKEINTRESOURCE(params.m_resourceID)
		,GetForegroundWindow(),
		(DLGPROC)dialogProc, (LPARAM) this)) return true;
	return false;
	}