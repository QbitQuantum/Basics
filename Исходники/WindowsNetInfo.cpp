	virtual std::wstring DistDomainNameToNT4Name(const std::wstring& domain)
	{
		KLSTD_CHKINPTR(m_fnDsGetDcName);

		std::wstring wstrDNSDomain(domain.begin() + 3, domain.end());

		size_t nPos = wstrDNSDomain.find(L",DC=");
		while(nPos != std::wstring::npos)
		{
			wstrDNSDomain.replace(nPos, 4, L".");
			nPos = wstrDNSDomain.find(L",DC=", nPos + 1);
		}

		PDOMAIN_CONTROLLER_INFO pDomainControllerInfo = NULL;
		DWORD dwResult = m_fnDsGetDcName(NULL, KLSTD_W2T2(wstrDNSDomain.c_str()), NULL, NULL, 
										 DS_DIRECTORY_SERVICE_REQUIRED | DS_IS_DNS_NAME | DS_RETURN_FLAT_NAME,
										 &pDomainControllerInfo);
		if (dwResult != NO_ERROR)
		{
			KLSTD_TRACE3(1, L"DistDomainNameToNT4Name(DN:'%ls', DNS:'%ls')::DsGetDcName - Error '%u'\n", domain.c_str(), wstrDNSDomain.c_str(), dwResult);
			KLSTD_THROW(KLSTD::STDE_FAULT);
		}
		
		std::wstring rc = KLSTD_T2W2(pDomainControllerInfo->DomainName);
		NetApiBufferFree(pDomainControllerInfo);
		return rc;
	}