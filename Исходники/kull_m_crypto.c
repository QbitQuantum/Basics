BOOL kull_m_crypto_pkcs5_pbkdf2_hmac(DWORD calgid, LPCVOID password, DWORD passwordLen, LPCVOID salt, DWORD saltLen, DWORD iterations, BYTE *key, DWORD keyLen)
{
	BOOL status = FALSE;
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	DWORD sizeHmac, count, i, j, r;
	PBYTE asalt, obuf, d1, d2;

	if(CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
	{
		if(CryptCreateHash(hProv, calgid, 0, 0, &hHash))
		{
			if(CryptGetHashParam(hHash, HP_HASHVAL, NULL, &sizeHmac, 0))
			{
				if(asalt = (PBYTE) LocalAlloc(LPTR, saltLen + 4))
				{
					if(obuf = (PBYTE) LocalAlloc(LPTR, sizeHmac))
					{
						if(d1 = (PBYTE) LocalAlloc(LPTR, sizeHmac))
						{
							if(d2 = (PBYTE) LocalAlloc(LPTR, sizeHmac))
							{
								status = TRUE;
								RtlCopyMemory(asalt, salt, saltLen);
								for (count = 1; keyLen > 0; count++)
								{
									*(PDWORD) (asalt + saltLen) = _byteswap_ulong(count);
									kull_m_crypto_hmac(calgid, password, passwordLen, asalt, saltLen + 4, d1, sizeHmac);
									RtlCopyMemory(obuf, d1, sizeHmac);
									for (i = 1; i < iterations; i++)
									{
										kull_m_crypto_hmac(calgid, password, passwordLen, d1, sizeHmac, d2, sizeHmac);
										RtlCopyMemory(d1, d2, sizeHmac);
										for (j = 0; j < sizeHmac; j++)
											obuf[j] ^= d1[j];
									}
									r = KIWI_MINIMUM(keyLen, sizeHmac);
									RtlCopyMemory(key, obuf, r);
									key += r;
									keyLen -= r;
								}
								LocalFree(d2);
							}
							LocalFree(d1);
						}
						LocalFree(obuf);
					}
					LocalFree(asalt);
				}
			}
			CryptDestroyHash(hHash);
		}
		CryptReleaseContext(hProv, 0);
	}
	return status;
}