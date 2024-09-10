static
int
__pkcs11h_crypto_win32_certificate_get_expiration (
	IN void * const global_data,
	IN const unsigned char * const blob,
	IN const size_t blob_size,
	OUT time_t * const expiration
) {
	__crypto_win32_data_t data = (__crypto_win32_data_t)global_data;
	PCCERT_CONTEXT cert = NULL;
	PKCS11H_BOOL ok = FALSE;
	SYSTEMTIME ust, st;
	struct tm tm1;

	_PKCS11H_ASSERT (global_data!=NULL);
	_PKCS11H_ASSERT (blob!=NULL);
	_PKCS11H_ASSERT (expiration!=NULL);

	*expiration = (time_t)0;

	if (
		(cert = data->p_CertCreateCertificateContext (
			PKCS_7_ASN_ENCODING | X509_ASN_ENCODING,
			blob,
			blob_size
		)) == NULL ||
		!FileTimeToSystemTime (
			&cert->pCertInfo->NotAfter,
			&ust
		)
	) {
		goto cleanup;
	}

	SystemTimeToTzSpecificLocalTime (NULL, &ust, &st);
	memset (&tm1, 0, sizeof (tm1));
	tm1.tm_year = st.wYear - 1900;
	tm1.tm_mon  = st.wMonth - 1;
	tm1.tm_mday = st.wDay;
	tm1.tm_hour = st.wHour;
	tm1.tm_min  = st.wMinute;
	tm1.tm_sec  = st.wSecond;

	*expiration = mktime (&tm1);

	ok = TRUE;

cleanup:

	if (cert != NULL) {
		data->p_CertFreeCertificateContext (cert);
		cert = NULL;
	}

	return ok != FALSE;
}