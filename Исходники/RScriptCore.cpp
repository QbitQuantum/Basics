HRESULT CRScriptCore::FinalConstruct()
{
	s_crit.Lock();
	m_lCookie = ++s_lCookie;	// for WIN95 - InterlockedIncrement(&s_lCookie);
	if (m_lCookie >= FIXNUM_MAX)
	{
		m_lCookie = s_lCookie = 0;
	}
	s_listEngine.push_front(this);
	s_crit.Unlock();
	return CoCreateFreeThreadedMarshaler(
		GetControllingUnknown(), &m_pUnkMarshaler.p);
}