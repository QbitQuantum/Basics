void CEstEIDIEPluginBHO::signWithCSP(BSTR id, BSTR hash, BSTR *signature) {
	LOG_LOCATION;

	HCRYPTPROV cryptoProvider = NULL;
	HCRYPTHASH _hash = NULL ;
	PCCERT_CONTEXT certContext = NULL;
	HCERTSTORE cert_store;
	BOOL must_release_provider;		

	try{
		if(!id || !strlen(CW2A(id))) {
			throw CryptoException(ESTEID_CERT_NOT_FOUND_ERROR);
		}
		EstEID_log("signing started, selected certificate id = %s", CW2A(id));	

#define VALID_HASH_LENGTH 40
		if (_bstr_t(hash).length() != VALID_HASH_LENGTH) {
			throw CryptoException("invalid hash");
		}

		cert_store = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, CERT_SYSTEM_STORE_CURRENT_USER | CERT_STORE_READONLY_FLAG, L"MY");
		if(!cert_store) throw CryptoException();
		
		while(certContext = CertFindCertificateInStore(cert_store, X509_ASN_ENCODING, 0, CERT_FIND_ANY, NULL, certContext)) {
			if(certificateMatchesId(certContext, id)) {
				DWORD key_type = 0;
				if (CryptAcquireCertificatePrivateKey(certContext, CRYPT_ACQUIRE_CACHE_FLAG, 
					NULL, &cryptoProvider, &key_type, &must_release_provider)) {
						BYTE hashBytes[21];
						DWORD hashBytesLength = 20;
						
						CryptStringToBinary(hash, VALID_HASH_LENGTH, CRYPT_STRING_HEX, hashBytes, &hashBytesLength, 0, 0);
						hashBytes[hashBytesLength] = '\0';
						EstEID_log("Number of bytes stored in hashBytes buffer = %u", hashBytesLength);

						CryptoErrorHandler(CryptCreateHash(cryptoProvider, CALG_SHA1, 0, 0, &_hash));
						EstEID_log("CryptCreateHash() set hash object pointer to %p", _hash);  

						CryptoErrorHandler(CryptSetHashParam(_hash, HP_HASHVAL, hashBytes, 0));

						#define SIGNATURE_LENGTH 1024 
						BYTE _signature[SIGNATURE_LENGTH];
						DWORD signatureLength = SIGNATURE_LENGTH;
						INT retCode = CryptSignHash(_hash, AT_SIGNATURE, NULL, 0, _signature, &signatureLength);
						DWORD lastError = GetLastError();
						EstEID_log("CryptSignHash() return code: %u (%s) %x", retCode, retCode ? "SUCCESS" : "FAILURE", lastError);
						if(!retCode) throw CryptoException(lastError);

						CryptDestroyHash(_hash);
						CryptReleaseContext(cryptoProvider, 0);	
						CertFreeCertificateContext(certContext);
						if(must_release_provider) CertCloseStore(cert_store, 0);

						std::stringstream ss;
						for (DWORD i = 0; i < signatureLength; i++) {
							ss << std::hex << std::setfill('0') << std::setw(2) << (short)_signature[signatureLength - i - 1];
						}

						*signature = _bstr_t(ss.str().c_str()).Detach();
				}
				else {
					INT lastError = GetLastError();
					EstEID_log("ERROR: CryptAcquireCertificatePrivateKey() failed, error code = %lXh", GetLastError());
					switch(lastError) {
					case NTE_BAD_PUBLIC_KEY:
						EstEID_log("       error code %lXh: NTE_BAD_PUBLIC_KEY", lastError);
						break;
					case NTE_SILENT_CONTEXT:
						EstEID_log("       error code %lXh: NTE_SILENT_CONTEXT", lastError);
					}
				}				
				break;
			}
		}	
	}
	catch(CryptoException e) {
		*signature = _bstr_t("").Detach();
		if(_hash) CryptDestroyHash(_hash);
		if(cryptoProvider) CryptReleaseContext(cryptoProvider, 0);
		if(certContext) CertFreeCertificateContext(certContext);
		if(must_release_provider && cert_store) CertCloseStore(cert_store, 0);

		throw(CryptoException(e.windowsErrorCode));
	}
}