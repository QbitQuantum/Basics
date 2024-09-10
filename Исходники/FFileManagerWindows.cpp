DWORD FFileManagerWindows::InternalCopy( const TCHAR* DestFile, const TCHAR* SrcFile, UBOOL ReplaceExisting, UBOOL EvenIfReadOnly, UBOOL Attributes, FCopyProgress* Progress )
{
	if( EvenIfReadOnly )
	{
		SetFileAttributesW(DestFile, 0);
	}
	DWORD Result;
	if( Progress )
	{
		Result = FFileManagerGeneric::Copy( DestFile, SrcFile, ReplaceExisting, EvenIfReadOnly, Attributes, Progress );
	}
	else
	{
		MakeDirectory(*FFilename(DestFile).GetPath(), TRUE);
		if( CopyFileW(SrcFile, DestFile, !ReplaceExisting) != 0)
		{
			Result = COPY_OK;
		}
		else
		{
			Result = COPY_MiscFail;
		}
	}
	if( Result==COPY_OK && !Attributes )
	{
		SetFileAttributesW(DestFile, 0);
	}
	return Result;
}