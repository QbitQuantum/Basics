// Creates a volume header in memory
int CreateVolumeHeaderInMemory (HWND hwndDlg, BOOL bBoot, char *header, int ea, int mode, Password *password,
		   int pkcs5_prf, char *masterKeydata, PCRYPTO_INFO *retInfo,
		   unsigned __int64 volumeSize, unsigned __int64 hiddenVolumeSize,
		   unsigned __int64 encryptedAreaStart, unsigned __int64 encryptedAreaLength, uint16 requiredProgramVersion, uint32 headerFlags, uint32 sectorSize, BOOL bWipeMode)
{
	unsigned char *p = (unsigned char *) header;
	static KEY_INFO keyInfo;

	int nUserKeyLen = password->Length;
	PCRYPTO_INFO cryptoInfo = crypto_open ();
	static char dk[MASTER_KEYDATA_SIZE];
	int x;
	int retVal = 0;
	int primaryKeyOffset;

	if (cryptoInfo == NULL)
		return ERR_OUTOFMEMORY;

	memset (header, 0, TC_VOLUME_HEADER_EFFECTIVE_SIZE);

	VirtualLock (&keyInfo, sizeof (keyInfo));
	VirtualLock (&dk, sizeof (dk));

	/* Encryption setup */

	if (masterKeydata == NULL)
	{
		// We have no master key data (creating a new volume) so we'll use the TrueCrypt RNG to generate them

		int bytesNeeded;

		switch (mode)
		{

		default:
			bytesNeeded = EAGetKeySize (ea) * 2;	// Size of primary + secondary key(s)
		}

		if (!RandgetBytes (hwndDlg, keyInfo.master_keydata, bytesNeeded, TRUE))
			return ERR_CIPHER_INIT_WEAK_KEY;
	}
	else
	{
		// We already have existing master key data (the header is being re-encrypted)
		memcpy (keyInfo.master_keydata, masterKeydata, MASTER_KEYDATA_SIZE);
	}

	// User key 
	memcpy (keyInfo.userKey, password->Text, nUserKeyLen);
	keyInfo.keyLength = nUserKeyLen;
	keyInfo.noIterations = get_pkcs5_iteration_count (pkcs5_prf, FALSE, bBoot);

	// User selected encryption algorithm
	cryptoInfo->ea = ea;

	// User selected PRF
	cryptoInfo->pkcs5 = pkcs5_prf;
	cryptoInfo->bTrueCryptMode = FALSE;

	// Mode of operation
	cryptoInfo->mode = mode;

	// Salt for header key derivation
	if (!RandgetBytes (hwndDlg, keyInfo.salt, PKCS5_SALT_SIZE, !bWipeMode))
		return ERR_CIPHER_INIT_WEAK_KEY; 

	// PBKDF2 (PKCS5) is used to derive primary header key(s) and secondary header key(s) (XTS) from the password/keyfiles
	switch (pkcs5_prf)
	{
	case SHA512:
		derive_key_sha512 (keyInfo.userKey, keyInfo.keyLength, keyInfo.salt,
			PKCS5_SALT_SIZE, keyInfo.noIterations, dk, GetMaxPkcs5OutSize());
		break;

	case SHA256:
		derive_key_sha256 (keyInfo.userKey, keyInfo.keyLength, keyInfo.salt,
			PKCS5_SALT_SIZE, keyInfo.noIterations, dk, GetMaxPkcs5OutSize());
		break;

	case RIPEMD160:
		derive_key_ripemd160 (keyInfo.userKey, keyInfo.keyLength, keyInfo.salt,
			PKCS5_SALT_SIZE, keyInfo.noIterations, dk, GetMaxPkcs5OutSize());
		break;

	case WHIRLPOOL:
		derive_key_whirlpool (keyInfo.userKey, keyInfo.keyLength, keyInfo.salt,
			PKCS5_SALT_SIZE, keyInfo.noIterations, dk, GetMaxPkcs5OutSize());
		break;

	default:		
		// Unknown/wrong ID
		TC_THROW_FATAL_EXCEPTION;
	} 

	/* Header setup */

	// Salt
	mputBytes (p, keyInfo.salt, PKCS5_SALT_SIZE);	

	// Magic
	mputLong (p, 0x56455241);

	// Header version
	mputWord (p, VOLUME_HEADER_VERSION);
	cryptoInfo->HeaderVersion = VOLUME_HEADER_VERSION;

	// Required program version to handle this volume
	mputWord (p, requiredProgramVersion != 0 ? requiredProgramVersion : TC_VOLUME_MIN_REQUIRED_PROGRAM_VERSION);

	// CRC of the master key data
	x = GetCrc32(keyInfo.master_keydata, MASTER_KEYDATA_SIZE);
	mputLong (p, x);

	// Reserved fields
	p += 2 * 8;

	// Size of hidden volume (if any)
	cryptoInfo->hiddenVolumeSize = hiddenVolumeSize;
	mputInt64 (p, cryptoInfo->hiddenVolumeSize);

	cryptoInfo->hiddenVolume = cryptoInfo->hiddenVolumeSize != 0;

	// Volume size
	cryptoInfo->VolumeSize.Value = volumeSize;
	mputInt64 (p, volumeSize);

	// Encrypted area start
	cryptoInfo->EncryptedAreaStart.Value = encryptedAreaStart;
	mputInt64 (p, encryptedAreaStart);

	// Encrypted area size
	cryptoInfo->EncryptedAreaLength.Value = encryptedAreaLength;
	mputInt64 (p, encryptedAreaLength);

	// Flags
	cryptoInfo->HeaderFlags = headerFlags;
	mputLong (p, headerFlags);

	// Sector size
	if (sectorSize < TC_MIN_VOLUME_SECTOR_SIZE
		|| sectorSize > TC_MAX_VOLUME_SECTOR_SIZE
		|| sectorSize % ENCRYPTION_DATA_UNIT_SIZE != 0)
	{
		TC_THROW_FATAL_EXCEPTION;
	}

	cryptoInfo->SectorSize = sectorSize;
	mputLong (p, sectorSize);

	// CRC of the header fields
	x = GetCrc32 (header + TC_HEADER_OFFSET_MAGIC, TC_HEADER_OFFSET_HEADER_CRC - TC_HEADER_OFFSET_MAGIC);
	p = header + TC_HEADER_OFFSET_HEADER_CRC;
	mputLong (p, x);

	// The master key data
	memcpy (header + HEADER_MASTER_KEYDATA_OFFSET, keyInfo.master_keydata, MASTER_KEYDATA_SIZE);


	/* Header encryption */

	switch (mode)
	{

	default:
		// The secondary key (if cascade, multiple concatenated)
		memcpy (cryptoInfo->k2, dk + EAGetKeySize (cryptoInfo->ea), EAGetKeySize (cryptoInfo->ea));
		primaryKeyOffset = 0;
	}

	retVal = EAInit (cryptoInfo->ea, dk + primaryKeyOffset, cryptoInfo->ks);
	if (retVal != ERR_SUCCESS)
		return retVal;

	// Mode of operation
	if (!EAInitMode (cryptoInfo))
		return ERR_OUTOFMEMORY;


	// Encrypt the entire header (except the salt)
	EncryptBuffer (header + HEADER_ENCRYPTED_DATA_OFFSET,
		HEADER_ENCRYPTED_DATA_SIZE,
		cryptoInfo);


	/* cryptoInfo setup for further use (disk format) */

	// Init with the master key(s) 
	retVal = EAInit (cryptoInfo->ea, keyInfo.master_keydata + primaryKeyOffset, cryptoInfo->ks);
	if (retVal != ERR_SUCCESS)
		return retVal;

	memcpy (cryptoInfo->master_keydata, keyInfo.master_keydata, MASTER_KEYDATA_SIZE);

	switch (cryptoInfo->mode)
	{

	default:
		// The secondary master key (if cascade, multiple concatenated)
		memcpy (cryptoInfo->k2, keyInfo.master_keydata + EAGetKeySize (cryptoInfo->ea), EAGetKeySize (cryptoInfo->ea));
	}

	// Mode of operation
	if (!EAInitMode (cryptoInfo))
		return ERR_OUTOFMEMORY;


#ifdef VOLFORMAT
	if (showKeys && !bInPlaceEncNonSys)
	{
		BOOL dots3 = FALSE;
		int i, j;

		j = EAGetKeySize (ea);

		if (j > NBR_KEY_BYTES_TO_DISPLAY)
		{
			dots3 = TRUE;
			j = NBR_KEY_BYTES_TO_DISPLAY;
		}

		MasterKeyGUIView[0] = 0;
		for (i = 0; i < j; i++)
		{
			char tmp2[8] = {0};
			StringCbPrintfA (tmp2, sizeof(tmp2), "%02X", (int) (unsigned char) keyInfo.master_keydata[i + primaryKeyOffset]);
			StringCbCatA (MasterKeyGUIView, sizeof(MasterKeyGUIView), tmp2);
		}

		HeaderKeyGUIView[0] = 0;
		for (i = 0; i < NBR_KEY_BYTES_TO_DISPLAY; i++)
		{
			char tmp2[8];
			StringCbPrintfA (tmp2, sizeof(tmp2), "%02X", (int) (unsigned char) dk[primaryKeyOffset + i]);
			StringCbCatA (HeaderKeyGUIView, sizeof(HeaderKeyGUIView), tmp2);
		}

		if (dots3)
		{
			DisplayPortionsOfKeys (hHeaderKey, hMasterKey, HeaderKeyGUIView, MasterKeyGUIView, !showKeys);
		}
		else
		{
			SendMessage (hMasterKey, WM_SETTEXT, 0, (LPARAM) MasterKeyGUIView);
			SendMessage (hHeaderKey, WM_SETTEXT, 0, (LPARAM) HeaderKeyGUIView);
		}
	}
#endif	// #ifdef VOLFORMAT

	burn (dk, sizeof(dk));
	burn (&keyInfo, sizeof (keyInfo));

	*retInfo = cryptoInfo;
	return 0;
}