VError XWinFolder::MoveToTrash() const
{
	// don't use XWinFullPath because SHFileOperation fails on any path prefixed with "\\?\".
	
	// the path parameter is actually a paths list and must be double null terminated.
	// so one must copy the path in a temp buffer.
	UniChar *path = (UniChar*) calloc( fOwner->GetPath().GetPath().GetLength() + 2, sizeof( UniChar));
	if (path == NULL)
		return MAKE_NATIVE_VERROR( ERROR_NOT_ENOUGH_MEMORY);
	
	wcscpy( path, fOwner->GetPath().GetPath().GetCPointer());
	
	SHFILEOPSTRUCTW  info;
	memset( &info, 0, sizeof(info));

	info.fFlags |= FOF_SILENT;				// don't report progress
	info.fFlags |= FOF_NOERRORUI;			// don't report errors
	info.fFlags |= FOF_NOCONFIRMATION;		// don't confirm delete
	info.fFlags |= FOF_ALLOWUNDO;			// move to recycle bin
	info.fFlags |= FOF_NOCONFIRMMKDIR;
	info.fFlags |= FOF_RENAMEONCOLLISION; 
	info.wFunc = FO_DELETE;                   // required: delete operation
	info.pTo = NULL;                          // must be NULL
	info.pFrom = path; 

	VError err;
	int result = SHFileOperationW( &info);
	if (result != 0)
	{
		// unfortunately, GetLastError() is unusable here.
		// and the result code is poorly documented.
		switch( result)
		{
			case 0x7C /*DE_INVALIDFILES*/:	err = MAKE_NATIVE_VERROR( ERROR_PATH_NOT_FOUND); break;
			default:				err = MAKE_NATIVE_VERROR( ERROR_INVALID_PARAMETER); break;
		}
	}
	else
	{
		err = VE_OK;
	}
	
	free( path);
	
	return err;
}