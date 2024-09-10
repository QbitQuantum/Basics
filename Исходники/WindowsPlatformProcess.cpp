/**
 * Resolves UNC path to local (full) path if possible.
 *
 * @param	InUNCPath		UNC path to resolve
 *
 * @param	OutPath		Resolved local path
 *
 * @return true if the path was resolved, false otherwise
 */
bool FWindowsPlatformProcess::ResolveNetworkPath( FString InUNCPath, FString& OutPath )
{
	// Get local machine name first and check if this UNC path points to local share
	// (if it's not UNC path it will also fail this check)
	uint32 ComputerNameSize = MAX_COMPUTERNAME_LENGTH;
	TCHAR ComputerName[MAX_COMPUTERNAME_LENGTH + 3] = { '\\', '\\', '\0', };

	if ( GetComputerName( ComputerName + 2, (::DWORD*)&ComputerNameSize ) )
	{
		// Check if the filename is pointing to local shared folder
		if ( InUNCPath.StartsWith( ComputerName ) )
		{
			// Get the share name (it's the first folder after the computer name)
			int32 ComputerNameLen = FCString::Strlen( ComputerName );
			int32 ShareNameLen = InUNCPath.Find( TEXT( "\\" ), ESearchCase::CaseSensitive, ESearchDir::FromStart, ComputerNameLen + 1 ) - ComputerNameLen - 1;
			FString ShareName = InUNCPath.Mid( ComputerNameLen + 1, ShareNameLen );

			// NetShareGetInfo doesn't accept const TCHAR* as the share name so copy to temp array
			SHARE_INFO_2* BufPtr = NULL;
			::NET_API_STATUS res;
			TCHAR ShareNamePtr[MAX_PATH];
			FCString::Strcpy(ShareNamePtr, ShareName.Len() + 1, *ShareName);

			// Call the NetShareGetInfo function, specifying level 2
			if ( ( res = NetShareGetInfo( NULL, ShareNamePtr, 2, (LPBYTE*)&BufPtr ) ) == ERROR_SUCCESS )
			{
				// Construct the local path
				OutPath = FString( BufPtr->shi2_path ) + InUNCPath.Mid( ComputerNameLen + 1 + ShareNameLen );

				// Free the buffer allocated by NetShareGetInfo
				NetApiBufferFree(BufPtr);
				
				return true;
			}
		}
	}

	// InUNCPath is not an UNC path or it's not pointing to local folder or something went wrong in NetShareGetInfo (insufficient privileges?)
	return false;
}