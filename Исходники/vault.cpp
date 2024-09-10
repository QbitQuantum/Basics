const char* encrypt(const char* unhexed, const char* key) {
	int size = strlen(unhexed);
	int spaces = 0;
	if (size % 16) {
		spaces = 16 - (size % 16);
	}
	size += spaces;

	char* buffer = new char[size+1];
	// TODO: memory check

	// Add spaces to the end to make size divisible by block size
	for (; spaces > 0; spaces--) {
		buffer[size-spaces] = ' ';
	}

	// Create reader
	CRijndael reader;
	reader.MakeKey(key, CRijndael::sm_chain0, 16, 16);
	reader.Encrypt(unhexed, buffer, size, CRijndael::CFB);

	// Convert to hex
	char* result = new char[size*2+1];
	CharStr2HexStr((unsigned char*)buffer, result, size);
	delete [] buffer;

	return result;
}