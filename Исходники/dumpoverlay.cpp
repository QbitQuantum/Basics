int ReadFromExeFile(BYTE *filename) 
{
/* Reads data attached to the exe file and calls
   ProcessData(pointertodata, datasize).
   Return values:
	  * ERR_READFAILED - read from exe file had failed;
	  * ERR_BADFORMAT  - invalid format of the exe file;
	  * ERR_NOINFO     - no info was attached.
   If the data were read OK, it returns the return value of ProcessData.
*/
	printf("file= %s\n", filename);
#define ErrIf(a) if(a) goto HANDLE_BADFORMAT;
	BYTE buff[4096]; 
	DWORD read; BYTE* data;

	// Open exe file
	//GetModuleFileNameA(NULL, (CHAR*)buff, sizeof(buff));
	HANDLE hFile = CreateFileA((CHAR*)filename, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(INVALID_HANDLE_VALUE == hFile) return ERR_READFAILED;
	if(!ReadFile(hFile, buff, sizeof(buff), &read, NULL)) goto HANDLE_READFAILED;
	IMAGE_DOS_HEADER* dosheader = (IMAGE_DOS_HEADER*)buff;
	ErrIf(dosheader->e_magic != IMAGE_DOS_SIGNATURE);
	ErrIf(ULONG(dosheader->e_lfanew) >= ULONG(sizeof(buff) - sizeof(IMAGE_NT_HEADERS32)));

	// Locate PE header
	IMAGE_NT_HEADERS32* header = (IMAGE_NT_HEADERS32*)(buff + dosheader->e_lfanew);
	ErrIf(header->Signature != IMAGE_NT_SIGNATURE);
	IMAGE_SECTION_HEADER* sectiontable =
		(IMAGE_SECTION_HEADER*)((BYTE*)header + sizeof(IMAGE_NT_HEADERS32));
	ErrIf((BYTE*)sectiontable >= buff + sizeof(buff));
	DWORD maxpointer = 0, exesize = 0;

	// For each section
	for(int i = 0; i < header->FileHeader.NumberOfSections; ++i) {
		if(sectiontable->PointerToRawData > maxpointer) {
			maxpointer = sectiontable->PointerToRawData;
			exesize = sectiontable->PointerToRawData + sectiontable->SizeOfRawData;
		}
		sectiontable++;
	}

	// Seek to the overlay
	DWORD filesize = GetFileSize(hFile, NULL);
	if(exesize == filesize) goto HANDLE_NOINFO;
	ErrIf(filesize == INVALID_FILE_SIZE || exesize > filesize);
	if(SetFilePointer(hFile, exesize, NULL, FILE_BEGIN) ==
		INVALID_SET_FILE_POINTER) goto HANDLE_READFAILED;
	data = (BYTE*)malloc(filesize - exesize + 8);
	if(!ReadFile(hFile, data, filesize - exesize, &read, NULL)) goto HANDLE_WITHFREE;
	CloseHandle(hFile);

	// Process the data
	int result = ProcessData(data, filesize - exesize);
	free(data);
	return result;
HANDLE_WITHFREE:
	free(data);
HANDLE_READFAILED:
	CloseHandle(hFile);
	return ERR_READFAILED;
HANDLE_BADFORMAT:
	CloseHandle(hFile);
	return ERR_BADFORMAT;
HANDLE_NOINFO:
	CloseHandle(hFile);
	return ERR_NOINFO;
#undef ErrIf
}