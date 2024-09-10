// Open
//------------------------------------------------------------------------------
void SharedMemory::Open( const char * name, unsigned int size )
{
	#if defined( __WINDOWS__ )
		m_MapFile = OpenFileMappingA( FILE_MAP_ALL_ACCESS,	// read/write access
										FALSE,				// do not inherit the name
										name );               // name of mapping object
		if ( m_MapFile )
		{
			m_Memory = MapViewOfFile( m_MapFile,			// handle to map object
									  FILE_MAP_ALL_ACCESS,  // read/write permission
									  0,					// DWORD dwFileOffsetHigh
									  0,					// DWORD dwFileOffsetLow
									  size );
		}
	#elif defined( __APPLE__ )
		// TODO:MAC Implement SharedMemory
	#elif defined( __LINUX__ )
		// TODO:LINUX Implement SharedMemory
	#else
		#error
	#endif
}