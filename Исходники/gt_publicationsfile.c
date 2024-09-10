/* Helper function to trace the signing cert to a trusted CA root
 * in the Windows Certificate Store. */
static int checkCertCryptoAPI(const GTPublicationsFile *publications_file)
{
	int res = GT_UNKNOWN_ERROR;
	unsigned char *cert_der = NULL;
	size_t cert_der_len;
	PCCERT_CONTEXT pCertContext = NULL;
	PCCERT_CHAIN_CONTEXT pChainContext = NULL;
	CERT_ENHKEY_USAGE enhkeyUsage;
	CERT_USAGE_MATCH certUsage;
	CERT_CHAIN_PARA chainPara;
	CERT_CHAIN_POLICY_PARA policyPara;
	CERT_CHAIN_POLICY_STATUS policyStatus;
	char tmp_name[256];

	res = GTPublicationsFile_getSigningCert(publications_file, &cert_der, &cert_der_len);
	if (res != GT_OK) {
		goto cleanup;
	}

	/* Create a certificate context based on the above certificate. */
	pCertContext = CertCreateCertificateContext(
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING, cert_der, cert_der_len);
	if (pCertContext == NULL) {
		res = GT_CRYPTO_FAILURE;
		goto cleanup;
	}

#ifdef MAGIC_EMAIL
	CertGetNameStringA(pCertContext, CERT_NAME_EMAIL_TYPE, 0, NULL,
			tmp_name, sizeof(tmp_name));
	if (strcmp(tmp_name, MAGIC_EMAIL) != 0) {
		return GT_INVALID_SIGNATURE;
	}
#endif

	/* Get the certificate chain of our certificate. */
	enhkeyUsage.cUsageIdentifier = 0;
	enhkeyUsage.rgpszUsageIdentifier = NULL;
	certUsage.dwType = USAGE_MATCH_TYPE_AND;
	certUsage.Usage = enhkeyUsage;
	chainPara.cbSize = sizeof(CERT_CHAIN_PARA);
	chainPara.RequestedUsage = certUsage;

	if (!CertGetCertificateChain(NULL, pCertContext, NULL, NULL,
			&chainPara, 0, NULL, &pChainContext)) {
		res = GT_CRYPTO_FAILURE;
		goto cleanup;
	}

	if (pChainContext->TrustStatus.dwErrorStatus != CERT_TRUST_NO_ERROR) {
		res = GT_CERT_NOT_TRUSTED;
		goto cleanup;
	}

	/* Verify certificate chain. */
	policyPara.cbSize = sizeof(CERT_CHAIN_POLICY_PARA);
	policyPara.dwFlags = 0;
	policyPara.pvExtraPolicyPara = NULL;

	if (!CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_BASE,
			pChainContext, &policyPara, &policyStatus)) {
		res = GT_CRYPTO_FAILURE;
		goto cleanup;
	}

	if (policyStatus.dwError) {
		res = GT_CERT_NOT_TRUSTED;
		goto cleanup;
	}

	res = GT_OK;

cleanup:
	GT_free(cert_der);
	if (pChainContext != NULL) {
		CertFreeCertificateChain(pChainContext);
	}
	if (pCertContext != NULL) {
		CertFreeCertificateContext(pCertContext);
	}

	return res;
}