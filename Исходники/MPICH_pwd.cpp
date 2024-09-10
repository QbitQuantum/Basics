BOOL SetupCryptoClient()
{
	// Ensure that the default cryptographic client is set up.
	HCRYPTPROV hProv;
	HCRYPTKEY hKey;
	int nError;
	
	// Attempt to acquire a handle to the default key container.
	//if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, 0))
	if (!CryptAcquireContext(&hProv, "MPICH", MS_DEF_PROV, PROV_RSA_FULL, 0))
	{
		// Some sort of error occured, create default key container.
		//if (!CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
		if (!CryptAcquireContext(&hProv, "MPICH", MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET))
		{
			// Error creating key container!
			nError = GetLastError();
			printf("SetupCryptoClient:CryptAcquireContext(...) failed, error: %d\n", nError);
			return FALSE;
		}
	}

	// Attempt to get handle to signature key.
	if (!CryptGetUserKey(hProv, AT_SIGNATURE, &hKey))
	{
		if ((nError = GetLastError()) == NTE_NO_KEY)
		{
			// Create signature key pair.
			if (!CryptGenKey(hProv, AT_SIGNATURE, 0, &hKey))
			{
				// Error during CryptGenKey!
				nError = GetLastError();
				CryptReleaseContext(hProv, 0);
				printf("SetupCryptoClient:CryptGenKey(...) failed, error: %d\n", nError);
				return FALSE;
			}
			else
			{
				CryptDestroyKey(hKey);
			}
		}
		else 
		{
			// Error during CryptGetUserKey!
			CryptReleaseContext(hProv, 0);
			printf("SetupCryptoClient:CryptGetUserKey(...) failed, error: %d\n", nError);
			return FALSE;
		}
	}

	// Attempt to get handle to exchange key.
	if (!CryptGetUserKey(hProv,AT_KEYEXCHANGE,&hKey))
	{
		if ((nError = GetLastError()) == NTE_NO_KEY)
		{
			// Create key exchange key pair.
			if (!CryptGenKey(hProv,AT_KEYEXCHANGE,0,&hKey))
			{
				// Error during CryptGenKey!
				nError = GetLastError();
				CryptReleaseContext(hProv, 0);
				printf("SetupCryptoClient:CryptGenKey(...) failed, error: %d\n", nError);
				return FALSE;
			}
			else
			{
				CryptDestroyKey(hKey);
			}
		}
		else
		{
			// Error during CryptGetUserKey!
			CryptReleaseContext(hProv, 0);
			printf("SetupCryptoClient:CryptGetUserKey(...) failed, error: %d\n", nError);
			return FALSE;
		}
	}

	CryptReleaseContext(hProv, 0);
	return TRUE;
}