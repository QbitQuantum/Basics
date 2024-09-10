COXIteratorService COXIteratorService::operator+(int nOffset)
{
	ASSERT(m_nPos != OXITERATORSERVICE_POS_NULL);
	if (m_nPos == OXITERATORSERVICE_POS_NULL)
		return *this;

	Empty();
	m_nPos += nOffset;
	if (m_nPos <= -1)
		m_nPos = -1;
	else if (m_nPos >= m_SrvKeyNames.GetSize())
		m_nPos = PtrToInt(m_SrvKeyNames.GetSize());
	else
		m_sKeyName = m_SrvKeyNames[m_nPos];
	return *this;
}