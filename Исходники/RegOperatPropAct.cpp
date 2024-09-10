///////////////////////////////////////////////////////////////////////////////////////////////
// IPropertyAction methods
// PropertyPages einhängen
// diese Stelle wird bei DoActions() erreicht
STDMETHODIMP CRegOperatPropAct::AddConfigPages (LPFNADDPROPSHEETPAGE lpfnAddPage,
												LPARAM lParam, LPCSTR pcDesc, UINT *puiCnt)
{
char cbCaption[_MAX_PATH];

	try
	{
		if (NULL != pcDesc)		// Caption ist gegeben
			strcpy (cbCaption, pcDesc);
		else	// von zugehöriger ClassProperty unseren Namen besorgen
			GetPropInfo (cbCaption, sizeof(cbCaption), NULL);

		// zugehörigen ConfigDialog (PropertyPage(s)) anlegen
		DELETE_OBJ (m_pRegOperDlg);	// evtl. vorherigen freigeben
		m_pRegOperDlg = CRegardOperatDlg::CreateInstance (ResID(IDD_REGOPERATPROPACT, pRF),
														  cbCaption, this, m_caSelInfo, *pRF);
		if (NULL == m_pRegOperDlg) _com_issue_error (E_OUTOFMEMORY);

		if (!IsNoShow())
		{
		// Seite hinzufügen, wenn selbige angezeigt werden soll
		HPROPSHEETPAGE hPSP = m_pRegOperDlg -> CreatePage();

			if (NULL == hPSP) return E_HANDLE;
			if (!(*lpfnAddPage) (hPSP, lParam))
				return E_UNEXPECTED;
		}

		// Initialisierungsdaten für den Dialog wurden von Load() bereitgestellt, konnten aber
		// noch nicht an diesen weitergereicht werden
		if (m_bHasInitData)
		{
		// Initialisierungsdaten jetzt an den Dialog weiterreichen
		HRESULT	hr = m_pRegOperDlg->SetSelectedInfo (&m_caSelInfo, IsNoShow());

			if (FAILED(hr)) _com_issue_error(hr);
		}

		if (NULL != puiCnt) 
			*puiCnt = IsNoShow() ? 0 : 1;	// "1" ist die Anzahl der einzuhängenden Pages

	}
	catch (_com_error& e)
	{
		DELETE_OBJ (m_pRegOperDlg);
		if (puiCnt) *puiCnt = 0;
		return _COM_ERROR (e);
	}

	return S_OK;

} // AddConfigPages