TSync::TSync()
{
	this->m_nLock=0;
	InitializeCriticalSection(&this->m_cs);
}