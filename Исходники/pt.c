int pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	DeleteCriticalSection((_pthread_mutex_t *) mutex);
	return 0;
}