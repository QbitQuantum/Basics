	/**
	 * Checks whether the file was completed during last install attempt and adds it to FilesCompleted if so
	 * @param Filename    The filename to check
	 */
	void CheckFile( const FString& Filename )
	{
		// If we had resume data, check file size is correct
		if( bHasResumeData && FilesStarted.Contains( Filename ) )
		{
			const FString FullFilename = StagingDir / Filename;
			const int64 DiskFileSize = IFileManager::Get().FileSize( *FullFilename );
			const int64 CompleteFileSize = BuildManifest->GetFileSize( Filename );
			if( DiskFileSize == CompleteFileSize )
			{
				FilesCompleted.Add( Filename );
			}
			// Sanity check, if file is larger than we expect, that's bad
			else if( DiskFileSize > CompleteFileSize )
			{
				FilesStarted.Remove( Filename );
			}
		}
	}