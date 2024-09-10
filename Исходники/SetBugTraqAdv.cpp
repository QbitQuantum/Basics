void CSetBugTraqAdv::OnOK()
{
	UpdateData();

	m_provider_clsid = GUID_NULL;

	int index = m_cProviderCombo.GetCurSel();
	if (index != CB_ERR)
	{
		CBugTraqProvider *provider = (CBugTraqProvider *)m_cProviderCombo.GetItemDataPtr(index);
		m_provider_clsid = provider->clsid;
	}

	CComPtr<IBugTraqProvider> pProvider;
	HRESULT hr = pProvider.CoCreateInstance(m_provider_clsid);

	if (FAILED(hr))
	{
		m_tooltips.ShowBalloon(IDC_BUGTRAQPROVIDERCOMBO, IDS_ERR_MISSING_PROVIDER, IDS_ERR_ERROR, TTI_ERROR);
		return;
	}

	VARIANT_BOOL valid;
	ATL::CComBSTR parameters(m_sParameters);
	hr = pProvider->ValidateParameters(GetSafeHwnd(), parameters, &valid);
	if (FAILED(hr))
	{
		ShowEditBalloon(IDC_BUGTRAQPARAMETERS, IDS_ERR_PROVIDER_VALIDATE_FAILED, IDS_ERR_ERROR, TTI_ERROR);
		return;
	}

	if (valid != VARIANT_TRUE)
		return;	// It's assumed that the provider will have done this.

	CResizableStandAloneDialog::OnOK();
}