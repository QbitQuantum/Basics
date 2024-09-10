int cryptoapi_hash_vector(ALG_ID alg, size_t hash_len, size_t num_elem,
						  const u8 *addr[], const size_t *len, u8 *mac)
{
	HCRYPTPROV prov;
	HCRYPTHASH hash;
	size_t i;
	DWORD hlen;
	int ret = 0;

	/*
	if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, 0)) {
		cryptoapi_report_error("CryptAcquireContext");
		return -1;
	}
	*/

	BOOL r = CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, 0);
	if (!r) {
		if (GetLastError() == NTE_BAD_KEYSET) {
			r = CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET);
		}
	}

	if (!r) {
		cryptoapi_report_error("CryptAcquireContext");
		return -1;
	}

	if (!CryptCreateHash(prov, alg, 0, 0, &hash)) {
		cryptoapi_report_error("CryptCreateHash");
		CryptReleaseContext(prov, 0);
		return -1;
	}

	for (i = 0; i < num_elem; i++) {
		if (!CryptHashData(hash, (BYTE *) addr[i], len[i], 0)) {
			cryptoapi_report_error("CryptHashData");
			CryptDestroyHash(hash);
			CryptReleaseContext(prov, 0);
		}
	}

	hlen = hash_len;
	if (!CryptGetHashParam(hash, HP_HASHVAL, mac, &hlen, 0)) {
		cryptoapi_report_error("CryptGetHashParam");
		ret = -1;
	}

	CryptDestroyHash(hash);
	CryptReleaseContext(prov, 0);

	return ret;
}