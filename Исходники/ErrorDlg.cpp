BOOL CErrorsDialog::OnInitDialog()
{

	CDialog::OnInitDialog();

	// Set the help button to be inactive
	m_ctlHelp.EnableWindow(FALSE);

	// Read in the error information from IErrorRecords
	CDBErrorInfo errInfo;
	ULONG ulRecords = 0;
	HRESULT hr;

	hr = errInfo.GetErrorRecords(m_spUnk, m_iid, &ulRecords);
	if (FAILED(hr) || hr == S_FALSE || ulRecords == 0)
	{
		CString strError;
		if( strError.LoadString(IDS_NOSPECIFIED_SOURCE) == FALSE)
		{
			AfxThrowResourceException();
		}
		m_ctlListSource.AddString(strError);
	}
	else
	{
		LCID lcid = GetUserDefaultLCID();
		for (ULONG l=0; l<ulRecords; l++)
		{
			// Get the error information from the source
			struct MYERRORINFO* pInfo = new MYERRORINFO;
			#pragma warning(disable: 6011) // unexpected null dereference prefast warning
			hr = errInfo.GetAllErrorInfo(l, lcid, &pInfo->bstrDescription,
				&pInfo->bstrSource, &pInfo->guid, &pInfo->dwHelpContext,
				&pInfo->bstrHelpFile);
			#pragma warning(default: 6011) // unexpected null dereference prefast warning
			if (FAILED(hr))
			{
				delete pInfo;
				continue;
			}

			m_listErrorInfo.AddTail(pInfo);

			// Add the information to the list view
			if (pInfo->bstrSource)
				m_ctlListSource.AddString(COLE2T(pInfo->bstrSource));
			else
				m_ctlListSource.AddString(_T("Unspecified error."));
		}
	}
	m_ctlListSource.SetCurSel(0);
	SelectSource(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}