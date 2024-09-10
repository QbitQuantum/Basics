HRESULT EMReadFrameInputPin::SetMediaType(const CMediaType *pmt) 
{	
	CAutoLock cLock(m_pReceiveLock);

	m_pDump->SetMediaType(pmt);
	return CRenderedInputPin::SetMediaType(pmt);
}