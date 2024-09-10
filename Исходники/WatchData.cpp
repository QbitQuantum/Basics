WatchData::WatchData(const WCHAR* path, int mask, bool watchSubtree, HANDLE completionPort)
	:
	_watchId(++_counter), 
	_mask(mask), 
	_watchSubtree(watchSubtree),
	_byteReturned(0),
	_completionPort(completionPort)
{
	_path = _wcsdup(path); 
	_hDir = CreateFileW(_path,
						 FILE_LIST_DIRECTORY | GENERIC_READ | GENERIC_WRITE,
						 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
						 NULL, //security attributes
						 OPEN_EXISTING,
						 FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL);
	if(_hDir == INVALID_HANDLE_VALUE )	
	{
		throw GetLastError();
	}
	
	if (NULL == CreateIoCompletionPort(_hDir, _completionPort, (ULONG_PTR)_watchId, 0))
	{
		throw GetLastError();
	}
}