//SHA-1 hash function
bool __fastcall SHA1_Hash(
	FILE *Input)
{
//Parameters check
	if (HashFamilyID != HASH_ID_SHA1 || Input == nullptr)
	{
		fwprintf_s(stderr, L"Parameters error.\n");
		return false;
	}

//Initialization
	std::shared_ptr<char> Buffer(new char[FILE_BUFFER_SIZE]()), StringBuffer(new char[FILE_BUFFER_SIZE]());
	auto HashInstance = std::make_shared<SHA1_State>();
	memset(Buffer.get(), 0, FILE_BUFFER_SIZE);
	memset(StringBuffer.get(), 0, FILE_BUFFER_SIZE);
	memset(HashInstance.get(), 0, sizeof(SHA1_State));
	size_t ReadLength = 0;

//SHA-1 initialization
	SHA1_Init(HashInstance.get());

//Hash process
	while (!feof(Input))
	{
		memset(Buffer.get(), 0, FILE_BUFFER_SIZE);
		ReadLength = fread_s(Buffer.get(), FILE_BUFFER_SIZE, sizeof(char), FILE_BUFFER_SIZE, Input);
		if (ReadLength == 0 && errno == EINVAL)
		{
			fwprintf_s(stderr, L"Hash process error.\n");
			return false;
		}
		else {
			SHA1_Process(HashInstance.get(), (uint8_t *)Buffer.get(), (unsigned long)ReadLength);
		}
	}

//Binary to hex
	memset(Buffer.get(), 0, FILE_BUFFER_SIZE);
	SHA1_Done(HashInstance.get(), (uint8_t *)Buffer.get());
	if (sodium_bin2hex(StringBuffer.get(), FILE_BUFFER_SIZE, (const unsigned char *)Buffer.get(), SHA1_SIZE_DIGEST) == nullptr)
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