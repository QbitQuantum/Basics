DWORD
AG_XBOX_GetXbeTitleId(const char *xbePath)
{
	HANDLE h;
	DWORD titleId = -1;
	DWORD loadAddress;
	DWORD certLocation;
	DWORD bytesRead;
	ANSI_STRING file;
	OBJECT_ATTRIBUTES attr;
	IO_STATUS_BLOCK status;

	if(!xbePath)
		return -1;

	RtlInitAnsiString(&file, xbePath);

	InitializeObjectAttributes(&attr, &file, OBJ_CASE_INSENSITIVE, NULL);

	if(SUCCEEDED(NtCreateFile(&h, FILE_GENERIC_READ, &attr, &status,
	                           NULL, 0, 0, FILE_OPEN,
	                           FILE_NON_DIRECTORY_FILE | FILE_SYNCHRONOUS_IO_NONALERT))) {
		if(SetFilePointer(h,  0x104, NULL, FILE_BEGIN) == 0x104) {
			ReadFile(h, &loadAddress, sizeof(DWORD), &bytesRead, NULL);
			if(bytesRead == sizeof(DWORD)) {
				if(SetFilePointer(h, 0x118, NULL, FILE_BEGIN ) == 0x118) {
					ReadFile(h, &certLocation, sizeof(DWORD), &bytesRead, NULL);
					if(bytesRead == sizeof(DWORD)) {
						certLocation -= loadAddress;
						certLocation += 8;
						titleId = 0;
						if(SetFilePointer(h, certLocation, NULL, FILE_BEGIN) == certLocation) {
							ReadFile(h, &titleId, sizeof(DWORD), &bytesRead, NULL);
							if(bytesRead != sizeof(DWORD)) {
								titleId = 0;
							}
						}
					}
				}
			}
		}
		CloseHandle(h);
	}

	return titleId;
}