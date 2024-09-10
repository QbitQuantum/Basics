PHYSFS_sint64 __PHYSFS_platformFileLength(void *opaque)
{
	HANDLE Handle = ((WinApiFile *)opaque)->handle;
	PHYSFS_sint64 retval;

	FILE_STANDARD_INFO file_info = { 0 };
	const BOOL res = GetFileInformationByHandleEx(Handle, FileStandardInfo, &file_info, sizeof(file_info));
	if (res) {
		retval = file_info.EndOfFile.QuadPart;
		assert(retval >= 0);
	}

	return retval;
} /* __PHYSFS_platformFileLength */