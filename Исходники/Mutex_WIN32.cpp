MutexImpl::~MutexImpl()
{
	DeleteCriticalSection(&_cs);
}