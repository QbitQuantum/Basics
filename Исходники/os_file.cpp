void OsFile::flush()
{
	ASSERT(nullptr != m_impl);
	FlushFileBuffers(m_impl->m_file);
}