BOOL SGThumbs::OpenThumbnailFile( CCDiskFile* pFile, const PathName& ThumbFileName ) const
{
	ERROR3IF( pFile==NULL, "SGThumbs::OpenThumbnailFile passed a null ptr" );
	
	TRACEUSER( "Martin", _T("Open thumb file: %s\n"), (const TCHAR *)ThumbFileName.GetPath() );

	BOOL Found = FALSE;

	if(!ThumbFileName.IsValid())
	{
		// either xarainfo\\<filename> or the actual clipart file
		ERROR3("SGThumbs::OpenThumbnailFile received an invalid xarainfo\\<filename> file");
		Error::ClearError();
		return FALSE;
	}

	// Open file and check if it exists at the same time
	if( !( Found = pFile->open( ThumbFileName, ios::in | ios::binary ) ) )
	{
		Found = FALSE;
		Error::ClearError();
	}

	return Found;
}