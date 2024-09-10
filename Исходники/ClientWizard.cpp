CClientWizard::~CClientWizard()
{
	ShutDown();

	DeleteCriticalSection(&m_csHostList);
	DeleteCriticalSection(&m_csDecomposer);
}