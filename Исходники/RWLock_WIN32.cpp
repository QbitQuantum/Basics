RWLockImpl::RWLockImpl(): _readers(0), _writersWaiting(0), _writers(0)
{
	_mutex = CreateMutexW(NULL, FALSE, NULL);
	if (_mutex == NULL)
		throw SystemException("cannot create reader/writer lock");

	_readEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
	if (_readEvent == NULL)
		throw SystemException("cannot create reader/writer lock");

	_writeEvent = CreateEventW(NULL, TRUE, TRUE, NULL);
	if (_writeEvent == NULL)
		throw SystemException("cannot create reader/writer lock");
}