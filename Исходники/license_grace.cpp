/*
char GracePeriodStore[GRACE_PERIOD_STORE_SIZE] = "RoundBrownFoxJumpedTheFence";
int LoadCurrectGracePeriodDataDLL(GraceStatusResourceStore *StaticDLLResourceDataInFile, long *StaticDataStoredAt)
{
	//make sure we do not return uninitialized values
	memset(StaticDLLResourceDataInFile, 0, sizeof(GraceStatusResourceStore));

	//open self DLL
	FILE *f;
	errno_t er = fopen_s(&f, "LicenseDLL.dll", "rb");
	if (er != NO_ERROR)
		return er;

	if (f == NULL)
		return ERROR_FILE_INVALID;

	GraceStatusResourceStore *StaticDLLResourceDataInMemory = (GraceStatusResourceStore *)GracePeriodStore;

	//search for our resource store header
#define FileReadBlockSize (10 * 1024 * 1024)		//our dll file should be about 150k
	int FileSize = GetFileSize("LicenseDLL.dll");
	if (FileSize <= 0)
		FileSize = FileReadBlockSize;
	unsigned char *FileContentBuffered = (unsigned char *)malloc(FileSize);
	size_t ReadCount = fread_s(FileContentBuffered, FileSize, 1, FileSize, f);
	*StaticDataStoredAt = 0;
	for (size_t i = 0; i < ReadCount; i++)
		if (memcmp(&FileContentBuffered[i], StaticDLLResourceDataInMemory->Header, sizeof(StaticDLLResourceDataInMemory->Header)) == 0)
		{
			if (StaticDLLResourceDataInFile != NULL)
				memcpy(StaticDLLResourceDataInFile, &FileContentBuffered[i], sizeof(GraceStatusResourceStore));
			*StaticDataStoredAt = i;
			break;
		}
	free(FileContentBuffered);
	fclose(f);

	//if data is encoded, decode it
	int erEncrypt = CODECGraceData(StaticDLLResourceDataInFile, 0);

	//pass through errors
	return erEncrypt;
}
*/
int LoadCurrectGracePeriodDataFile(const char *FileName,GraceStatusResourceStore *StaticDLLResourceDataInFile)
{
	//make sure we do not return uninitialized values
	memset(StaticDLLResourceDataInFile, 0, sizeof(GraceStatusResourceStore));
	FILE *f;
	errno_t er = fopen_s(&f, FileName, "rb");
	if (er != NO_ERROR)
		return er;

	if (f == NULL)
		return ERROR_FILE_INVALID;

	size_t ReadCount = fread_s(StaticDLLResourceDataInFile, sizeof(GraceStatusResourceStore), 1, sizeof(GraceStatusResourceStore), f);
	fclose(f);
	if (ReadCount != sizeof(GraceStatusResourceStore))
		return ERROR_COULD_NOT_LOAD_GRACE_DATA;

	//if data is encoded, decode it
	int erEncrypt = CODECGraceData(StaticDLLResourceDataInFile, 0);
	if (erEncrypt == 0)
	{
		if (StaticDLLResourceDataInFile->IsFileInitialized != 1 || StaticDLLResourceDataInFile->StoreVersion != GRACE_STORE_VERSION)
			return ERROR_STORE_VERSION_MISMATCH;
	}

	//pass through errors
	return erEncrypt;
}