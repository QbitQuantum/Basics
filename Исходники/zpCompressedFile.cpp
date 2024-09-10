void CompressedFile::seekInPackage(u32 offset)
{
	_fseeki64(m_package->m_stream, m_offset + offset, SEEK_SET);
	m_package->m_lastSeekFile = this;
}