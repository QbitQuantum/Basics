HMODULE WINAPI MonoLoadImage(LPCWSTR FileName)
{
	HANDLE FileHandle;
	DWORD FileSize;
	HANDLE MapHandle;
	IMAGE_DOS_HEADER* DosHeader;
	IMAGE_NT_HEADERS32* NtHeaders32;
#ifdef _WIN64
	IMAGE_NT_HEADERS64* NtHeaders64;
#endif
	HMODULE ModuleHandle;

	FileHandle = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return NULL;

	FileSize = GetFileSize(FileHandle, NULL); 
	if (FileSize == INVALID_FILE_SIZE)
		goto CloseFile;

	MapHandle = CreateFileMapping(FileHandle, NULL, PAGE_READONLY, 0, 0, NULL);
	if (MapHandle == NULL)
		goto CloseFile;

	DosHeader = (IMAGE_DOS_HEADER*)MapViewOfFile(MapHandle, FILE_MAP_READ, 0, 0, 0);
	if (DosHeader == NULL)
		goto CloseMap;

	if (FileSize < sizeof(IMAGE_DOS_HEADER) || DosHeader->e_magic != IMAGE_DOS_SIGNATURE || FileSize < DosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS32))
		goto InvalidImageFormat;

	NtHeaders32 = (IMAGE_NT_HEADERS32*)((DWORD_PTR)DosHeader + DosHeader->e_lfanew);
	if (NtHeaders32->Signature != IMAGE_NT_SIGNATURE)
		goto InvalidImageFormat;

#ifdef _WIN64
	NtHeaders64 = (IMAGE_NT_HEADERS64*)NtHeaders32;
	if (NtHeaders64->OptionalHeader.Magic == IMAGE_NT_OPTIONAL_HDR64_MAGIC)
	{
		if (FileSize < DosHeader->e_lfanew + sizeof(IMAGE_NT_HEADERS64) ||
			NtHeaders64->OptionalHeader.NumberOfRvaAndSizes <= IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ||
			!NtHeaders64->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress)
				goto InvalidImageFormat;

		goto ValidImage;
	}
#endif

	if (NtHeaders32->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC ||
		NtHeaders32->OptionalHeader.NumberOfRvaAndSizes <= IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR ||
		!NtHeaders32->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR].VirtualAddress)
	{
InvalidImageFormat:
		SetLastError(STATUS_INVALID_IMAGE_FORMAT);
		goto UnmapView;
	}

#ifdef _WIN64
ValidImage:
#endif
	UnmapViewOfFile(DosHeader);
	CloseHandle(MapHandle);

	ModuleHandle = LoadLibrary(FileName);

	CloseHandle(FileHandle);
	return ModuleHandle;

UnmapView:
	UnmapViewOfFile(DosHeader);
CloseMap:
	CloseHandle(MapHandle);
CloseFile:
	CloseHandle(FileHandle);
	return NULL;
}