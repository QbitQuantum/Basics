BOOL CPrefConnectServers::OnApply() 
{
	std::vector<CString> HostServers;
	for(int i = 0; i < m_lstServers.GetItemCount(); i++)
	{
		CString HostPort = m_lstServers.GetItemText(i, 0);
		HostPort  += ":" + m_lstServers.GetItemText(i, 1);

		m_pDoc->m_autCache->AddNode(HostPort, false);

		HostServers.push_back(HostPort);
	}

	VARIANT vaNodes;
	VariantInit(&vaNodes);

	vaNodes.vt = VT_ARRAY | VT_BSTR;

	SAFEARRAYBOUND bounds = {HostServers.size(), 0};
	SAFEARRAY* psa = SafeArrayCreate(VT_BSTR, 1, &bounds);

	BSTR* strArray;
	SafeArrayAccessData(psa, reinterpret_cast<void**> (&strArray));

	for(int i = 0; i < HostServers.size(); i++)
		strArray[i] = HostServers[i].AllocSysString();

	SafeArrayUnaccessData(psa);
	vaNodes.parray = psa;

	m_autPrefs->SetHostServers(&vaNodes);
	
	VariantClear(&vaNodes);

	return CPropertyPage::OnApply();
}