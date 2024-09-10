void __cdecl main(void)
{
	//-------------------------------------------------------------------
	// Pointer to a certificate. 

	PCCERT_CONTEXT pCertContext = NULL; 

	//-------------------------------------------------------------------
	// Declare and Initialize variables 
	DWORD cbData = 0;
	BYTE* pbData = NULL;
	LPWSTR pwszMimeType = NULL;

	//-------------------------------------------------------------------
	// Use the helper function to get the certificate which has a logotype
	// extension

	pCertContext = MyGetCertificate();

	if(pCertContext == NULL)
	{
		MyHandleError( L"The certificate with logotype extension not found.\n");
		goto done;
	}

	//-------------------------------------------------------------------
	// This API allocates memory for pbData and pwszMimeType which has to be freed 
	// by calling CryptMemFree()
	if(!CertRetrieveLogoOrBiometricInfo(
					pCertContext,
					CERT_RETRIEVE_ISSUER_LOGO,	  
					0,                            // Retrieval Flags
					RETRIEVAL_TIMEOUT,            // TimeOut in milliseconds
					0,                            // dwFlags : reserved
					NULL,                         // Reserved for future use
					&pbData,					   
					&cbData,
					&pwszMimeType
					))
	{
		MyHandleError( L"CertRetrieveLogoOrBiometricInfo failed.\n");
	}
	else
	{
		wprintf( L"Successfully retrieved logo information \n");  
	}
	//-------------------------------------------------------------------
	// Clean up. 
done:
	if(pwszMimeType)
		CryptMemFree(pwszMimeType);

	if(pbData)
		CryptMemFree(pbData);

	if(pCertContext)
		CertFreeCertificateContext(pCertContext);

} //end Main