int CryptoAPI_verify_certificate(X509 *x509)
{
  int ret = -1;
  int len;
  unsigned char *buf = NULL;

  PCCERT_CONTEXT pCertContext = NULL;
  PCCERT_CHAIN_CONTEXT pChainContext = NULL;
  CERT_ENHKEY_USAGE EnhkeyUsage;
  CERT_USAGE_MATCH CertUsage;  
  CERT_CHAIN_PARA ChainPara;

  /* Convert from internal X509 format to DER */
  len = i2d_X509(x509, &buf);
  if (len < 0) {
	SSLerr(SSL_F_SSL_CTX_USE_CERTIFICATE_FILE, ERR_R_ASN1_LIB);
	goto err;
  }

#ifdef __MINGW32_VERSION
    /* MinGW w32api is incomplete when it comes to CryptoAPI, as per version 3.1
     * anyway. This is a hack around that problem. */
    if (crypt32dll == NULL) {
	crypt32dll = LoadLibrary("crypt32");
	if (crypt32dll == NULL) {
	    CRYPTOAPIerr(CRYPTOAPI_F_LOAD_LIBRARY);
	    goto err;
	}
    }
    if (CertCreateCertificateContext == NULL) {
	CertCreateCertificateContext = GetProcAddress(crypt32dll,
		"CertCreateCertificateContext");
	if (CertCreateCertificateContext == NULL) {
	    CRYPTOAPIerr(CRYPTOAPI_F_GET_PROC_ADDRESS);
	    goto err;
	}
    }
#endif

  /* Create a certificate context based on the above certificate */
  pCertContext = CertCreateCertificateContext(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
  	buf, len);
  if (pCertContext == NULL) {
	CRYPTOAPIerr(CRYPTOAPI_F_CERT_CREATE_CERT_CONTEXT);
	goto err;
  }

  /* Create an empty issuer list */
  EnhkeyUsage.cUsageIdentifier = 0;
  EnhkeyUsage.rgpszUsageIdentifier = NULL;
  CertUsage.dwType = USAGE_MATCH_TYPE_AND;
  CertUsage.Usage  = EnhkeyUsage;

  /* Searching and matching criteria to be used when building the chain */
  ChainPara.cbSize = sizeof(CERT_CHAIN_PARA);
  ChainPara.RequestedUsage = CertUsage;

  /* Get the certificate chain of our certificate */
  if (!CertGetCertificateChain(NULL, pCertContext, NULL, NULL, &ChainPara,
	0, NULL, &pChainContext)) {
	CRYPTOAPIerr(CRYPTOAPI_F_CERT_GET_CERT_CHAIN);
	goto err;
  }

  /* return 1 when the certificate is trusted, 0 when it's not; -1 on error */
  ret = (pChainContext->TrustStatus.dwErrorStatus == CERT_TRUST_NO_ERROR);

  err:
    if (buf)
	OPENSSL_free(buf);
    if (pChainContext)
	CertFreeCertificateChain(pChainContext);
    if (pCertContext)
	CertFreeCertificateContext(pCertContext);

  return ret;
}