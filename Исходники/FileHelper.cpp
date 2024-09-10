FilePathType GetFileType(LPCWSTR FilePath)
{
	if(StrEmpty(FilePath))
		return FilePathType::PathNotExist;

	UNICODE_STRING usFileFile;
	if (!RtlDosPathNameToNtPathName_U(FilePath, &usFileFile, NULL, NULL))
	{
		return FilePathType::PathNotExist;
	}


	IO_STATUS_BLOCK IoStatusBlock;

	OBJECT_ATTRIBUTES ObjectAttributes = { sizeof(OBJECT_ATTRIBUTES), NULL, &usFileFile, OBJ_CASE_INSENSITIVE };


	HANDLE hFile;
	auto hr = NtOpenFile(&hFile, SYNCHRONIZE, &ObjectAttributes, &IoStatusBlock, FILE_SHARE_VALID_FLAGS, FILE_SYNCHRONOUS_IO_NONALERT | FILE_DIRECTORY_FILE | FILE_OPEN_FOR_BACKUP_INTENT);

	RtlFreeUnicodeString(&usFileFile);

	switch (hr)
	{
	case 0xC0000103:
		//目录无效，说明是个文件
		return FilePathType::PathIsFile;
#ifdef DEBUG
	case 0xc000003a:
		//系统找不到指定的路径
	case 0xc0000013:
		//设备未就绪。
	case 0xc0000034:
		//系统找不到指定的文件
	case 0xc0000240:
		//请求被终止
		return FilePathType::PathNotExist;
#endif
	case 0:
		//成功打开
		NtClose(hFile);
		return FilePathType::PathIsDir;
	default:
#ifdef DEBUG
		//assert(0);
		SetLastError(RtlNtStatusToDosError(hr));
#endif
		return FilePathType::PathNotExist;
		break;
	}
}