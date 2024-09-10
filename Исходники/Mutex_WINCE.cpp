MutexImpl::MutexImpl(MutexTypeImpl type)
	: _lockCount(0)
	, _recursive(type == MUTEX_RECURSIVE_IMPL)
{
	_mutex = CreateMutexW(NULL, FALSE, NULL);
	if (!_mutex) throw SystemException("cannot create mutex");
}