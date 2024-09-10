bool CGZIPFile::Open(LPCTSTR pszFilePath)
{
	ASSERT( m_gzFile == 0 );
	Close();

	USES_CONVERSION;
	m_gzFile = gzopen(T2CA(pszFilePath), "rb");
	if (m_gzFile)
		m_strGzFilePath = pszFilePath;
	return m_gzFile != 0;
}