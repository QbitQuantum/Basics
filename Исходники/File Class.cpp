ULONG CFile::GetLength() const
{
	return GetFileSize(m_hFile,0);
}