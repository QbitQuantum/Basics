HRESULT DocProvHelper::VerifyODMAProvider(CStdString lpszDmsId)
{
	if(m_mapODMAtoWS.size() == 0)
	{
		std::vector<CStdString> docProvs = RegistryHandler::GetAvailableDocProvs(true);
		std::vector<CStdString>::iterator it;
		for (it = docProvs.begin(); it != docProvs.end(); it++)
		{
			CStdString sWsId = Workshare::OptionApi::GetString(L"DocumentProviders", *it, L"ServerID");
			CStdString sOdmaId = Workshare::OptionApi::GetString(L"DocumentProviders", *it, L"OdmaDmsID");

			if(sOdmaId.length())
				m_mapODMAtoWS[sOdmaId] = sWsId;
		}
	}

	return S_OK;
}