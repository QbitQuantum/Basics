/**
 * Decrypts a buffer using the crypto API
 *
 * @param SrcBuffer the source data being decrypted
 * @param SrcLen the size of the buffer in bytes
 * @param DestBuffer (out) chunk of memory that is written to
 * @param DestLen (in) the size of the dest buffer, (out) the size of the encrypted data
 *
 * @return true if the decryption worked, false otherwise
 */
static bool DecryptBuffer(const uint8* SrcBuffer,const uint32 SrcLen,uint8* DestBuffer,uint32& DestLen)
{
	bool bDecryptedOk = false;
#if PLATFORM_MAC
	unsigned long long MacAddress = 0;
	uint32 AddressSize = sizeof(unsigned long long);
	GetMacAddress((uint8*)&MacAddress,AddressSize);
	unsigned long long Entropy = 5148284414757334885ull;
	Entropy ^= MacAddress;

	uint8 Key[kCCKeySizeAES128];
	check(kCCKeySizeAES128 == 2*sizeof(unsigned long long));
	FMemory::Memcpy(Key,&Entropy,sizeof(Entropy));
	FMemory::Memcpy(Key+sizeof(Entropy),&Entropy,sizeof(Entropy));

	size_t OutBufferSize = SrcLen + kCCBlockSizeAES128;
	uint8* OutBuffer = (uint8*)FMemory::Malloc(OutBufferSize);
	FMemory::Memset(OutBuffer,0,OutBufferSize);

	size_t BytesDecrypted = 0;
	CCCryptorStatus Status = CCCrypt( kCCDecrypt, kCCAlgorithmAES128,
		kCCOptionPKCS7Padding, Key, kCCKeySizeAES128, NULL, SrcBuffer,
		SrcLen, OutBuffer, OutBufferSize, &BytesDecrypted);
	if (Status == kCCSuccess)
	{
		DestLen = BytesDecrypted;
		FMemory::Memcpy(DestBuffer,OutBuffer,DestLen);
		bDecryptedOk = true;
	}
	else
	{
		UE_LOG(LogTaskBrowser, Log, TEXT("CCCrypt failed w/ 0x%08x"), Status);
	}
	FMemory::Free(OutBuffer);
#elif PLATFORM_LINUX
        printf("STaskBrowser.cpp: LINUX DecryptBuffer()\n");
#elif PLATFORM_WINDOWS
	DATA_BLOB SourceBlob, EntropyBlob, FinalBlob;
	// Set up the datablob to encrypt
	SourceBlob.cbData = SrcLen;
	SourceBlob.pbData = (uint8*)SrcBuffer;
	// Get the mac address for mixing into the entropy (ties the encryption to a location)
	ULONGLONG MacAddress = 0;
	uint32 AddressSize = sizeof(ULONGLONG);
	GetMacAddress((uint8*)&MacAddress,AddressSize);
	// Set up the entropy blob
	ULONGLONG Entropy = 5148284414757334885ui64;
	Entropy ^= MacAddress;
	EntropyBlob.cbData = sizeof(ULONGLONG);
	EntropyBlob.pbData = (uint8*)&Entropy;
	// Zero the output data
	FMemory::Memzero(&FinalBlob,sizeof(DATA_BLOB));
	// Now encrypt the data
	if (CryptUnprotectData(&SourceBlob,
		NULL,
		&EntropyBlob,
		NULL,
		NULL,
		CRYPTPROTECT_UI_FORBIDDEN,
		&FinalBlob))
	{
		if (FinalBlob.cbData <= DestLen)
		{
			// Copy the final results
			DestLen = FinalBlob.cbData;
			FMemory::Memcpy(DestBuffer,FinalBlob.pbData,DestLen);
			bDecryptedOk = true;
		}
		// Free the decryption buffer
		LocalFree(FinalBlob.pbData);
	}
#else
	unimplemented();
#endif
	return bDecryptedOk;
}