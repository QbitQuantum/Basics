BOOL Csp::CPExportKey(
		IN  HCRYPTPROV hProv,
		IN  HCRYPTKEY hKey,
		IN  HCRYPTKEY hPubKey,
		IN  DWORD dwBlobType,
		IN  DWORD dwFlags,
		OUT LPBYTE pbData,
		IN OUT LPDWORD pcbDataLen){
	DECL_RET(ret);
	try {
		CSPContext * it = *findContext(hProv);
		CSPKeyContext * key =  *it->findKeyContext(hKey);

		switch (dwBlobType) {
			case PUBLICKEYBLOB: {
				if (hPubKey) throw err_badKey();
				packData dat(pbData,pcbDataLen);
				struct {
					PUBLICKEYSTRUC  pubkeyStruc;
					RSAPUBKEY		rsaKey;
					BYTE			modulus[2048 / 8];
				} RSABlob;
				PCCERT_CONTEXT ctx = CertCreateCertificateContext(X509_ASN_ENCODING,
					&key->m_certificateBlob[0],(DWORD)key->m_certificateBlob.size());
				PCRYPT_BIT_BLOB pubKey = &ctx->pCertInfo->SubjectPublicKeyInfo.PublicKey;
				DWORD actSize = sizeof(RSABlob);
				err_crypto::check(CryptDecodeObject(X509_ASN_ENCODING,
					RSA_CSP_PUBLICKEYBLOB,pubKey->pbData,pubKey->cbData,
					0, &RSABlob, &actSize));
				dat.setValue(RSABlob);
				//key->m_certificateBlo
				ret.SetOk();
				break;
				}
			default:
				throw std::runtime_error("not implemented");
			}
	} catch(std::runtime_error &err) {
		ret.logReturn(err);
	}
	return ret;
}