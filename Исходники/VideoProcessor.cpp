CVideoProcessor::~CVideoProcessor()
{
	DeleteCriticalSection(&m_csLock);
}