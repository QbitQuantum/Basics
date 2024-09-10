char* CryptPassword(const char* str, int inSize, void** out, int* outSize, int encrypt) {
	DATA_BLOB input, output;
	input.cbData = (DWORD)inSize + 1;
	input.pbData = (BYTE*)str;

	BOOL ok;
	if (encrypt) {
		ok = CryptProtectData(&input, NULL, NULL, NULL, NULL, 0, &output);
		if (!ok) {
			return geterror("CryptProtectData");
		}
	} else {
		ok = CryptUnprotectData(&input, NULL, NULL, NULL, NULL, 0, &output);
		if (!ok) {
			return geterror("CryptUnprotectData");
		}
	}

	*out = output.pbData;
	*outSize = output.cbData;

	return NULL;
}