int  os_sem_post(os_sem_t *sem)
{
	if (!sem) return -1;
	return ReleaseSemaphore(sem->handle, 1, NULL) ? 0 : -1;
}