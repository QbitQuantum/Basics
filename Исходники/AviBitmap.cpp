void CAviBitmap::ReleaseMemory()
{
	if(m_pGetFrame != NULL)
	{
		AVIStreamGetFrameClose(m_pGetFrame);
		m_pGetFrame = NULL;
	}

	if(m_pAviStream != NULL)
	{
		AVIStreamRelease(m_pAviStream);
		m_pAviStream = NULL;
	}

	if(m_pAviFile != NULL)
	{
		AVIFileRelease(m_pAviFile);
		m_pAviFile = NULL;
	}

	m_lFirstSample = 0;
	m_lSampleCount = 0;
}