void FDirectoryWatcherWindows::Tick( float DeltaSeconds )
{
	TArray<HANDLE> DirectoryHandles;
	TMap<FString, FDirectoryWatchRequestWindows*> InvalidRequestsToDelete;

	// Find all handles to listen to and invalid requests to delete
	for (TMap<FString, FDirectoryWatchRequestWindows*>::TConstIterator RequestIt(RequestMap); RequestIt; ++RequestIt)
	{
		if ( RequestIt.Value()->IsPendingDelete() )
		{
			InvalidRequestsToDelete.Add(RequestIt.Key(), RequestIt.Value());
		}
		else
		{
			DirectoryHandles.Add(RequestIt.Value()->GetDirectoryHandle());
		}
	}

	// Remove all invalid requests from the request map and add them to the pending delete list so they will be deleted below
	for (TMap<FString, FDirectoryWatchRequestWindows*>::TConstIterator RequestIt(InvalidRequestsToDelete); RequestIt; ++RequestIt)
	{
		RequestMap.Remove(RequestIt.Key());
		RequestsPendingDelete.AddUnique(RequestIt.Value());
	}

	// Trigger any file changed delegates that are queued up
	if ( DirectoryHandles.Num() > 0 )
	{
		MsgWaitForMultipleObjectsEx(DirectoryHandles.Num(), DirectoryHandles.GetData(), 0, QS_ALLEVENTS, MWMO_ALERTABLE);
	}

	// Delete any stale or invalid requests
	for ( int32 RequestIdx = RequestsPendingDelete.Num() - 1; RequestIdx >= 0; --RequestIdx )
	{
		FDirectoryWatchRequestWindows* Request = RequestsPendingDelete[RequestIdx];

		if ( Request->IsPendingDelete() )
		{
			// This request is safe to delete. Delete and remove it from the list
			delete Request;
			NumRequests--;
			RequestsPendingDelete.RemoveAt(RequestIdx);
		}
	}

	// Finally, trigger any file change notification delegates
	for (TMap<FString, FDirectoryWatchRequestWindows*>::TConstIterator RequestIt(RequestMap); RequestIt; ++RequestIt)
	{
		RequestIt.Value()->ProcessPendingNotifications();
	}
}