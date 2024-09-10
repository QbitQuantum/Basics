void kuhl_m_sid_displayMessage(PLDAP ld, PLDAPMessage pMessage)
{
	PLDAPMessage pEntry;
	PWCHAR pAttribute, name, domain;
	BerElement* pBer = NULL;
	PBERVAL *pBerVal;
	DWORD i;
	SID_NAME_USE nameUse;

	for(pEntry = ldap_first_entry(ld, pMessage); pEntry; pEntry = ldap_next_entry(ld, pEntry))
	{
		kprintf(L"\n%s\n", ldap_get_dn(ld, pEntry));
		for(pAttribute = ldap_first_attribute(ld, pEntry, &pBer); pAttribute; pAttribute = ldap_next_attribute(ld, pEntry, pBer))
		{
			kprintf(L"  %s: ", pAttribute);
			if(pBerVal = ldap_get_values_len(ld, pEntry, pAttribute))
			{
				if(
					(_wcsicmp(pAttribute, L"name") == 0) ||
					(_wcsicmp(pAttribute, L"sAMAccountName") == 0)
					)
				{
					kprintf(L"%*S\n", pBerVal[0]->bv_len, pBerVal[0]->bv_val);
				}
				else if((_wcsicmp(pAttribute, L"objectSid") == 0))
				{
					kull_m_string_displaySID(pBerVal[0]->bv_val);
					kprintf(L"\n");
				}
				else if((_wcsicmp(pAttribute, L"objectGUID") == 0))
				{
					kull_m_string_displayGUID((LPGUID) pBerVal[0]->bv_val);
					kprintf(L"\n");
				}
				else 
				{
					for(i = 0; pBerVal[i]; i++)
					{
						kprintf(L"\n   [%u] ", i);
						if((_wcsicmp(pAttribute, L"sIDHistory") == 0))
						{
							kull_m_string_displaySID(pBerVal[i]->bv_val);
							if(kull_m_token_getNameDomainFromSID(pBerVal[i]->bv_val, &name, &domain, &nameUse, NULL))
							{
								kprintf(L" ( %s -- %s\\%s )", kull_m_token_getSidNameUse(nameUse), domain, name);
								LocalFree(name);
								LocalFree(domain);
							}
						}
						else kull_m_string_wprintf_hex(pBerVal[i]->bv_val, pBerVal[i]->bv_len, 1);
					}
					kprintf(L"\n");
				}
				ldap_value_free_len(pBerVal);
			}
			ldap_memfree(pAttribute);
		}
		if(pBer)
			ber_free(pBer, 0);
	}
}