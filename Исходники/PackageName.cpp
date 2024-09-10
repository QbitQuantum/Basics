	// This will remove a previously inserted mount point
	void RemoveMountPoint(const FString& RootPath, const FString& ContentPath)
	{
		// Make sure the content path is stored as a relative path, consistent with the other paths we have
		FString RelativeContentPath = IFileManager::Get().ConvertToRelativePath(*ContentPath);

		// Make sure the path ends in a trailing path separator.  We are expecting that in the InternalFilenameToLongPackageName code.
		if (!RelativeContentPath.EndsWith(TEXT("/")))
		{
			RelativeContentPath += TEXT("/");
		}

		if ( MountPointRootPaths.Remove(RootPath) > 0 )
		{
			FPathPair Pair(RootPath, RelativeContentPath);
			ContentRootToPath.Remove(Pair);
			ContentPathToRoot.Remove(Pair);
			MountPointRootPaths.Remove(RootPath);

			// Let subscribers know that a new content path was mounted
			FPackageName::OnContentPathDismounted().Broadcast( RootPath, ContentPath );
		}
	}