void rsautil_decryptFileWithKey(HCRYPTPROV hProv, HCRYPTKEY hUserRsaKey, HCRYPTKEY hFreeRsaKey, LPWSTR filename)
{
	HCRYPTKEY hUserFileAesKey;
	PWANA_FORMAT pbEncData;
	PWCHAR p;
	DWORD cbEncData, cbRealDataLen, cryptoMode = CRYPT_MODE_CBC;
	kprintf(L"File %s -- ", filename);
	if(kull_m_file_readData(filename, (PBYTE *) &pbEncData, &cbEncData))
	{
		if(p = wcsrchr(filename, L'.'))
		{
			*p = L'\0'; // 'delete' the WNCRY extension
			if(pbEncData->magic == WANA_MAGIC)
			{
				if(CryptDecrypt(hUserRsaKey, 0, TRUE, 0, pbEncData->key, &pbEncData->enc_keysize) || (hFreeRsaKey ? CryptDecrypt(hFreeRsaKey, 0, TRUE, 0, pbEncData->key, &pbEncData->enc_keysize) : FALSE)) // decrypt the raw AES key from your RSA key (from userone of free if present)
				{
					if(SIMPLE_kull_m_crypto_hkey(hProv, CALG_AES_128, pbEncData->key, pbEncData->enc_keysize, 0, &hUserFileAesKey)) // let's make a AES 128 Windows key from raw bytes
					{
						if(CryptSetKeyParam(hUserFileAesKey, KP_MODE, (PBYTE) &cryptoMode, 0)) // we'll do CBC
						{
							cbRealDataLen = cbEncData - FIELD_OFFSET(WANA_FORMAT, data);
							if(CryptDecrypt(hUserFileAesKey, 0, FALSE, 0, pbEncData->data, &cbRealDataLen)) // decrypt final data (padding issue, so 'FALSE' arg)
							{
								if(kull_m_file_writeData(filename, pbEncData->data, (ULONG) pbEncData->qwDataSize))
									kprintf(L"OK\n");
								else PRINT_ERROR_AUTO(L"kull_m_file_writeData");
							}
							else PRINT_ERROR_AUTO(L"CryptDecrypt(AES)");
						}
						CryptDestroyKey(hUserFileAesKey);
					}
				}
				else PRINT_ERROR_AUTO(L"CryptDecrypt(RSA)");
			}
			else PRINT_ERROR(L"ERROR: WANACRY! magic number not found\n");
		}
		else PRINT_ERROR(L"ERROR: no \'.\' at the end of the user file ?\n");
		LocalFree(pbEncData);
	}
	else PRINT_ERROR_AUTO(L"kull_m_file_readData");
}