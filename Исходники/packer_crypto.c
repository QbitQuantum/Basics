/*
 * Simple, native encryption using RC4, inspired from one of Howard's 
 * old books.
 *
 * In a nutshell: Acquire the CSP handle, create an empty hash, put 
 * the hash of the key in it, derive the crypto key from it. Note
 * (from Howard) the key also stores the algorithm in order to
 * perform the encryption.
 *
 * Return: TRUE if completed successfully, FALSE otherwise.
 */
BOOL Encrypt(LPBYTE bKey, LPBYTE bPlaintext, LPBYTE bCipherText, DWORD dwHowMuch) {
	
	HCRYPTPROV hProv;
	HCRYPTKEY  hKey;
	HCRYPTHASH hHash;
	LPBYTE lpExpKey;
	DWORD dwBuff = dwHowMuch;
	CopyMemory(bCipherText, bPlaintext, dwHowMuch);

	lpExpKey = Expand(bKey);

	if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, 
								CRYPT_VERIFYCONTEXT))
		return FALSE;
	if (!CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash))
		return FALSE;
	if (!CryptHashData(hHash, lpExpKey, strlen((char *) lpExpKey), 0))
		return FALSE;
	if (!CryptDeriveKey(hProv, CALG_RC4, hHash, 
						CRYPT_EXPORTABLE, 
						&hKey))
		return FALSE;
	if (!CryptEncrypt(hKey, 0, TRUE, 0, 
						bCipherText, 
						&dwBuff, 
						dwHowMuch))
		return FALSE;

	if (hKey)  CryptDestroyKey(hKey);
	if (hHash) CryptDestroyHash(hHash);
	if (hProv) CryptReleaseContext(hProv, 0);

	return TRUE;
}