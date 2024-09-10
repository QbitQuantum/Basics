void
sys_init(void)
{
	int i;
	Timeout**	ppTimeout=&pFreeTimeouts;

	dbgprintf("sys_init: Initializing (TID: %d)\n",GetThreadId());

	for(i = 0; i < SYS_MAX_MESSAGES; i++)
	{
	    msg_pool[i].next = NULL;
	    msg_pool[i].sys_msg = NULL;
	}


	for	(i = 0; i < SYS_TIMEOUT_MAX; i++)
	{
		Timeout*		pTimeout=&aTimeouts[i];

		*ppTimeout=pTimeout;
		ppTimeout=&pTimeout->pNext;
	}

	*ppTimeout=NULL;
}