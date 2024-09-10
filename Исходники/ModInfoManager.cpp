bool GetFileHash(const char *pPath, uint32 &outResult)
{
	if (!gEnv || !gEnv->pCryPak)
	{
		assert(0);
		return false;
	}

	ICryPak* pCryPak = gEnv->pCryPak;

	// Try to open file on disk and hash it (using algorithm taken from CryHashStringId)
	FILE *file = pCryPak->FOpen( pPath,"rb",ICryPak::FOPEN_ONDISK );
	if (file)
	{
		pCryPak->FSeek( file,0,SEEK_END );
		unsigned int nFileSize = pCryPak->FTell(file);
		pCryPak->FSeek( file,0,SEEK_SET );

		outResult = FILE_HASH_SEED;

		unsigned char *pBuf = (unsigned char*)malloc( FILE_CHECK_BUFFER_SIZE );
		if (!pBuf)
		{
			pCryPak->FClose(file);
			return false;
		}

		while (nFileSize)
		{
			unsigned int fetchLength=min(nFileSize,(unsigned int)FILE_CHECK_BUFFER_SIZE);

			unsigned int result = pCryPak->FRead( pBuf,fetchLength,file );
			if (result != fetchLength)
			{
				free( pBuf );
				pCryPak->FClose(file);
				return false;
			}
			
			const char *pChar = (const char*)pBuf;
			for (unsigned int i = 0; i < fetchLength; ++ i, ++ pChar)
			{
				outResult += *pChar;
				outResult += (outResult << 10);
				outResult ^= (outResult >> 6);
			}

			nFileSize-=fetchLength;
		}

		outResult += (outResult << 3);
		outResult ^= (outResult >> 11);
		outResult += (outResult << 15);

		free( pBuf );
		pCryPak->FClose(file);

		return true;
	}

	return false;
}