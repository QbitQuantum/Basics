PCCERT_CONTEXT SslSocketCpServer::CreateOurCertificate()
{
	// CertCreateSelfSignCertificate(0,&SubjectName,0,0,0,0,0,0);
	HRESULT hr = 0;
	HCRYPTPROV hProv = NULL;
	PCCERT_CONTEXT p = 0;
	HCRYPTKEY hKey = 0;
	CERT_NAME_BLOB sib = { 0 };
	BOOL AX = 0;

	// Step by step to create our own certificate
	try
	{
		// Create the subject
		char cb[1000] = { 0 };
		sib.pbData = (BYTE*)cb;
		sib.cbData = 1000;
		wchar_t*	szSubject = L"CN=Certificate";
		if (!CertStrToName(CRYPT_ASN_ENCODING, szSubject, 0, 0, sib.pbData, &sib.cbData, NULL))
			throw;


		// Acquire Context
		wchar_t* pszKeyContainerName = L"Container";

		if (!CryptAcquireContext(&hProv, pszKeyContainerName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET | CRYPT_MACHINE_KEYSET))
		{
			hr = GetLastError();
			if (GetLastError() == NTE_EXISTS)
			{
				if (!CryptAcquireContext(&hProv, pszKeyContainerName, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_MACHINE_KEYSET))
				{
					throw;
				}
			}
			else
				throw;
		}

		// Generate KeyPair
		if (!CryptGenKey(hProv, AT_KEYEXCHANGE, CRYPT_EXPORTABLE, &hKey))
			throw;

		// Generate the certificate
		CRYPT_KEY_PROV_INFO kpi = { 0 };
		kpi.pwszContainerName = pszKeyContainerName;
		kpi.pwszProvName = MS_DEF_PROV;
		kpi.dwProvType = PROV_RSA_FULL;
		kpi.dwFlags = CERT_SET_KEY_CONTEXT_PROP_ID;
		kpi.dwKeySpec = AT_KEYEXCHANGE;

		SYSTEMTIME et;
		GetSystemTime(&et);
		et.wYear += 1;

		CERT_EXTENSIONS exts = { 0 };
		p = CertCreateSelfSignCertificate(hProv, &sib, 0, &kpi, NULL, NULL, &et, &exts);

		AX = CryptFindCertificateKeyProvInfo(p, CRYPT_FIND_MACHINE_KEYSET_FLAG, NULL);
		hCS = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, 0, CERT_STORE_CREATE_NEW_FLAG, 0);
		/*AX = CertAddCertificateContextToStore(hCS,p,CERT_STORE_ADD_NEW,0);
		AX = CryptFindCertificateKeyProvInfo(p,CRYPT_FIND_MACHINE_KEYSET_FLAG,NULL);*/
	}

	catch (...)
	{
	}

	if (hKey)
		CryptDestroyKey(hKey);
	hKey = 0;

	if (hProv)
		CryptReleaseContext(hProv, 0);
	hProv = 0;
	return p;
}