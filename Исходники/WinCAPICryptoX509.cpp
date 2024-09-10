// Get functions
XSECCryptoKey * WinCAPICryptoX509::clonePublicKey() const {


	if (mp_certContext == NULL) {
		throw XSECCryptoException(XSECCryptoException::X509Error,
			"WinCAPI:X509 - clonePublicKey called before X509 loaded");
	}

	// Import the key into the provider to get a pointer to the key

	HCRYPTKEY key;
	BOOL fResult;
                 
	if (getPublicKeyType() == XSECCryptoKey::KEY_DSA_PUBLIC) {

		fResult= CryptImportPublicKeyInfo(
			   m_pDSS,
			   X509_ASN_ENCODING,
			   &(mp_certContext->pCertInfo->SubjectPublicKeyInfo),
			   &key);
                 

		if (fResult == FALSE) {
			throw XSECCryptoException(XSECCryptoException::X509Error,
				"WinCAPI:X509 - Error loading public key info from certificate");
		}

		// Now that we have a handle for the DSA key, create a DSA Key object to
		// wrap it in

		WinCAPICryptoKeyDSA * ret;
		XSECnew(ret, WinCAPICryptoKeyDSA(m_pDSS, key));

		return ret;

	}

	if (getPublicKeyType() == XSECCryptoKey::KEY_RSA_PUBLIC) {

		fResult= CryptImportPublicKeyInfo(
			   m_pRSA,
			   X509_ASN_ENCODING,
			   &(mp_certContext->pCertInfo->SubjectPublicKeyInfo),
			   &key);
                 

		if (fResult == FALSE) {
			throw XSECCryptoException(XSECCryptoException::X509Error,
				"WinCAPI:X509 - Error loading public key info from certificate");
		}

		// Now that we have a handle for the DSA key, create a DSA Key object to
		// wrap it in

		WinCAPICryptoKeyRSA * ret;
		XSECnew(ret, WinCAPICryptoKeyRSA(m_pRSA, key));

		return ret;

	}

	return NULL;		// Unknown key type, but not necessarily an error

}