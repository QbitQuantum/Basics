BOOL SavedPasswords::RetrievePassword(LPCWSTR path, LPWSTR password_buf, DWORD password_buf_len)
{
	wstring hash;

	if (!GetPathHash(path, hash))
		return FALSE;

	BYTE *p = NULL;
	UINT len = 0;
	if (!theApp.GetProfileBinary(SAVED_PASSWORDS_SECTION, hash.c_str(), &p, &len))
		return FALSE;

	DATA_BLOB pw_blob;
	DATA_BLOB enc_pw_blob;

	DATA_BLOB optional_entropy;
	const char *entropy = OPTIONAL_ENTROPY;
	optional_entropy.cbData = (DWORD)strlen(entropy);
	optional_entropy.pbData = (BYTE*)entropy;

	enc_pw_blob.cbData = len;
	enc_pw_blob.pbData = p;

	BOOL bResult = CryptUnprotectData(&enc_pw_blob, NULL, &optional_entropy, NULL, NULL, 0, &pw_blob);

	if (!bResult) {
		delete[] p;
		return FALSE;
	}

	wcscpy_s(password_buf, password_buf_len, (WCHAR*)pw_blob.pbData);

	SecureZeroMemory(pw_blob.pbData, pw_blob.cbData);

	LocalFree(pw_blob.pbData);

	delete[] p;

	return TRUE;
}