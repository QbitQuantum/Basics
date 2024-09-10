void CMmio::AscendList ()
{

	ASSERT (m_hMmio != NULL);
	ASSERT_VALID (this);
	ASSERT (m_iListDepth > 0);

	if (mmioAscend (m_hMmio, &m_mckiList[m_iListDepth-1], 0) != 0)
		{
		ThrowError (ERR_MMIO_ASCEND_LIST);
		}

	m_iListDepth--;
}