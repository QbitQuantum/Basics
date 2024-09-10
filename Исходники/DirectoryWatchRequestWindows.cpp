void FDirectoryWatchRequestWindows::EndWatchRequest()
{
	if ( !bEndWatchRequestInvoked && !bPendingDelete )
	{
		if ( DirectoryHandle != INVALID_HANDLE_VALUE )
		{
#if WINVER >= 0x600		// CancelIoEx() is only supported on Windows Vista and higher
			CancelIoEx(DirectoryHandle, &Overlapped);
#else
			CancelIo(DirectoryHandle);
#endif
			// Clear the handle so we don't setup any more requests, and wait for the operation to finish
			HANDLE TempDirectoryHandle = DirectoryHandle;
			DirectoryHandle = INVALID_HANDLE_VALUE;
			WaitForSingleObjectEx(TempDirectoryHandle, 1000, true);
			
			::CloseHandle(TempDirectoryHandle);
		}
		else
		{
			// The directory handle was never opened
			bPendingDelete = true;
		}

		// Only allow this to be invoked once
		bEndWatchRequestInvoked = true;
	}
}