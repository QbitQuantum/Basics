BOOL FileLockThread::ReleaseFileLock()
{
	for (auto it = fileHandles.begin(); it != fileHandles.end(); it++)
	{
		if (UnlockFile(*it, 0, 0, GetFileSize(*it, 0), 0) != 0)
			::CloseHandle(*it);
	}
	fileHandles.clear();
	return TRUE;
}