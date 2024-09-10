STDMETHODIMP CStreamSwitcherInputPin::NotifyEndOfStream(HANDLE hNotifyEvent)
{
	if(m_hNotifyEvent) SetEvent(m_hNotifyEvent);
	m_hNotifyEvent = hNotifyEvent;
	return S_OK;
}