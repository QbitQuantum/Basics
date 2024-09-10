void CAviToBmp::Close()
{
	if (m_pGetFrame != NULL)
		AVIStreamGetFrameClose(m_pGetFrame);
	if (m_pStream != NULL)
		AVIStreamRelease(m_pStream);
	if (m_pFile != NULL)
		AVIFileRelease(m_pFile);
	if (m_pBmpInfo != NULL)
		delete m_pBmpInfo;
	Init();
}