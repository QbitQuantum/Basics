	SHMEMHandle AttachShareMem(SHMEMKey keyShmem, INT iSize)
	{
#ifdef WIN32
		char keybuf[32] = { 0 };
		sprintf_s(keybuf, "%d", keyShmem);
		return OpenFileMappingA(FILE_MAP_ALL_ACCESS, TRUE, keybuf);
#else
		return shmget(keyShmem, iSize, 0);
#endif
	}