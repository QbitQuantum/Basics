int _osd_sem_init(osd_sem_t *sem, int pshared, int value SEM_FILELINEARGS)
{
	sem_t *s = &sem->posix;
	int rc;
	FUN("osd_sem_init");

	if (NULL == sem) {
		LOG(L_ERROR,("sem is NULL%s\n",
			at_file_line(SEM_FILELINEVARS)));
		errno = EINVAL;
		return -1;
	}
	/* shutting down? */
	if (SHUTDOWN()) {
		return 0;
	}
	if (MY_SEM_MAGIC == sem->magic) {
		LOG(L_ERROR,("sem %p already initialized%s\n",
			sem, at_file_line(SEM_FILELINEVARS)));
		sem->pid = 0;
		/* Destroy and initialize semaphore again */
		sem_destroy(s);
		sem_init(s, 0, value);
		return 0;
	}
	sem->pid = 0;
	rc = sem_init(s, pshared, value);
	if (0 == rc)
		sem->magic = MY_SEM_MAGIC;
	return rc;
}