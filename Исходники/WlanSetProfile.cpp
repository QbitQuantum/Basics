//
// Retrieve the thumbprint of the certificate
//
DWORD GetCertificate(IN WCHAR* pwcTrustRootCA, 
					 IN PBYTE  pbCertHash,
					 IN DWORD* pcbCertHash)
{
	HCERTSTORE		hCertStore;
	WCHAR			*pwcSubjectName;
	DWORD			cwcSubjectName; 
	PBYTE			pbSHA1;
	DWORD			cbSHA1;
	PCCERT_CONTEXT	pCertContext = NULL;
	DWORD			dwRet;

	dwRet = NO_ERROR;

	if( ( hCertStore = CertOpenStore( CERT_STORE_PROV_SYSTEM, 
		X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
		( HCRYPTPROV ) NULL,
		CERT_SYSTEM_STORE_LOCAL_MACHINE,
		L"ROOT" ) ) )
	{
		BOOL	bFoundCert = FALSE;

		while( ( pCertContext = CertEnumCertificatesInStore( hCertStore,
			pCertContext ) ) &&
			bFoundCert == FALSE )
		{
			if( ( cwcSubjectName  = CertGetNameString( pCertContext,
				CERT_NAME_SIMPLE_DISPLAY_TYPE,
				0, 
				NULL,
				NULL,
				0 ) ) > 0 )
			{
				if( ( pwcSubjectName = ( WCHAR* ) malloc( cwcSubjectName * sizeof( WCHAR ) ) ) )
				{
					if( CertGetNameStringW( pCertContext,
						CERT_NAME_SIMPLE_DISPLAY_TYPE,
						0, 
						NULL,
						pwcSubjectName,
						cwcSubjectName ) > 0 )
					{
						//printf("Found the certificate [%ws] in the system store\n", pwcSubjectName);

						if ( wcscmp(pwcTrustRootCA, pwcSubjectName) == 0)
						{
							bFoundCert = TRUE;

							// Retrieve information on the property by first getting the property size.
							if(CertGetCertificateContextProperty( pCertContext, 
								CERT_SHA1_HASH_PROP_ID , // work fine on XP 
								NULL, 
								&cbSHA1))
							{
								// Use the size to allocate the memory for the property
								if ( pbSHA1 = (BYTE *) malloc(cbSHA1 * sizeof(BYTE) ) )
								{
									// Retrieve HASH of the certificate
									if(CertGetCertificateContextProperty( pCertContext, 
										CERT_SHA1_HASH_PROP_ID ,  
										pbSHA1, 
										&cbSHA1))
									{
										memcpy(pbCertHash, pbSHA1, cbSHA1);
										*pcbCertHash = cbSHA1;
									}
									else
									{
										printf("->GetCertificate :: Error retrieving certificate HASH.\n");
										dwRet = ERROR_CANTOPEN;
									}

									free(pbSHA1);

								}
								else
								{
									printf("->GetCertificate :: Error allocating memory.\n");
									dwRet = ERROR_NOT_ENOUGH_MEMORY;
								}
							}
							else
							{
								printf("->GetCertificate :: Error getting certificate property.\n");
								dwRet = ERROR_CANTOPEN;
							}

						} 
					}
					else
					{
						printf("->GetCertificate :: Error getting certificate name string.\n");
						dwRet = ERROR_CANTOPEN;
					}

					free( pwcSubjectName );
					cwcSubjectName = 0;
				}
				else
				{
					printf("->GetCertificate :: Error allocating memory.\n");
					dwRet = ERROR_NOT_ENOUGH_MEMORY;
				}
			}
			else
				dwRet = ERROR_CANTOPEN;
		}

		if( !bFoundCert )
		{
			printf("->GetCertificate :: Error looking for the certificate in the system store.\n");
			dwRet = ERROR_CANTOPEN;
		}

		if( dwRet != NO_ERROR )
		{
			if( pCertContext )
				CertFreeCertificateContext( pCertContext );

		}

		CertCloseStore( hCertStore, CERT_CLOSE_STORE_CHECK_FLAG );
	}
	else
	{
		printf("->GetCertificate :: Error opening system store.\n");
		dwRet = ERROR_CANTOPEN;
	}


	return dwRet;

}