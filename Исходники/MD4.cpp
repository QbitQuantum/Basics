//MD4 hash function
bool __fastcall MD4_Hash(
	FILE *Input)
{
//Parameters check
	if ((HashFamilyID != HASH_ID_MD4 && HashFamilyID != HASH_ID_ED2K) || Input == nullptr)
	{
		fwprintf_s(stderr, L"Parameters error.\n");
		return false;
	}

//Initialization
	size_t ReadBlockSize = FILE_BUFFER_SIZE, ReadLength = 0, RoundCount = 0;
	if (HashFamilyID == HASH_ID_ED2K)
		ReadBlockSize = ED2K_SIZE_BLOCK;
	std::shared_ptr<char> Buffer(new char[ReadBlockSize]()), StringBuffer(new char[FILE_BUFFER_SIZE]()), BufferED2K(new char[MD4_SIZE_DIGEST]());
	memset(Buffer.get(), 0, ReadBlockSize);
	memset(StringBuffer.get(), 0, FILE_BUFFER_SIZE);
	memset(BufferED2K.get(), 0, MD4_SIZE_DIGEST);
	MD4_CTX HashInstance, HashInstanceED2K;
	memset(&HashInstance, 0, sizeof(MD4_CTX));
	memset(&HashInstanceED2K, 0, sizeof(MD4_CTX));

//MD4 initialization
	MD4_Init(&HashInstance);
	if (HashFamilyID == HASH_ID_ED2K)
		MD4_Init(&HashInstanceED2K);

//Hash process
	while (!feof(Input))
	{
		memset(Buffer.get(), 0, ReadBlockSize);
		_set_errno(0);
		ReadLength = fread_s(Buffer.get(), ReadBlockSize, sizeof(char), ReadBlockSize, Input);
		if (ReadLength == 0)
		{
			fwprintf_s(stderr, L"Hash process error");
			if (errno > 0)
				fwprintf_s(stderr, L", error code is %d.\n", errno);
			else
				fwprintf_s(stderr, L".\n");

			return false;
		}
		else {
			MD4_Update(&HashInstance, Buffer.get(), ReadLength);
			if (HashFamilyID == HASH_ID_ED2K)
			{
				MD4_Final((unsigned char *)Buffer.get(), &HashInstance);
				memcpy_s(BufferED2K.get(), MD4_SIZE_DIGEST, Buffer.get(), MD4_SIZE_DIGEST);
				MD4_Update(&HashInstanceED2K, Buffer.get(), MD4_SIZE_DIGEST);
				MD4_Init(&HashInstance);
			}

			++RoundCount;
		}
	}

//Binary to hex
	memset(Buffer.get(), 0, ReadBlockSize);
	if (HashFamilyID == HASH_ID_MD4)
	{
		MD4_Final((unsigned char *)Buffer.get(), &HashInstance);
	}
	else if (HashFamilyID == HASH_ID_ED2K)
	{
		if (RoundCount > 1U)
			MD4_Final((unsigned char *)Buffer.get(), &HashInstanceED2K);
		else 
			memcpy_s(Buffer.get(), MD4_SIZE_DIGEST, BufferED2K.get(), MD4_SIZE_DIGEST);
	}
	else {
		return false;
	}
	if (sodium_bin2hex(StringBuffer.get(), FILE_BUFFER_SIZE, (const unsigned char *)Buffer.get(), MD4_SIZE_DIGEST) == nullptr)
	{
		fwprintf_s(stderr, L"Convert binary to hex error.\n");
		return false;
	}
	else {
	//Print to screen.
		std::string HashResult = StringBuffer.get();
		CaseConvert(true, HashResult);
		for (size_t Index = 0;Index < HashResult.length();++Index)
			fwprintf_s(stderr, L"%c", HashResult.c_str()[Index]);
		fwprintf_s(stderr, L"\n");
	}

	return true;
}