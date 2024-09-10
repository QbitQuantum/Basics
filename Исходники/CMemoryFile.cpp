	Bool CMemoryFile::Open(const AString& sFile)
	{
		Close();

		m_eOpenType = OPEN_READ;
		m_bExtra    = false;

		CDiskFile df;
		if (df.Open(sFile))
		{
			m_iFileSize = df.GetFileSize();

			m_pData = (Char*)malloc((Size_t)m_iFileSize);
			memset(m_pData, 0, (Size_t)m_iFileSize);

			df.Read(m_pData, m_iFileSize);
			return true;
		}
		return false;
	}