int EDT_CSP_ReadParam(HCRYPTPROV hProv,DWORD dwParam)
{
	int iRetVal = EDT_OK;
	BYTE *pbData = NULL;
	DWORD dwDataLen = 0;
	DWORD dwFlags = 0;

	if (CryptGetProvParam(hProv, dwParam, NULL, &dwDataLen, dwFlags) == TRUE )
	{
		pbData = (BYTE *)malloc(dwDataLen);
		if(pbData != NULL)
		{
			if (CryptGetProvParam(hProv, dwParam, pbData, &dwDataLen, dwFlags) == TRUE )
			{
				GUID *pTheGuid;
				HCERTSTORE *phCertStore;
				PCCERT_CONTEXT pPrevCertContext = NULL;
				switch(dwParam)
				{
				case PP_SMARTCARD_READER:
					LOG(L"SmartCard Reader: %hs\n",pbData);
					break;
				case PP_SMARTCARD_GUID:
					pTheGuid = (GUID *)pbData;
					LOG(L"SmartCard GUID: ");
					LOG_BYTE_ARRAY(pTheGuid->Data4,sizeof(pTheGuid->Data4));
					break;
				case PP_USER_CERTSTORE:
					phCertStore = (HCERTSTORE*)pbData;
					pPrevCertContext = CertEnumCertificatesInStore(*phCertStore,pPrevCertContext);
					while(pPrevCertContext != NULL)
					{
						LOG(L"Found certificate with length %d\n",pPrevCertContext->cbCertEncoded);
						pPrevCertContext = CertEnumCertificatesInStore(*phCertStore,pPrevCertContext);						
					}
					if ( CertCloseStore(*phCertStore,0) == FALSE )
					{
						LOG_ERROR(L"CertCloseStore failed");
					}
					break;
				default:
					break;
				}
			}
			else
			{
				LOG_LASTERROR(L"CryptGetProvParam failed 2e \n");
			}
			free(pbData);
		}
		else
		{
			LOG_ERROR(L"malloc failed\n");
		}
	}
	else
	{
		LOG_LASTERROR(L"CryptGetProvParam failed\n");
	}
	return iRetVal;
}