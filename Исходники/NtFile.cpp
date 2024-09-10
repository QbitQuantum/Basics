void NtFile::ReadBuffer( ntSize length /*= READ_BUF_SIZE*/ )
{
	if (length >= READ_BUF_SIZE)
	{
		return;
	}

	Crt::MemSet(m_readBuffer, sizeof(m_readBuffer));

	fread_s(m_readBuffer, sizeof(m_readBuffer), sizeof(ntWchar) * length, 1, m_fp);
}