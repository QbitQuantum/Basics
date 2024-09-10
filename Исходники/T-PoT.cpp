// FsRenMovFile is called to transfer (copy or move) a file within the 
// plugin's file system.
//
int __stdcall FsRenMovFile(char *OldName, char *NewName, BOOL Move, BOOL OverWrite, RemoteInfoStruct *ri)
{
	t_iPodError status = iPodApi.OpenSession();
	CString BSDOldPath(OldName), BSDNewPath(NewName);
	t_MachError ret;

	BSDOldPath.Replace('\\', '/');
	BSDNewPath.Replace('\\', '/');
	if (!Move) {
		// Does a combination of AFCFileRefRead and AFCFileRefWrite,
		// a little silly as we lose the file attributes on the way.
		CString LocalCopy;
		
		iPodApi.GetTempFilename(LocalCopy);
		if (iPodApi.FileRead(BSDOldPath.GetBuffer(), LocalCopy.GetBuffer()) != FS_FILE_OK)
			return FS_FILE_READERROR;
		ret = iPodApi.FileWrite(BSDNewPath.GetBuffer(), LocalCopy.GetBuffer());
		_unlink(LocalCopy);
		return ret;
	}
	bAborted = false;
	if (status == IPOD_ERR_OK) {
		
		if (!OverWrite) {
			if (iPodApi.FileExists(BSDNewPath.GetBuffer()))
				// Files exists, unfortunately we can't check the write permission
				// so asks the user's decision
				return FS_FILE_EXISTSRESUMEALLOWED;			
		}
		ret = iPodApi.Move(BSDOldPath.GetBuffer(), BSDNewPath.GetBuffer());
		return (ret == FS_FILE_OK) ? FS_FILE_OK : FS_FILE_READERROR;
	}
	return FS_FILE_READERROR;
}