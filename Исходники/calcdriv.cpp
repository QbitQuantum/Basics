BOOL CDriverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// create the calculator object that we'll drive through OLE automation
	COleException e;
	CLSID clsid;
	if (CLSIDFromProgID(OLESTR("mfccalc.calculator"), &clsid) != NOERROR)
	{
		AfxMessageBox(IDP_UNABLE_TO_CREATE);
		EndDialog(IDABORT);
		return FALSE;
	}

	// try to get the active calculator before creating a new one
	LPUNKNOWN lpUnk;
	LPDISPATCH lpDispatch;
	if (GetActiveObject(clsid, NULL, &lpUnk) == NOERROR)
	{
		HRESULT hr = lpUnk->QueryInterface(IID_IDispatch,
			(LPVOID*)&lpDispatch);
		lpUnk->Release();
		if (hr == NOERROR)
			m_calc.AttachDispatch(lpDispatch, TRUE);
	}

	// if not dispatch ptr attached yet, need to create one
	if (m_calc.m_lpDispatch == NULL &&
		!m_calc.CreateDispatch(clsid, &e))
	{
		AfxMessageBox(IDP_UNABLE_TO_CREATE);
		EndDialog(IDABORT);
		return FALSE;
	}

	// attempt to make it visible
	m_calc.SetVisible(TRUE);
	if (!m_calc.GetVisible())
	{
		AfxMessageBox(IDP_UNABLE_TO_SHOW);
		EndDialog(IDABORT);
		return FALSE;
	}

	// refresh display to contents of the automation calculator
	OnRefresh();

	return TRUE;  // return TRUE  unless you set the focus to a control
}