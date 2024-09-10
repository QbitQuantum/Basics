void CACMStream::Unprepare()
{
	m_mmr = 0;
	if (m_hdr->fdwStatus & ACMSTREAMHEADER_STATUSF_PREPARED)
	{
		m_hdr->cbSrcLength = m_hdr->dwSrcUser;
		m_mmr = acmStreamUnprepareHeader(m_strm, m_hdr, 0);
		GlobalFree(m_hdr->pbDst);
	}

	if (m_mmr)
		raiseError(m_mmr, 
			"Error unpreparing stream header");
}