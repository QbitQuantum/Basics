BOOL isCardInReader(PCCERT_CONTEXT certContext) {
#ifndef WIN_XP
	DWORD flags = CRYPT_ACQUIRE_CACHE_FLAG|CRYPT_ACQUIRE_COMPARE_KEY_FLAG|CRYPT_ACQUIRE_SILENT_FLAG;
	NCRYPT_KEY_HANDLE key = 0;
	DWORD spec = 0;
	BOOL ncrypt = FALSE;
	CryptAcquireCertificatePrivateKey(certContext, flags, 0, &key, &spec, &ncrypt);
	if(!key) {
		return FALSE;
	}
	if(ncrypt) {
		NCryptFreeObject(key);
	}
#endif
	return TRUE;
}