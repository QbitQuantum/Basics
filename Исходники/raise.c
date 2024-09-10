int (raise)(int sig)
	{	/* raise a signal */
	return (_Kill(_Getpid(), sig));
	}