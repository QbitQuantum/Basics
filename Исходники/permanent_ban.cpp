// mark a bnp file without corrupting its datas (this force the patch to be applied the next time the client is launched, thus delaying the trouble maker)
static void markBNPFile(std::string &path)
{
	CRandom rnd;
	rnd.srand((sint32) CTime::getLocalTime());

	uint32 nFileSize=CFile::getFileSize(path);
	if (!nFileSize) return;
	FILE *f = fopen(path.c_str(), "rb+");
	if (!f) return;
// Result
	if (nlfseek64 (f, nFileSize-4, SEEK_SET) != 0)
	{
		fclose (f);
		return;
	}

	uint32 nOffsetFromBeginning;
	if (fread (&nOffsetFromBeginning, sizeof(uint32), 1, f) != 1)
	{
		fclose (f);
		return;
	}

#ifdef NL_BIG_ENDIAN
	NLMISC_BSWAP32(nOffsetFromBeginning);
#endif

	if (nlfseek64 (f, nOffsetFromBeginning, SEEK_SET) != 0)
	{
		fclose (f);
		return;
	}

	// Read the file count
	uint32 nNbFile;
	if (fread (&nNbFile, sizeof(uint32), 1, f) != 1)
	{
		fclose (f);
		return;
	}

#ifdef NL_BIG_ENDIAN
	NLMISC_BSWAP32(nNbFile);
#endif

	for (uint32 i = 0; i < nNbFile; ++i)
	{
		char FileName[MAX_PATH];
		uint8 nStringSize;
		if (fread (&nStringSize, 1, 1, f) != 1)
		{
			fclose(f);
			return;
		}

		sint64 currPos = nlftell64(f);
		if (currPos < 0)
		{
			fclose(f);
			return;
		}
		if (fread (FileName, 1, nStringSize, f) != nStringSize)
		{
			fclose (f);
			return;
		}

		FileName[nStringSize] = 0;

		for(uint k = 0; k < nStringSize; ++k)
		{
			if (rnd.rand() & 1) FileName[k] = toupper(FileName[k]);
			else FileName[k] = tolower(FileName[k]);
		}


		if (nlfseek64 (f, currPos, SEEK_SET) != 0)
		{
			fclose (f);
			return;
		}


		// write shuffled version
		if (fwrite(FileName, 1, nStringSize, f) != nStringSize)
		{
			fclose(f);
			return;
		}
		fflush(f);

		uint32 nFileSize2;
		if (fread (&nFileSize2, sizeof(uint32), 1, f) != 1)
		{
			fclose (f);
			return;
		}

#ifdef NL_BIG_ENDIAN
		NLMISC_BSWAP32(nFileSize2);
#endif

		uint32 nFilePos;
		if (fread (&nFilePos, sizeof(uint32), 1, f) != 1)
		{
			fclose (f);
			return;
		}

#ifdef NL_BIG_ENDIAN
		NLMISC_BSWAP32(nFilePos);
#endif
	}

	fclose (f);
}