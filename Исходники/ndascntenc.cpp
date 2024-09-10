//
// Create a 128 bit key
//
UINT
WINAPI
NdasEncCreateKey128(
	LPCTSTR szPassphrase, 
	CONST BYTE* lpEntropy,
	DWORD cbEntrypy,
	LPBYTE lpbKey128)
{
	BOOL fInvalidParam = ::IsBadStringPtr(szPassphrase, -1);
	_ASSERTE(!fInvalidParam);
	if (fInvalidParam) {
		return ERROR_INVALID_PARAMETER;
	}

	fInvalidParam = ::IsBadReadPtr(lpEntropy, cbEntrypy);
	_ASSERTE(!fInvalidParam);
	if (fInvalidParam) {
		return ERROR_INVALID_PARAMETER;
	}

	fInvalidParam = ::IsBadWritePtr(lpbKey128, 16);
	_ASSERTE(!fInvalidParam);
	if (fInvalidParam) {
		return ERROR_INVALID_PARAMETER;
	}

	size_t cbPassphrase = 0;

	HRESULT hr = ::StringCbLength(
		szPassphrase, 
		STRSAFE_MAX_CCH * sizeof(TCHAR), 
		&cbPassphrase);

	if (FAILED(hr)) {
		return ERROR_INVALID_PARAMETER;
	}

	//
	// Get MD5 hash of the passphrase
	//

	AutoResourceT<xcrypt::IHashing*> pHashing = 
		xcrypt::CreateCryptAPIMD5Hashing();

	BOOL fSuccess = pHashing->Initialize();

	if (!fSuccess) {
		return NDASENC_ERROR_HASH_PROVIDER_INIT_FAILURE;
	}

	fSuccess = pHashing->HashData(
		(CONST BYTE*) szPassphrase, 
		cbPassphrase);

	if (!fSuccess) {
		return NDASENC_ERROR_HASH_GEN_FAILURE;
	}

	fSuccess = pHashing->HashData(
		lpEntropy,
		cbEntrypy);

	if (!fSuccess) {
		return NDASENC_ERROR_HASH_GEN_FAILURE_2;
	}

	DWORD cbHash = 0;
	LPBYTE lpbHash = pHashing->GetHashValue(&cbHash);

	if (NULL == lpbHash) {
		return NDASENC_ERROR_HASH_GEN_FAILURE_3;
	}

#ifdef _DEBUG
	_tprintf(_T("Hash: %s\n"), 
		xs::CXSByteString(cbHash, lpbHash, _T(' ')).ToString());
#endif

	_ASSERTE(16 == cbHash);

	::CopyMemory(lpbKey128, lpbHash, cbHash);

	return ERROR_SUCCESS;

}