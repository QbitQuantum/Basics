	uint64 DataStream_File::Write(void* buffer, uint64 bytes)
	{
		return fwrite(buffer, size_t(bytes), 1, m_pFile);
	}