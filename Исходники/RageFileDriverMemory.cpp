int RageFileObjMem::SeekInternal( int offset )
{
	m_iFilePos = clamp( offset, 0, GetFileSize() );
	return m_iFilePos;
}