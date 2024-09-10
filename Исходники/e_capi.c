CRYPT_KEY_PROV_INFO *capi_get_prov_info(CAPI_CTX *ctx, PCCERT_CONTEXT cert)
	{
	DWORD len;
	CRYPT_KEY_PROV_INFO *pinfo;
	
	if(!CertGetCertificateContextProperty(cert, CERT_KEY_PROV_INFO_PROP_ID, NULL, &len))
		return NULL;
	pinfo = OPENSSL_malloc(len);
	if (!pinfo)
		{
		CAPIerr(CAPI_F_CAPI_GET_PROV_INFO, ERR_R_MALLOC_FAILURE);
		return NULL;
		}
	if(!CertGetCertificateContextProperty(cert, CERT_KEY_PROV_INFO_PROP_ID, pinfo, &len))
		{
		CAPIerr(CAPI_F_CAPI_GET_PROV_INFO, CAPI_R_ERROR_GETTING_KEY_PROVIDER_INFO);
		capi_addlasterror();
		OPENSSL_free(pinfo);
		return NULL;
		}
	return pinfo;
	}