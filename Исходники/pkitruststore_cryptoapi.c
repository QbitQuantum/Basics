static int KSI_PKITruststore_verifyCertificate(const KSI_PKITruststore *pki, const PCCERT_CONTEXT cert){
	int res = KSI_UNKNOWN_ERROR;
	KSI_CTX *ctx = NULL;
	CERT_ENHKEY_USAGE enhkeyUsage;
	CERT_USAGE_MATCH certUsage;
	CERT_CHAIN_PARA chainPara;
	PCCERT_CHAIN_CONTEXT pChainContext = NULL;
	CERT_CHAIN_POLICY_PARA policyPara;
	CERT_CHAIN_POLICY_STATUS policyStatus;
	char buf[1024];

	if (pki == NULL || cert == NULL){
		res = KSI_INVALID_ARGUMENT;
		goto cleanup;
	}
	ctx = pki->ctx;
	KSI_ERR_clearErrors(ctx);

	/* Get the certificate chain of certificate under verification. */
	/*OID List for certificate trust list extensions*/
	enhkeyUsage.cUsageIdentifier = 0;
	enhkeyUsage.rgpszUsageIdentifier = NULL;
	/*Criteria for identifying issuer certificate for chain building*/
	certUsage.dwType = USAGE_MATCH_TYPE_AND;
	certUsage.Usage = enhkeyUsage;
	/*Searching and matching criteria for chain building*/
	chainPara.cbSize = sizeof(CERT_CHAIN_PARA);
	chainPara.RequestedUsage = certUsage;

	/*Use CERT_CHAIN_CACHE_ONLY_URL_RETRIEVAL for no automatic cert store update by windows.
	 It is useful when there is need to remove default cert from system store*/
	/*Build Certificate Chain from top to root certificate*/
	if (!CertGetCertificateChain(NULL, cert, NULL, pki->collectionStore, &chainPara, 0, NULL, &pChainContext)) {
		KSI_LOG_debug(pki->ctx, "%s", getMSError(GetLastError(), buf, sizeof(buf)));
		KSI_pushError(ctx, res = KSI_CRYPTO_FAILURE, "Unable to get PKI certificate chain");
		goto cleanup;
	}
//TODO: debugging
//	printCertChain(pChainContext);

	/*TODO: REMOVE*/
	/*If chain is based on untrusted root, determine if it's in pki->collectionStore.
	 If it is, enable chain verification to trust untrusted roots*/
	if (pChainContext->TrustStatus.dwErrorStatus&CERT_TRUST_IS_UNTRUSTED_ROOT){
		KSI_LOG_debug(ctx, "CryptoAPI: Root certificate is not present under Windows 'Trusted Root Certification Authorities'.");
		KSI_LOG_debug(ctx, "CryptoAPI: Searching if it is present under PKI Trust Store from files.");
		if (isUntrustedRootCertInStore(pki, pChainContext)){
			policyPara.dwFlags =  CERT_CHAIN_POLICY_ALLOW_UNKNOWN_CA_FLAG;
			KSI_LOG_debug(ctx, "CryptoAPI: Certificate is present. Allow untrusted root certificates");
		}
		else{
			policyPara.dwFlags = 0;
			KSI_LOG_debug(ctx, "CryptoAPI: Certificate is not present.");
		}
	}
	else if (pChainContext->TrustStatus.dwErrorStatus != CERT_TRUST_NO_ERROR) {
		KSI_LOG_debug(ctx, "%s", getCertificateChainErrorStr(pChainContext));
		KSI_pushError(ctx, res = KSI_PKI_CERTIFICATE_NOT_TRUSTED, getCertificateChainErrorStr(pChainContext));
		goto cleanup;
	}
	else{
		policyPara.dwFlags = 0;
	}

	/* Verify certificate chain. */
	policyPara.cbSize = sizeof(CERT_CHAIN_POLICY_PARA);
	policyPara.pvExtraPolicyPara = 0;

	if (!CertVerifyCertificateChainPolicy(CERT_CHAIN_POLICY_BASE, pChainContext, &policyPara, &policyStatus)) {
		KSI_LOG_debug(pki->ctx, "%s", getMSError(GetLastError(), buf, sizeof(buf)));
		KSI_pushError(ctx, res = KSI_CRYPTO_FAILURE, NULL);
		goto cleanup;
	}

	if (policyStatus.dwError) {
		KSI_LOG_debug(ctx, "CryptoAPI: PKI chain policy error %X.", policyStatus.dwError);
 		KSI_pushError(ctx, res = KSI_PKI_CERTIFICATE_NOT_TRUSTED, NULL);
		goto cleanup;
	}

	res = KSI_OK;

cleanup:

	if (pChainContext) CertFreeCertificateChain(pChainContext);

	return res;
}