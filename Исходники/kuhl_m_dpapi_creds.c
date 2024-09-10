BOOL kuhl_m_dpapi_vault_key_type(PKULL_M_CRED_VAULT_CREDENTIAL_ATTRIBUTE attribute, HCRYPTPROV hProv, BYTE aes128[AES_128_KEY_SIZE], BYTE aes256[AES_256_KEY_SIZE], HCRYPTKEY *hKey, BOOL *isAttr)
{
	BOOL status = FALSE;
	DWORD mode = CRYPT_MODE_CBC, calgId, keyLen;
	LPCVOID key;

	*isAttr = attribute->id && (attribute->id < 100);
	if(*isAttr)
	{
		calgId = CALG_AES_128;
		key = aes128;
		keyLen = AES_128_KEY_SIZE;
		
	}
	else
	{
		calgId = CALG_AES_256;
		key = aes256;
		keyLen = AES_256_KEY_SIZE;
	}

	if(status = kull_m_crypto_hkey(hProv, calgId, key, keyLen, 0, hKey, NULL))
	{
		CryptSetKeyParam(*hKey, KP_MODE, (LPCBYTE) &mode, 0);
		if(attribute->szIV && attribute->IV)
			CryptSetKeyParam(*hKey, KP_IV, attribute->IV, 0);
	}
	return status;
}