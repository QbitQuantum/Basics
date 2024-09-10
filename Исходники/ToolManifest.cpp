// LoadFile
//------------------------------------------------------------------------------
bool ToolManifest::LoadFile( const AString & fileName, void * & content, uint32_t & contentSize ) const
{
	// read the file into memory
	FileStream fs;
	if ( fs.Open( fileName.Get(), FileStream::READ_ONLY ) == false )
	{
		FLOG_ERROR( "Error opening file '%s' in Compiler ToolManifest\n", fileName.Get() );
		return false;
	}
	contentSize = (uint32_t)fs.GetFileSize();
	AutoPtr< void > mem( ALLOC( contentSize ) );
	if ( fs.Read( mem.Get(), contentSize ) != contentSize )
	{
		FLOG_ERROR( "Error reading file '%s' in Compiler ToolManifest\n", fileName.Get() );
		return false;
	}

	content = mem.Release();
	return true;
}