int KSI_DataHasher_reset(KSI_DataHasher *hasher) {
	int res = KSI_UNKNOWN_ERROR;
	ALG_ID msHashAlg = 0;
	CRYPTO_HASH_CTX * pCryptoCTX = NULL;	//Crypto helper struct
	HCRYPTPROV pCSP = 0;					//Crypto service provider
	HCRYPTHASH pTmp_hash = 0;			//Hash object

	if (hasher == NULL){
		res = KSI_INVALID_ARGUMENT;
		goto cleanup;
	}
	KSI_ERR_clearErrors(hasher->ctx);

	/*Shortcuts for pointers*/
	pCryptoCTX = (CRYPTO_HASH_CTX*)hasher->hashContext;
	pCSP = pCryptoCTX->pt_CSP;

	/*Convert hash algorithm into crypto api style*/
	msHashAlg = hashAlgorithmToALG_ID(hasher->algorithm);
	if (msHashAlg == 0) {
		KSI_pushError(hasher->ctx, res = KSI_UNAVAILABLE_HASH_ALGORITHM, NULL);
		goto cleanup;
	}

	/*If hasher object already exists, destroy one*/
	if (pTmp_hash != 0){
		CryptDestroyHash(pTmp_hash);
		}

	/*Create new hasher object*/
	if (!CryptCreateHash(pCSP, msHashAlg, 0,0,&pTmp_hash)) {
		DWORD error = GetLastError();
		KSI_LOG_debug(hasher->ctx, "Cryptoapi: Create hash error %i\n", error);
		KSI_pushError(hasher->ctx, res = KSI_OUT_OF_MEMORY, NULL);
		goto cleanup;
		}

	pCryptoCTX->pt_hHash = pTmp_hash;

	pTmp_hash = 0;

	res = KSI_OK;

cleanup:

	if (pTmp_hash) CryptDestroyHash(pTmp_hash);

	return res;
}