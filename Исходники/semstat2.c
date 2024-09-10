int main (int argc, char *argv[])
{
	int 		i, j;
	char 		s[81];
	int 		sem, semval, semncnt, semzcnt, sempid;
	struct	 	sembuf sop;
	struct semid_ds		semstat;
	union semun	semarg;

	if (argc == 1)
	{
		usage(argv[0]);
		exit(1);
	}
	semarg.buf = &semstat;
	for(i=1; i< argc; i++)
	{

		sem = ATOI(argv[i]);
		if ( semctl(sem, 0, IPC_STAT, semarg) == -1 )
		{
			FPRINTF(stderr, "Error obtaining semaphore status.\n");
			SPRINTF(s, "semctl(%d)", sem);
			PERROR(s);
			continue;
		}
		PRINTF("semid %d: %hu semaphores in the set\n", sem, (unsigned short int)semarg.buf->sem_nsems);
		for(j=0; j < semarg.buf->sem_nsems; j++)
		{

			if ( (semval = semctl(sem, j, GETVAL)) == -1 )
			{
				FPRINTF(stderr, "Error obtaining semaphore %d value.\n", j);
				SPRINTF(s, "semctl(%d)", sem);
				PERROR(s);
				continue;
			}
			PRINTF("sem %d: (semval=%d, ", j, semval);
			if ( (semncnt = semctl(sem, j, GETNCNT)) == -1 )
			{
				FPRINTF(stderr, "\nError obtaining semaphore %d ncnt.\n", j);
				SPRINTF(s, "semctl(%d)", sem);
				PERROR(s);
				continue;
			}
			PRINTF("semncnt=%d, ", semncnt);
			if ( (semzcnt = semctl(sem, j, GETZCNT)) == -1 )
			{
				FPRINTF(stderr, "\nError obtaining semaphore %d zcnt.\n", j);
				SPRINTF(s, "semctl(%d)", sem);
				PERROR(s);
				continue;
			}
			PRINTF("semzcnt=%d, ", semzcnt);
			if ( (sempid= semctl(sem, j, GETPID)) == -1 )
			{
				FPRINTF(stderr, "\nError obtaining semaphore %d PID.\n", j);
				SPRINTF(s, "semctl(%d)", sem);
				PERROR(s);
				continue;
			}
			PRINTF("sempid=%d)\n", sempid);
		}
	}
	exit(0);
}