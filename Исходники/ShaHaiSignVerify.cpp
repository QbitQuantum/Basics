int VerifyDataSignWithHashAlg(const char * userData,  const char * hashAlg, const char * certDataB64, const char * signatureDataB64)
{
	int rv = -1;
	int ulHashAlg = 0;
	HCRYPTHASH hHash = NULL;
	char * pbCert = NULL;
	char * pbSignature = NULL;
	unsigned int ulCert = 0;
	unsigned int ulSignature = 0;
	PCCERT_CONTEXT pCertContext = NULL;  
	HCRYPTPROV hProv = NULL;  
	HCRYPTKEY hPubKey = NULL;  

	{
		ulCert = modp_b64_decode_len(strlen(certDataB64));
		ulSignature = modp_b64_decode_len(strlen(signatureDataB64));

		pbCert = (char *)malloc(ulCert);
		pbSignature =  (char *) malloc(ulSignature);

		if (NULL == pbCert || NULL == pbSignature)
		{
			sprintf(m_errMsg, "%s","memroy less.\n" );
			goto err;
		}

		ulCert = modp_b64_decode(pbCert, certDataB64,strlen(certDataB64));
		ulSignature = modp_b64_decode(pbSignature, signatureDataB64,strlen(signatureDataB64));
	}

	if (0 == strcmp(hashAlg, "MD5"))
	{
		ulHashAlg = CALG_MD5;
	}
	else if (0 == strcmp(hashAlg, "SHA"))
	{
		ulHashAlg = CALG_SHA;
	}
	else if (0 == strcmp(hashAlg, "SHA1"))
	{
		ulHashAlg = CALG_SHA1;
	}
	else if (0 == strcmp(hashAlg, "SHA_256"))
	{
		ulHashAlg = CALG_SHA_256;
	}
	else if (0 == strcmp(hashAlg, "SHA_384"))
	{
		ulHashAlg = CALG_SHA_384;
	}

	pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, (BYTE *)pbCert,ulCert);
	if (!pCertContext)
	{
		sprintf(m_errMsg, "%s","Select Certificate UI failed.\n" );
		goto err;
	}


	//Ò»¡¢»ñµÃÒ»¸öCSP¾ä±ú  
	if(!CryptAcquireContext(  
		&hProv,  
		NULL,           //ÃÜÔ¿ÈÝÆ÷Ãû£¬NULL±íÊ¾Ê¹ÓÃÄ¬ÈÏÈÝÆ÷  
		NULL,           //CSP_NAME  
		PROV_RSA_FULL,  
		0  
		)) 
	{  
		if(!CryptAcquireContext(  
			&hProv,  
			NULL,           //ÃÜÔ¿ÈÝÆ÷Ãû£¬NULL±íÊ¾Ê¹ÓÃÄ¬ÈÏÈÝÆ÷  
			NULL,           //CSP_NAME  
			PROV_RSA_FULL,  
			CRYPT_NEWKEYSET //´´½¨ÃÜÔ¿ÈÝÆ÷  
			))
		{
			sprintf(m_errMsg, "%s","CryptAcquireContext fail.\n");
			goto err;
		}
	}  


	if(CryptImportPublicKeyInfo(
		hProv,
		X509_ASN_ENCODING,
		&(pCertContext->pCertInfo->SubjectPublicKeyInfo),
		&hPubKey
		))
	{
		sprintf(m_errMsg,"CryptImportPublicKeyInfo OK. \n");
	}
	else
	{
		sprintf(m_errMsg,"Error CryptImportPublicKeyInfo.\n");
		goto err;
	}

	//if(CryptImportKey(hProv,pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData, pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData, NULL, 0, &hPubKey))
	//{
	//	sprintf(m_errMsg,"CryptImportKey OK. \n");
	//}
	//else
	//{
	//	sprintf(m_errMsg,"Error CryptImportKey.\n");
	//	goto err;
	//}

	if(CryptCreateHash(
		hProv, 
		ulHashAlg, 
		0, 
		0, 
		&hHash)) 
	{
		sprintf(m_errMsg, "%s","An empty hash object has been created. \n");
	}
	else
	{
		sprintf(m_errMsg, "%s","Error during CryptBeginHash!\n");
		goto err;
	}


	//--------------------------------------------------------------------
	//  This code assumes that the handle of a cryptographic context 
	//  has been acquired and that a hash object has been created 
	//  and its handle (hHash) is available.
	if(CryptHashData(
		hHash, 
		(unsigned char *)userData, 
		strlen(userData), 
		0)) 
	{
		sprintf(m_errMsg, "%s","The data buffer has been added to the hash.\n");
	}
	else
	{
		sprintf(m_errMsg, "%s","Error during CryptHashData.\n");
		goto err;
	}

	if(CryptVerifySignature(hHash, (const BYTE *)pbSignature, ulSignature,hPubKey,NULL,0))
	{
		sprintf(m_errMsg,"verify OK.\n");
	}
	else
	{
		sprintf(m_errMsg,"Error during CryptVerifySignature.\n");
		goto err;
	}

	rv = 0;

err:
	if(hHash) 
	{
		CryptDestroyHash(hHash);
	}

	if (pbSignature)
	{
		free(pbSignature);
	}

	if (pbCert)
	{
		free(pbCert);
	}

	if (pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
	}

	if(hProv)  
	{
		CryptReleaseContext(hProv,0);  
	}


	return rv;
}