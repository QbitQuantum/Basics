HRESULT MuPDFDoc::InitContext()
{
	InitializeCriticalSectionEx(&m_critSec, 0, 0);
	locks.user = &m_critSec;
	locks.lock = lock_mutex;
	locks.unlock = unlock_mutex;
	m_context = fz_new_context(nullptr, &locks, FZ_STORE_DEFAULT);
	if (!m_context)
	{
		return E_OUTOFMEMORY;
	}
	else
	{
		m_cts = (fz_cookie*)CoTaskMemAlloc(sizeof(fz_cookie));
		return S_OK;
	}
}