		DWORD TinyMemoryFile::Write(const void* pData, DWORD cbData)
		{
			if (pData == NULL || cbData == 0)
				return FALSE;

			if ((m_dwPosition + cbData) < m_dwPosition)
				return FALSE;

			//超出当前缓冲区大小重新分配大小
			if ((m_dwPosition + cbData) > m_dwBufferSize)
			{
				if (!Realloc((m_dwPosition + cbData)))
					return FALSE;
			}
			memcpy_s((BYTE*)pData + m_dwPosition, cbData, (BYTE*)pData, cbData);
			m_dwPosition += cbData;
			if (m_dwPosition > m_dwBufferSize)
				m_dwBufferSize = m_dwPosition;
			return cbData;
		}