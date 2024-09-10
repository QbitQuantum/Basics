void 
get_cert_time_left(
	char				*realm,
	CTimeSpan			*ptimeLeft
)
{
	HCERTSTORE			hStoreHandle		= NULL;
	PCCERT_CONTEXT		pCertContext		= NULL;      
	PCCERT_CONTEXT		prev_pCertContext	= NULL;      
	DWORD				dwCertEncodingType	= X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
	DWORD				dwAddDisposition	= CERT_STORE_ADD_REPLACE_EXISTING;
	DWORD				dwFindFlags			= 0;
# define				OID_KCA_AUTHREALM	"1.3.6.1.4.1.250.42.1"
	DWORD				dwFindType			= CERT_FIND_ANY;
	CERT_INFO			*pCertInfo			= NULL;
	PCERT_EXTENSION		pCertExt			= NULL;
	CRYPT_OBJID_BLOB	*p					= NULL;
	int					i					= 0;
	char				tmpRealm[250]		= { 0 };
	CTime				startTime			= 0;
	CTime				endTime				= 0;



	memset(ptimeLeft, 0, sizeof(*ptimeLeft));

	if (!realm || !strlen(realm))
		return;

	//--------------------------------------------------------------------
	// Open a store as the source of the certificates to be deleted and added

	if(!(hStoreHandle = CertOpenSystemStore(
			0,
			MY_STORE)))
	{
		HandleError("get_cert_time_left: Strange.  Unable to access your place in the Registry for certificates");
		goto EXIT_RTN;
	}


	// Find first MY store cert issued by our Certificate Authority

	while ((pCertContext = CertFindCertificateInStore(
						hStoreHandle,					// in
						dwCertEncodingType,				// in
						dwFindFlags,					// in
						dwFindType,						// in
						NULL,							// in
						prev_pCertContext				// in
						)))
	{
		if (pCertInfo = pCertContext->pCertInfo)
			for (i = pCertInfo->cExtension; i; i--)
			{
				pCertExt = &pCertInfo->rgExtension[i-1];
				if (!strcmp(pCertExt->pszObjId, OID_KCA_AUTHREALM))
				{
					log_printf("get_cert_time_left: Found KCA_AUTHREALM Extension\n");

					p = &pCertExt->Value;
					memcpy(tmpRealm, &p->pbData[2], p->cbData-2);
					tmpRealm[p->cbData-2] ='\0';
					log_printf("get_cert_time_left:    value is: '%s'\n", tmpRealm);

					/* only match if realm of current TGT matches AuthRealm of this cert */
					if (realm && !strcmp(realm, tmpRealm))
					{
						// It matches, determine remaining certificate's remaining minutes
						startTime	= CTime::GetCurrentTime();
						endTime		= pCertContext->pCertInfo->NotAfter;
						*ptimeLeft	= endTime - startTime;

						goto EXIT_RTN;
					}
				}
			}

		prev_pCertContext = pCertContext;
	}

EXIT_RTN:
	if ((prev_pCertContext != pCertContext) && pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
		pCertContext = NULL;
	}

	if (pCertContext)
		CertFreeCertificateContext(pCertContext);

	if(hStoreHandle &&!CertCloseStore(
							hStoreHandle,
#ifdef DEBUG
							CERT_CLOSE_STORE_CHECK_FLAG
#else // !DEBUG
							CERT_CLOSE_STORE_FORCE_FLAG
#endif // ! DEBUG
			))
	{
		log_printf("get_cert_time_left: The store was closed, but certificates still in use.\n");
	}
} // get_cert_time_left