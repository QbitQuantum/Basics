void 
CipherContext::InitContext(
	PGPdiskEncryptionAlgorithm	algorithm, 
	const PGPUInt8				*key, 
	const PGPUInt8				*salt)
{
	PGPUInt32 i;

	pgpAssert(algorithm != kInvalidEncryptionAlgorithm);

	DestroyContext();
	mAlgorithm = algorithm;

	switch (mAlgorithm)
	{

	case kBrokenCASTEncryptionAlgorithm:
		pgpAssertAddrValid(salt, PGPUInt8);
		pgpAssertAddrValid(key, PGPUInt8);

		pgpCopyMemory(salt, mSalt.saltBytes, sizeof(mSalt.saltBytes));
		pgpCopyMemory(key, mCastCFB.expandedKey.keyBytes, 16);

#if PGP_USE_ASSEMBLY

		// The key schedule for assembly must be slightly different. The
		// rotate subkeys (every second word) must be XORed with 16. This
		// swaps the halves of some words internally in a way that the code
		// expects. Don't forget this!

		for (i=0; i<32; i+=2)
		{
			mCastCFB.expandedKey.keyDWords[i+1] = 
				mCastCFB.expandedKey.keyDWords[i+1] ^ 16;
		}

#else	// ] !PGP_USE_ASSEMBLY

		i;	// get rid of unreferenced local variable error

#endif	// ] PGP_USE_ASSEMBLY

		mInitialized = TRUE;
		break;

	case kCASTEncryptionAlgorithm:
		pgpAssertAddrValid(salt, PGPUInt8);
		pgpAssertAddrValid(key, PGPUInt8);

		pgpCopyMemory(salt, mSalt.saltBytes, sizeof(mSalt.saltBytes));

		// Expand the key.
		CAST5schedule(mCastCFB.expandedKey.keyDWords, key);

#if PGP_USE_ASSEMBLY

		// The key schedule for assembly must be slightly different. The
		// rotate subkeys (every second word) must be XORed with 16. This
		// swaps the halves of some words internally in a way that the code
		// expects. Don't forget this!

		for (i=0; i<32; i+=2)
		{
			mCastCFB.expandedKey.keyDWords[i+1] = 
				mCastCFB.expandedKey.keyDWords[i+1] ^ 16;
		}

#else	// ] !PGP_USE_ASSEMBLY

		i;	// get rid of unreferenced local variable error

#endif	// ] PGP_USE_ASSEMBLY

		mInitialized = TRUE;
		break;

	case kCopyDataEncryptionAlgorithm:
		mInitialized = TRUE;
		break;

	default:
		pgpAssert(FALSE);
		break;
	}
}