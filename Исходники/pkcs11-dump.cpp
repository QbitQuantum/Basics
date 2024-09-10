static
std::string
ParseSubject (
	IN const void * const p,
	IN const unsigned s
) {
	char szSubject[1024];
	bool fOK = false;

#if defined(_WIN32)
	CRYPT_DER_BLOB blobSubject = {s, (PBYTE)p};

	if (
		CertNameToStrA (
			X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
			&blobSubject,
			CERT_X500_NAME_STR | CERT_NAME_STR_REVERSE_FLAG,
			szSubject,
			sizeof (szSubject)
		) != 0
	) {
		fOK = true;
	}
#else
	X509_NAME *name;
	name = X509_NAME_new ();
	if (name != NULL) {
		pkcs11_openssl_d2i_t pp = (pkcs11_openssl_d2i_t)p;
		if (
			d2i_X509_NAME (
				&name,
				&pp,
				s
			)
		) {
			X509_NAME_oneline (
				name,
				szSubject,
				sizeof (szSubject)
			);
			fOK = true;
		}
		X509_NAME_free (name);
	}
#endif
	if (fOK) {
		return szSubject;
	}
	else {
		return "ERROR";
	}
}