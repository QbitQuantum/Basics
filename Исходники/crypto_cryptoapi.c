struct crypto_public_key * crypto_public_key_from_cert(const u8 *buf,
						       size_t len)
{
	struct crypto_public_key *pk;
	PCCERT_CONTEXT cc;

	pk = os_zalloc(sizeof(*pk));
	if (pk == NULL)
		return NULL;

	cc = CertCreateCertificateContext(X509_ASN_ENCODING |
					  PKCS_7_ASN_ENCODING, buf, len);
	if (!cc) {
 		cryptoapi_report_error("CryptCreateCertificateContext");
		os_free(pk);
		return NULL;
	}

	if (!CryptAcquireContext(&pk->prov, NULL, MS_DEF_PROV, PROV_RSA_FULL,
				 0)) {
 		cryptoapi_report_error("CryptAcquireContext");
		os_free(pk);
		CertFreeCertificateContext(cc);
		return NULL;
	}

	if (!CryptImportPublicKeyInfo(pk->prov, X509_ASN_ENCODING |
				      PKCS_7_ASN_ENCODING,
				      &cc->pCertInfo->SubjectPublicKeyInfo,
				      &pk->rsa)) {
 		cryptoapi_report_error("CryptImportPublicKeyInfo");
		CryptReleaseContext(pk->prov, 0);
		os_free(pk);
		CertFreeCertificateContext(cc);
		return NULL;
	}

	CertFreeCertificateContext(cc);

	return pk;
}