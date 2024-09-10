static PCCERT_CONTEXT
xmlSecMSCryptoKeysStoreFindCert(xmlSecKeyStorePtr store, const xmlChar* name, 
			       xmlSecKeyInfoCtxPtr keyInfoCtx) {
    const char* storeName;
    HCERTSTORE hStoreHandle = NULL;
    PCCERT_CONTEXT pCertContext = NULL;

    xmlSecAssert2(xmlSecKeyStoreCheckId(store, xmlSecMSCryptoKeysStoreId), NULL);
    xmlSecAssert2(name != NULL, NULL);
    xmlSecAssert2(keyInfoCtx != NULL, NULL);

    storeName = xmlSecMSCryptoAppGetCertStoreName();
    if(storeName == NULL) {
	storeName = XMLSEC_MSCRYPTO_APP_DEFAULT_CERT_STORE_NAME;
    }

    hStoreHandle = CertOpenSystemStore(0, storeName);
    if (NULL == hStoreHandle) {
	xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
		    NULL,
		    "CertOpenSystemStore",
		    XMLSEC_ERRORS_R_CRYPTO_FAILED,
		    "storeName=%s",
		    xmlSecErrorsSafeString(storeName));
	return(NULL);
    }

    /* first attempt: search by cert id == name */
    if(pCertContext == NULL) {
	size_t len = xmlStrlen(name) + 1;     
	wchar_t * lpCertID;
	
	/* aleksey todo: shouldn't we call MultiByteToWideChar first to get the buffer size? */
	lpCertID = (wchar_t *)xmlMalloc(sizeof(wchar_t) * len);
	if(lpCertID == NULL) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
			xmlSecErrorsSafeString(xmlSecKeyStoreGetName(store)),
			NULL,
			XMLSEC_ERRORS_R_MALLOC_FAILED,
		    	XMLSEC_ERRORS_NO_MESSAGE);
	    CertCloseStore(hStoreHandle, 0);
	    return(NULL);
	}
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, -1, lpCertID, len);
	
	pCertContext = CertFindCertificateInStore(
	    hStoreHandle,
	    X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
	    0,
	    CERT_FIND_SUBJECT_STR,
	    lpCertID,
	    NULL);
	xmlFree(lpCertID);
    }

    /* We don't give up easily, now try to fetch the cert with a full blown 
     * subject dn
     */
    if (NULL == pCertContext) {
	BYTE* bdata;
	DWORD len;
	
	bdata = xmlSecMSCryptoCertStrToName(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
					    name, 
					    CERT_OID_NAME_STR,
					    &len);
	if(bdata != NULL) {
	    CERT_NAME_BLOB cnb;
    
	    cnb.cbData = len;
    	    cnb.pbData = bdata;
	    
	    pCertContext = CertFindCertificateInStore(hStoreHandle,
				X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
				0,
				CERT_FIND_SUBJECT_NAME,
				&cnb,
				NULL);
	    xmlFree(bdata);
	}
    }
	    
    /* We don't give up easily, now try to fetch the cert with a full blown 
     * subject dn, and try with a reversed dn
     */
    if (NULL == pCertContext) {
	BYTE* bdata;
	DWORD len;
	
	bdata = xmlSecMSCryptoCertStrToName(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
					    name, 
					    CERT_OID_NAME_STR | CERT_NAME_STR_REVERSE_FLAG,
					    &len);
	if(bdata != NULL) {
	    CERT_NAME_BLOB cnb;
    
	    cnb.cbData = len;
    	    cnb.pbData = bdata;
	    
	    pCertContext = CertFindCertificateInStore(hStoreHandle,
				X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
				0,
				CERT_FIND_SUBJECT_NAME,
				&cnb,
				NULL);
	    xmlFree(bdata);
	}
    }

    /*
     * Try ro find certificate with name="Friendly Name"
     */
    if (NULL == pCertContext) {
      DWORD dwPropSize;
      PBYTE pbFriendlyName;
      PCCERT_CONTEXT pCertCtxIter = NULL;
      size_t len = xmlStrlen(name) + 1;     
      wchar_t * lpFName;
	
      lpFName = (wchar_t *)xmlMalloc(sizeof(wchar_t) * len);
      if(lpFName == NULL) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
			xmlSecErrorsSafeString(xmlSecKeyStoreGetName(store)),
			NULL,
			XMLSEC_ERRORS_R_MALLOC_FAILED,
		    	XMLSEC_ERRORS_NO_MESSAGE);
	    CertCloseStore(hStoreHandle, 0);
	    return(NULL);
      }
      MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, name, -1, lpFName, len);
      
      while (pCertCtxIter = CertEnumCertificatesInStore(hStoreHandle, pCertCtxIter)) {
	if (TRUE != CertGetCertificateContextProperty(pCertCtxIter,
						      CERT_FRIENDLY_NAME_PROP_ID,
						      NULL,
						      &dwPropSize)) {
	  continue;
	}

	pbFriendlyName = xmlMalloc(dwPropSize);
	if(pbFriendlyName == NULL) {
	    xmlSecErr_a_ignorar5(XMLSEC_ERRORS_HERE,
			xmlSecErrorsSafeString(xmlSecKeyStoreGetName(store)),
			NULL,
			XMLSEC_ERRORS_R_MALLOC_FAILED,
		    	XMLSEC_ERRORS_NO_MESSAGE);
	    xmlFree(lpFName);
	    CertCloseStore(hStoreHandle, 0);
	    return(NULL);
	}
	if (TRUE != CertGetCertificateContextProperty(pCertCtxIter,
						      CERT_FRIENDLY_NAME_PROP_ID,
						      pbFriendlyName,
						      &dwPropSize)) {
	  xmlFree(pbFriendlyName);
	  continue;
	}

	/* Compare FriendlyName to name */
	if (!wcscmp(lpFName, (const wchar_t *)pbFriendlyName)) {
	  pCertContext = pCertCtxIter;
	  xmlFree(pbFriendlyName);
	  break;
	}
	xmlFree(pbFriendlyName);
      }

      xmlFree(lpFName);
    }

    /* We could do the following here: 
     * It would be nice if we could locate the cert with issuer name and
     * serial number, the given keyname can be something like this:
     * 'serial=1234567;issuer=CN=ikke, C=NL'
     * to be implemented by the first person who reads this, and thinks it's
     * a good idea :) WK
     */     

    /* OK, I give up, I'm gone :( */
    
    /* aleksey todo: is it a right idea to close store if we have a handle to 
     * a cert in this store? */
    CertCloseStore(hStoreHandle, 0);
    return(pCertContext);
}