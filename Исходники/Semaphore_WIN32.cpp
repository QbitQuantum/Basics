SemaphoreImpl::SemaphoreImpl(int n, int max)
{
	poco_assert (n >= 0 && max > 0 && n <= max);

	_sema = CreateSemaphoreW(NULL, n, max, NULL);
	if (!_sema)
	{
		throw SystemException("cannot create semaphore");
	}
}