GffFileReader::GffFileReader(
	__in const std::string & FileName,
	__in ResourceManager & ResMan
	)
/*++

Routine Description:

	This routine constructs a new GffFileReader object and parses the contents
	of a GFF file by filename.  The file must already exist as it
	immediately deserialized.

Arguments:

	FileName - Supplies the path to the GFF file.

	ResMan - Supplies the resource manager instance that is used to look up
	         STRREFs from talk tables.

Return Value:

	The newly constructed object.

Environment:

	User mode.

--*/
: m_File( INVALID_HANDLE_VALUE ),
  m_FileSize( 0 ),
  m_Language( LangEnglish ),
  m_ResourceManager( ResMan )
{
	HANDLE File;

	File = CreateFileA(
		FileName.c_str( ),
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
		NULL);

	if (File == INVALID_HANDLE_VALUE)
	{
		File = CreateFileA(
			FileName.c_str( ),
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
			NULL);

		if (File == INVALID_HANDLE_VALUE)
			throw std::exception( "Failed to open GFF file." );
	}

	m_File = File;

	m_FileWrapper.SetFileHandle( File );

	try
	{
		m_FileSize = GetFileSize( File, NULL );

		if ((m_FileSize == 0xFFFFFFFF) && (GetLastError( ) != NO_ERROR))
			throw std::exception( "Failed to read file size." );

		ParseGffFile( );
	}
	catch (...)
	{
		m_File = INVALID_HANDLE_VALUE;

		CloseHandle( File );

		m_FileWrapper.SetFileHandle( INVALID_HANDLE_VALUE );

		throw;
	}
}