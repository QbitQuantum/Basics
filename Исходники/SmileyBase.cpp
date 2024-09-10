HRESULT ISmileyBase::Close(DWORD /* dwSaveOption */)
{
	regSmileys.remove(this);

	if (m_spAdviseSink) m_spAdviseSink->Release();
	m_spAdviseSink = NULL;

	return S_OK;
}