/*
 * Compute the Base64-encoded HmacSha256 for the given key and content, optionally URL
 * encoding the Base64 result.
 */
CharHolder
HmacSha256::getEncodedHMAC(const std::string& secretKey, const std::string& signContent, bool urlEncode)
{
	// get the crypt provider
	CryptProviderHolder provider;
	if (!CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
		throw FormattedException(GetLastError(), "CryptAcquireContext: %08x", GetLastError());

	// import the supplied key into a crypt library key object using PLAINTEXTKEYBLOB
	typedef struct _PLAINTEXTKEYBLOBSTRUCT {
		BLOBHEADER hdr;
		DWORD dwKeyLen;
	} PLAINTEXTKEYBLOBSTRUCT;

	UCharHolder keyImport(sizeof(PLAINTEXTKEYBLOBSTRUCT) + secretKey.length());
	((PLAINTEXTKEYBLOBSTRUCT*) keyImport.get())->hdr.bType = PLAINTEXTKEYBLOB;
	((PLAINTEXTKEYBLOBSTRUCT*) keyImport.get())->hdr.bVersion = CUR_BLOB_VERSION;
	((PLAINTEXTKEYBLOBSTRUCT*) keyImport.get())->hdr.reserved = 0;
	((PLAINTEXTKEYBLOBSTRUCT*) keyImport.get())->hdr.aiKeyAlg = CALG_RC2;
	((PLAINTEXTKEYBLOBSTRUCT*) keyImport.get())->dwKeyLen = secretKey.length();
	CopyMemory(keyImport.get() + sizeof(PLAINTEXTKEYBLOBSTRUCT), secretKey.c_str(), secretKey.length());

	CryptKeyHolder key;
	if (!CryptImportKey(provider.get(), (const BYTE *) keyImport.get(), sizeof(PLAINTEXTKEYBLOBSTRUCT), 0,
			CRYPT_IPSEC_HMAC_KEY, &key))
		throw FormattedException(GetLastError(), "CryptImportKey(key): %08x", GetLastError());

	// create the hash object using the imported key
	CryptHashHolder hash;
	if (!CryptCreateHash(provider.get(), CALG_HMAC, key.get(), 0, &hash))
		throw FormattedException(GetLastError(), "CryptCreateHash(data): %08x", GetLastError());
	HMAC_INFO hmacInfo;
	ZeroMemory(&hmacInfo, sizeof(HMAC_INFO));
	hmacInfo.HashAlgid = CALG_SHA_256;
	if (!CryptSetHashParam(hash.get(), HP_HMAC_INFO, (BYTE *) &hmacInfo, 0))
		throw FormattedException(GetLastError(), "CryptSetHashParam(data): %08x", GetLastError());

	// hash the content data
	if (!CryptHashData(hash.get(), (const BYTE *) signContent.c_str(), signContent.length(), 0))
		throw FormattedException("CryptHashData(data): %08x", GetLastError());

	// query the size of the hash that will be returned
	DWORD hashSize = 0;
	if (!CryptGetHashParam(hash.get(), HP_HASHVAL, NULL, &hashSize, 0))
		throw FormattedException(GetLastError(), "CryptGetHashParam(data): %08x", GetLastError());

	// create a managed buffer to receive the hash value and then store it there
	UCharHolder buffer(hashSize);
	if (!CryptGetHashParam(hash.get(), HP_HASHVAL, (BYTE *) buffer.get(), &hashSize, 0))
		throw FormattedException(GetLastError(), "CryptGetHashParam(data): %08x", GetLastError());

	// convert hash to Base64, store that in a managed buffer
	size_t base64Size;
	Base64Codec base64Codec;
	char* base64 = base64Codec.base64_encode((const unsigned char *) buffer.get(), buffer.getSize(), &base64Size);
	CharHolder base64Holder(base64, base64Size);

	if (!urlEncode)
		return base64Holder;

	// poor-man's URL encoding for Base64'd data -- only need to worry about + / and =
	int count = 0;
	for (unsigned int i=0; i<base64Holder.getSize(); i++) {
		if ((base64Holder.get()[i] == '+') || (base64Holder.get()[i] == '/') || (base64Holder.get()[i] == '='))
			count++;
	}
	CharHolder urlHolder(base64Holder.getSize() + 2 * count); // 2 additional characters for each + / or =

	int j = 0;
	for (unsigned int i=0; i<base64Holder.getSize(); i++) {
		if (base64Holder.get()[i] == '+') {
			urlHolder.get()[j++] = '%';
			urlHolder.get()[j++] = '2';
			urlHolder.get()[j++] = 'B';
		}
		else if (base64Holder.get()[i] == '/') {
			urlHolder.get()[j++] = '%';
			urlHolder.get()[j++] = '2';
			urlHolder.get()[j++] = 'F';
		}
		else if (base64Holder.get()[i] == '=') {
			urlHolder.get()[j++] = '%';
			urlHolder.get()[j++] = '3';
			urlHolder.get()[j++] = 'D';
		}
		else {
			urlHolder.get()[j++] = base64Holder.get()[i];
		}
	}
	return urlHolder;
}