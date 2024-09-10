NTSTATUS kuhl_m_token_list_or_elevate(int argc, wchar_t * argv[], BOOL elevate)
{
	KUHL_M_TOKEN_ELEVATE_DATA pData = {NULL, NULL, 0, elevate};
	WELL_KNOWN_SID_TYPE type = WinNullSid;
	PWSTR name, domain;
	PCWSTR strTokenId;
	PPOLICY_DNS_DOMAIN_INFO pDomainInfo = NULL;

	kull_m_string_args_byName(argc, argv, L"user", &pData.pUsername, NULL);

	if(kull_m_string_args_byName(argc, argv, L"id", &strTokenId, NULL))
	{
		pData.tokenId = wcstoul(strTokenId, NULL, 0);
	}
	else if(kull_m_string_args_byName(argc, argv, L"domainadmin", NULL, NULL))
	{
		type = WinAccountDomainAdminsSid;
		if(!kull_m_net_getCurrentDomainInfo(&pDomainInfo))
			PRINT_ERROR_AUTO(L"kull_m_local_domain_user_getCurrentDomainSID");
	}
	else if(kull_m_string_args_byName(argc, argv, L"admin", NULL, NULL))
		type = WinBuiltinAdministratorsSid;
	else if((elevate && !pData.pUsername) || kull_m_string_args_byName(argc, argv, L"system", NULL, NULL))
	{
		type = WinLocalSystemSid;
		if(pData.pUsername)
		{
			PRINT_ERROR(L"No username available when SYSTEM\n");
			pData.pUsername = NULL;
		}
	}

	if(!elevate || pData.tokenId || type || pData.pUsername)
	{
		kprintf(L"Token Id  : %u\nUser name : %s\nSID name  : ", pData.tokenId, pData.pUsername ? pData.pUsername : L"");
		if(type)
		{
			if(kull_m_net_CreateWellKnownSid(type, pDomainInfo ? pDomainInfo->Sid : NULL, &pData.pSid))
			{
				if(kull_m_token_getNameDomainFromSID(pData.pSid, &name, &domain, NULL))
				{
					kprintf(L"%s\\%s\n", domain, name);
					LocalFree(name);
					LocalFree(domain);
				} else PRINT_ERROR_AUTO(L"kull_m_token_getNameDomainFromSID");
			}
			else PRINT_ERROR_AUTO(L"kull_m_local_domain_user_CreateWellKnownSid");
		}
		else kprintf(L"\n");
		kprintf(L"\n");
		
		if(!elevate || pData.tokenId || pData.pSid || pData.pUsername)
			kull_m_token_getTokens(kuhl_m_token_list_or_elevate_callback, &pData);
		
		if(pData.pSid)
			LocalFree(pData.pSid);
		
		if(pDomainInfo)
			LsaFreeMemory(pDomainInfo);
	}
	return STATUS_SUCCESS;
}