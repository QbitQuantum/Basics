DWORD ImportCertificate(CK_BYTE* certData, DWORD certSize, CK_BYTE* cardSerialNumber, CK_ULONG cardSerialNumberLen)
{
	PCCERT_CONTEXT		pCertContext = NULL;
	DWORD				dwRet = 0;
	// ------------------------------------------------------------
	// create the certificate context with the certificate raw data
	// ------------------------------------------------------------
	pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, certData,certSize);

	if( pCertContext == NULL )
	{
		dwRet = GetLastError();
		if (dwRet == E_INVALIDARG)
			printf("ImportCertificates: Unable to create certificate context. The certificate encoding type is not supported.Error code: %d.\n",dwRet);
		else
			printf("ImportCertificates: Unable to create certificate context. Error code: %d.\n",dwRet);
	}
	else
	{
		unsigned char KeyUsageBits = 0; // Intended key usage bits copied to here.
		CertGetIntendedKeyUsage(X509_ASN_ENCODING, pCertContext->pCertInfo, &KeyUsageBits, 1);
		// ----------------------------------------------------------------------
		// Only store the context of the certificates with usages for an end-user
		// i.e. no CA or root certificates
		// ----------------------------------------------------------------------
		if((KeyUsageBits & CERT_KEY_CERT_SIGN_KEY_USAGE) == CERT_KEY_CERT_SIGN_KEY_USAGE)
		{
			dwRet = StoreAuthorityCert (pCertContext, KeyUsageBits);
		}
		else
		{
			dwRet = StoreUserCert (pCertContext, KeyUsageBits, cardSerialNumber, cardSerialNumberLen);
		}
		if (pCertContext)
			CertFreeCertificateContext(pCertContext);
	}
	return dwRet;
}