uint64 MFFileNative_GetSize(const char *pFilename)
{
	MFCALLSTACK;

	uint64 fileSize = 0;

#if defined(MF_XBOX) || defined(MF_X360)
	pFilename = FixXBoxFilename(pFilename);
#endif

	HANDLE hFile = CreateFile(MFString_UFT8AsWChar(pFilename), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER size;
		GetFileSizeEx(hFile, &size);
		CloseHandle(hFile);

		fileSize = size.QuadPart;
	}

	return fileSize;
}