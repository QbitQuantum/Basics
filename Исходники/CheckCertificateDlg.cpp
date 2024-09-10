static CString getCertificateHash(HCRYPTPROV hCryptProv, ALG_ID algId, BYTE* certificate, size_t len)
{
	CString readable = _T("unknown");
	std::unique_ptr<BYTE[]> pHash(nullptr);
	HCRYPTHASH hHash = NULL;

	if (!hCryptProv)
		goto finish;

	if (!CryptCreateHash(hCryptProv, algId, 0, 0, &hHash))
		goto finish;

	if (!CryptHashData(hHash, certificate, (DWORD)len, 0))
		goto finish;

	DWORD hashLen;
	DWORD hashLenLen = sizeof(DWORD);
	if (!CryptGetHashParam(hHash, HP_HASHSIZE, (BYTE *)&hashLen, &hashLenLen, 0))
		goto finish;

	pHash.reset(new BYTE[hashLen]);
	if (!CryptGetHashParam(hHash, HP_HASHVAL, pHash.get(), &hashLen, 0))
		goto finish;

	readable.Empty();
	for (const BYTE* it = pHash.get(); it < pHash.get() + hashLen; ++it)
	{
		CString tmp;
		tmp.Format(L"%02X", *it);
		if (!readable.IsEmpty())
			readable += L":";
		readable += tmp;
	}

finish:
	if (hHash)
		CryptDestroyHash(hHash);

	return readable;
}