void cTimeManager::Update()
{
	DWORD dwCurrTime = GetTickCount();
	m_dwDeltaTime = dwCurrTime - m_dwLastUpdateTime;
	m_dwLastUpdateTime = dwCurrTime;
}