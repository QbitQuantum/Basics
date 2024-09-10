CPoomAddressbook* CPoomAddressbook::self()
{
	while (InterlockedExchange((LPLONG)&lLock, 1) != 0)
		_Sleep(1);

	if (m_pInstance == NULL)
		m_pInstance = new(std::nothrow) CPoomAddressbook();

	InterlockedExchange((LPLONG)&lLock, 0);

	return m_pInstance;
}