int COXWatchBuffer::GetUnmodified() const
{
	ASSERT_VALID(this);
	ASSERT(sizeof(BYTE) == 1);
	LPBYTE pModified = (LPBYTE)memchr(m_pFlags, FALSE, m_nLength);
	if (pModified != NULL)
		return PtrToInt(pModified - m_pFlags);
	else
		return -1;
}