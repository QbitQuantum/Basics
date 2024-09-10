///
/// Disabled all enhanced key usages for the specified certificate.
///
void RemoveAllEnhancedKeyUsages(LPTSTR pszStoreName, LPTSTR szSubjectName)
{
	HANDLE hStoreHandle = NULL;
	PCCERT_CONTEXT pCertContext = NULL;


	// Open Store.
	if (hStoreHandle = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, CERT_SYSTEM_STORE_LOCAL_MACHINE, pszStoreName))
	{
		_tprintf(TEXT("[i] Successfully opened certificate store '%s'\n"), pszStoreName);
	}
	else
	{
		ErrorHandler("Failed to open certificate store");
		exit(1);
	}

	//
	// Iterate over certificates in this store.
	while (pCertContext = CertEnumCertificatesInStore(hStoreHandle, pCertContext))
	{
		DWORD cbSize;
		LPTSTR pszName;

		// Get the Certificate Subject Name.
		cbSize = CertNameToStr(pCertContext->dwCertEncodingType, &(pCertContext->pCertInfo->Subject), CERT_OID_NAME_STR, NULL, 0);
		if (1 == cbSize)
		{
			ErrorHandler("Failed to return the subject name of the certificate.");
		}
		if (!(pszName = (LPTSTR)malloc(cbSize * sizeof(TCHAR))))
		{
			ErrorHandler("Failed to allocate memory");
		}
		if (CertGetNameString(pCertContext, CERT_NAME_SIMPLE_DISPLAY_TYPE, 0, NULL, pszName, cbSize))
		{
//			_tprintf(TEXT("%s\n"), pszName);
		}
		else
		{
			ErrorHandler("CertGetNameString failed");
		}

		//
		// Is this the certificate we're looking for?
		if (_tcscmp(pszName, szSubjectName) == 0)
		{
			_tprintf(TEXT("[i] Located certificate %s\n"), pszName);
			PCERT_ENHKEY_USAGE pEKeyUsage = NULL;

			if (!(pEKeyUsage = (PCERT_ENHKEY_USAGE)CryptMemAlloc(sizeof(CERT_ENHKEY_USAGE))))
			{
				ErrorHandler("Failed to allocate memory");
			}
			if (CertSetEnhancedKeyUsage(pCertContext, pEKeyUsage))
			{
				_tprintf(TEXT("[i] Removed EKU\n"));
			}
			else
			{
				ErrorHandler("CertSetEnhancedKeyUsage Failed");
			}
			CryptMemFree(pEKeyUsage);
		}
		free(pszName);
	}

	// Clean Up
	if (pCertContext)
		CertFreeCertificateContext(pCertContext);
	if (hStoreHandle)
	{
		if (!CertCloseStore(hStoreHandle, 0))
			ErrorHandler("Failed CertCloseStorn");
	}
}