int create_server(void)
{
	int		child_pid, done_pid, status = 0;
#	ifdef _BSD
	union	wait	chld_status;
#	define CSTAT	chld_status
#	else
#	define CSTAT	status
#	endif
	int		save_errno;

	FORK(child_pid);
	if (0 == child_pid)
	{
		process_id = getpid();
		/* Do exec using gtmsecshr_path, which was initialize in file check code - send_mesg2gtmsecshr */
		if (WBTEST_ENABLED(WBTEST_BADEXEC_SECSHR_PROCESS))
			STRCPY(gtmsecshr_path, "");
		status = EXECL(gtmsecshr_path, gtmsecshr_path, 0);
		if (-1 == status)
		{
			send_msg_csa(CSA_ARG(NULL) VARLSTCNT(9) ERR_GTMSECSHRSTART, 3, RTS_ERROR_TEXT("Client"), process_id,
				ERR_TEXT, 2, RTS_ERROR_STRING(secshrstart_error_code[UNABLETOEXECGTMSECSHR]));
			UNDERSCORE_EXIT(UNABLETOEXECGTMSECSHR);
		}
        } else
	{
		if (-1 == child_pid)
		{
			status = GNDCHLDFORKFLD;
			gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(10) ERR_GTMSECSHRSTART, 3, RTS_ERROR_TEXT("Client"), process_id,
				   ERR_TEXT,  2, RTS_ERROR_TEXT("Failed to fork off gtmsecshr"), errno);
			/* Sleep for a while and hope a subsequent fork will succeed */
			hiber_start(1000);
		}
		for (; !status ;)
		{
			/* To prevent a warning message that the compiler issues */
			done_pid = wait(&CSTAT);
			if (done_pid == child_pid)
			{
				status = WEXITSTATUS(CSTAT);
				break;
			} else if (-1 == done_pid)
			{
				if (ECHILD == errno) /* Assume normal exit status */
					break;
				else if (EINTR != errno)
				{
					status = GNDCHLDFORKFLD;
					gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(10) ERR_GTMSECSHRSTART, 3,
							RTS_ERROR_TEXT("Client"), process_id,
							ERR_TEXT, 2, RTS_ERROR_TEXT("Error spawning gtmsecshr"), errno);
				}
			}
		}
	}
	return status;
}