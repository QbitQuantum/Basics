static DWORD _OpenFileById(const HANDLE VolumeHint, const ULONG64 FileId, PHANDLE Handle)
{
	DWORD ret = ERROR_GEN_FAILURE;
	FILE_ID_DESCRIPTOR fdd;
	HANDLE tmpHandle = NULL;

	fdd.dwSize = sizeof(fdd);
	fdd.Type = FileIdType;
	fdd.FileId.QuadPart = FileId | 0x50000000000000;

	tmpHandle = OpenFileById(VolumeHint, &fdd, FILE_READ_ATTRIBUTES | SYNCHRONIZE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, FILE_FLAG_BACKUP_SEMANTICS);
	ret = (tmpHandle != INVALID_HANDLE_VALUE) ? ERROR_SUCCESS : GetLastError();
	if (ret == ERROR_SHARING_VIOLATION) {
		tmpHandle = OpenFileById(VolumeHint, &fdd, FILE_READ_ATTRIBUTES | SYNCHRONIZE, FILE_SHARE_READ, NULL, FILE_FLAG_BACKUP_SEMANTICS);
		ret = (tmpHandle != INVALID_HANDLE_VALUE) ? ERROR_SUCCESS : GetLastError();
	}

	if (ret == ERROR_SHARING_VIOLATION) {
		tmpHandle = OpenFileById(VolumeHint, &fdd, FILE_READ_ATTRIBUTES | SYNCHRONIZE, FILE_SHARE_WRITE, NULL, FILE_FLAG_BACKUP_SEMANTICS);
		ret = (tmpHandle != INVALID_HANDLE_VALUE) ? ERROR_SUCCESS : GetLastError();
	}

	if (ret == ERROR_SUCCESS)
		*Handle = tmpHandle;

	return ret;
}