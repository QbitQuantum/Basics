unsigned int CFileWatcher::Worker(void* arg)
{
	CFileWatcher* watcher = (CFileWatcher*)arg;
	DWORD error;
	DWORD bytes;
	ULONG_PTR key;
	LPOVERLAPPED overlapped;

	while (TRUE)
	{
		error = S_OK;
		if (!GetQueuedCompletionStatus(
			watcher->completionPort, &bytes, &key, &overlapped, watcher->uncFileSharePollingInterval))
		{
			error = GetLastError();
		}

		if (-1L == key) // terminate thread
		{
			break;
		}
		else if (S_OK == error) // a change in registered directory detected (local file system)
		{
			WatchedDirectory* directory = (WatchedDirectory*)key;
			
			watcher->ScanDirectory(directory, FALSE);

			RtlZeroMemory(&directory->overlapped, sizeof directory->overlapped);
			ReadDirectoryChangesW(
				directory->watchHandle,
				&directory->info,
				sizeof directory->info,
				FALSE,
				FILE_NOTIFY_CHANGE_LAST_WRITE,
				NULL,
				&directory->overlapped,
				NULL);
		}
		else // timeout - scan all registered UNC files for changes
		{
			WatchedDirectory* current = watcher->directories;
			while (current)
			{
				watcher->ScanDirectory(current, TRUE);
				current = current->next;
			}
		}		
	}

	return 0;
}