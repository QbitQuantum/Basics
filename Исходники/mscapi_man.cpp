BOOL MSCAPI_Manager::BuildCertificateChain(HCRYPTPROV provider, OpString &label, OpString &shortname, SSL_ASN1Cert_list &cert)
{
	CERT_PUBLIC_KEY_INFO *pubkey = (CERT_PUBLIC_KEY_INFO *) g_memory_manager->GetTempBuf2k();
	DWORD len;

	label.Empty();
	shortname.Empty();
	cert.Resize(0);

	if(!hMYSystemStore)
		return FALSE;

	len = g_memory_manager->GetTempBuf2kLen();
	if(!CryptExportPublicKeyInfo(provider,  /*AT_SIGNATURE*/ AT_KEYEXCHANGE, (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), pubkey, &len))
	{
		int err0 = GetLastError();
		op_memset(&pubkey, 0, sizeof(pubkey));
		len = g_memory_manager->GetTempBufLen();
		if(!CryptExportPublicKeyInfo(provider, /* AT_KEYEXCHANGE */ AT_SIGNATURE, (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), pubkey, &len))
		{
			int err = GetLastError();
			return FALSE;
		}
	}
		
	PCCERT_CONTEXT cert_item = NULL;
	
	cert_item = CertFindCertificateInStore(hMYSystemStore, (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), 0, CERT_FIND_PUBLIC_KEY, pubkey, cert_item);
	if(!cert_item && hUserDSSystemStore)
		cert_item = CertFindCertificateInStore(hUserDSSystemStore, (X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), 0, CERT_FIND_PUBLIC_KEY, pubkey, cert_item);

	if(!cert_item)
		return FALSE;

	
	len = CertNameToStr((X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), 
		&cert_item->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, NULL, 0);
	

	if(len)
	{
		if(shortname.Reserve(len+1) == NULL)
			return OpStatus::ERR_NO_MEMORY;
		
		len = CertNameToStr((X509_ASN_ENCODING | PKCS_7_ASN_ENCODING), 
			&cert_item->pCertInfo->Subject, CERT_SIMPLE_NAME_STR, shortname.DataPtr(), shortname.Capacity());
	}
	
	cert.Resize(1);
	if(cert.Error())
		return FALSE();
	
	cert[0].Set(cert_item->pbCertEncoded, cert_item->cbCertEncoded);
	
	if(cert.Error() || cert[0].GetLength() == 0)
		return FALSE;

	return TRUE;
}