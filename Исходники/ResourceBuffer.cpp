bool ResourceBuffer::GetUInt32(uint32& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint32>(ATOL(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetUInt32 fail!\n");
	return false;
}