/** Send a kill signal to a windows version of GridLAB-D
    @return 0 on successfull completion, -1 on error (e.g., no such signal, no such process)
 **/
int kill(pid_t pid,	/**< the window process id */
		 int sig)				/**< the signal id (see signal.h) */
{
	char name[32];
	HANDLE hEvent;
	sprintf(name,"gridlabd.%u.%u",pid,sig==0?SIGINT:sig); /* use INT for sig==0 just to check */
	hEvent = OpenEventA(EVENT_MODIFY_STATE,FALSE,name);
	
	/* existence check only */
	if ( sig==0 )
	{
		if ( hEvent!=NULL )
		{
			CloseHandle(hEvent);
			return 0;
		}
		else
		{
			errno = ESRCH;
			return -1;
		}
	}

	/* valid signal needs to be sent */
	else if (hEvent==NULL)
	{
		errno = EINVAL; // TODO distinguish between bad signal and bad pid
		output_error("unable to signal gridlabd process %d with signal %d (error %d)", pid, sig, GetLastError());
		return -1;
	}
	else 
	{
		SetEvent(hEvent);
		output_verbose("signal %d sent to gridlabd process %d", sig, pid);
		CloseHandle(hEvent);
		return 0;
	}
}