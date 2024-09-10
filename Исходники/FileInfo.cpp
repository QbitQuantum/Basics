FileInfo::FileInfo( const Path& path, bool followSymbolicLinks )
{
#if defined(__WIN32__)
	if( _stat64(path.absolute().c_str(), &m_Stat) != -1 )
		return;
#else
	if( followSymbolicLinks )
	{
		if( stat(path.absolute().c_str(), &m_Stat) != -1 )
			return;
	}
	else
	{
		if( lstat(path.absolute().c_str(), &m_Stat) != -1 )
			return;
	}
#endif
	
	std::memset(&m_Stat, 0, sizeof(m_Stat));
}