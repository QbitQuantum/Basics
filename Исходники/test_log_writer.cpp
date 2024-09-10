long
TestLogWriter::getUserLogSize( void )
{
	static StatWrapper	swrap;
	if ( NULL == m_options.getLogFile() ) {
		return 0;
	}
	if ( !swrap.IsInitialized() ) {
		swrap.SetPath( m_options.getLogFile() );
	}
	if ( swrap.Stat() ) {
		return -1L;			// What should we do here????
	}
	return swrap.GetBuf()->st_size;
}