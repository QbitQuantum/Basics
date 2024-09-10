//-----------------------------------------------------------------
// Calculate the MD5 hash value from a previously matched file name
//----------------------------------------------------------------- 
LPTSTR CalculateMD5(LPTSTR FileName)
{
	HANDLE hashFile = NULL;
	BOOL bResult = FALSE;
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	DWORD cbRead = 0;
	DWORD cbHash = MD5LEN;
	BYTE rgbFile[BUFSIZE];
	BYTE rgbHash[MD5LEN];
	CHAR rgbDigits[] = "0123456789abcdef";
	LPTSTR md5HashString;
	DWORD i;

	// Open the file to perform hash
	hashFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (INVALID_HANDLE_VALUE == hashFile) {
		return TEXT("ERROR_OPENING_FILE\0");
	}

	// Get handle to the crypto provider
	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
		CloseHandle(hashFile);
		return TEXT("HASHING_FAILED\0");
	}

	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash)) {
		CloseHandle(hashFile);
		return TEXT("HASHING_FAILED\0");
	}

	while (bResult = ReadFile(hashFile, rgbFile, BUFSIZE, &cbRead, NULL)) {
		if (0 == cbRead) {
			break;
		}
		if (!CryptHashData(hHash, rgbFile, cbRead, 0)) {
			CryptReleaseContext(hProv, 0);
			CryptDestroyHash(hHash);
			CloseHandle(hashFile);
			return TEXT("HASHING_FAILED\0");
		}
	}

	if (!bResult) {
		CryptReleaseContext(hProv, 0);
		CryptDestroyHash(hHash);
		CloseHandle(hashFile);
		return TEXT("ERROR_READING_FILE\0");
	}

	// Finally got here with no errors, now calculate the SHA1 hash value
	md5HashString = MYALLOC0((MD5LEN * 2 + 1) * sizeof(TCHAR));
	_tcscpy_s(md5HashString, 1, TEXT(""));
	if (CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0)) 
	{
		for (i = 0; i < cbHash; i++) {
			_sntprintf(md5HashString + (i * 2), 2, TEXT("%02x\0"), rgbHash[i]);
		}
	}

	CryptDestroyHash(hHash);
	CryptReleaseContext(hProv, 0);
	CloseHandle(hashFile);
	return md5HashString;
}