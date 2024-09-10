VError XWinFileSystemNotification::StartWatchingForChanges( const VFolder &inFolder, VFileSystemNotifier::EventKind inKindFilter, VFileSystemNotifier::IEventHandler *inHandler, sLONG inLatency )
{
	VString path;
	inFolder.GetPath( path );

	VError err = VE_OK;

	// Now that we know we need to care about this folder, let's see if we can create an entry for it.  First,
	// we will try to open a handle to the folder.
	HANDLE hFolder = ::CreateFileW( path.GetCPointer(), FILE_LIST_DIRECTORY | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
						NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, NULL );
	if (hFolder == INVALID_HANDLE_VALUE)
	{
		// We were unable to open the folder, so we need to bail out
		return MAKE_NATIVE_VERROR( ::GetLastError() );
	}

	// launch our task if not already there
	LaunchTaskIfNecessary();

	// Now that we've opened the folder handle, we can add an entry to our watch list
	XWinChangeData *data = new XWinChangeData( inFolder.GetPath(), inKindFilter, VTask::GetCurrent(), inHandler, this);
	data->fFolderHandle = hFolder;
	data->fLatency = inLatency;
	data->fOverlapped.hEvent = ::CreateEvent( NULL, true, false, NULL );
	data->fTimer = NULL;
	if (inLatency)
		data->fTimer = ::CreateWaitableTimer( NULL, FALSE, NULL );

	// Add the new data to our list of things to watch for
	fOwner->PushChangeData( data );

	WatchForChanges( data );

	ReleaseRefCountable( &data);

	return VE_OK;
}