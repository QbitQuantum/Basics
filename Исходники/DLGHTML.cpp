int CHtmlDialog::DoModal()
{
	//First get the proc ShowHTMLDialog
	SHOWHTMLDIALOGFN  *pfnShowHTMLDialog;

	pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(m_hInstMSHTML, TEXT("ShowHTMLDialog"));
	
	if (!pfnShowHTMLDialog)
		return -1;
	

	//Now create a URL Moniker
	IMoniker* pmk = NULL;
	BSTR bstrURL = m_strURL.AllocSysString();
	CreateURLMoniker(NULL, bstrURL, &pmk);
	if (!pmk)
		return -1;
	
	TCHAR* pchOptions = m_strOptions.IsEmpty() ? NULL : m_strOptions.GetBuffer(0);
	
	
	//Now show the HTML Dialog
	HRESULT hr = (*pfnShowHTMLDialog)(m_hWndParent, pmk, m_varArgs, pchOptions, m_varReturn);
	if (FAILED(hr))
		return -1;

	return 0;
}