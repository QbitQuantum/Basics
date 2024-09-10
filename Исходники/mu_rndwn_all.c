int mu_rndwn_all(void)
{
	int 			save_errno, fname_len, exit_status = SS_NORMAL, shmid, tmp_exit_status;
	char			entry[MAX_ENTRY_LEN];
	FILE			*pf;
	char			*fname, *fgets_res;
	shm_parms		*parm_buff;

	if (NULL == (pf = POPEN(IPCS_CMD_STR ,"r")))
        {
		save_errno = errno;
		gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(8) ERR_SYSCALL, 5, RTS_ERROR_LITERAL("POPEN()"), CALLFROM, save_errno);
                return ERR_MUNOTALLSEC;
        }
	fname = (char *)malloc(MAX_FN_LEN + 1);
	while (NULL != (FGETS(entry, SIZEOF(entry), pf, fgets_res)) && entry[0] != '\n')
	{
		tmp_exit_status = SS_NORMAL;
		parm_buff = get_shm_parm(entry);
		if (NULL == parm_buff)
		{
			exit_status = ERR_MUNOTALLSEC;
			continue;
		}
		mu_rndwn_all_helper(parm_buff, fname, &exit_status, &tmp_exit_status);
		if ((SS_NORMAL == exit_status) && (SS_NORMAL != tmp_exit_status))
			exit_status = tmp_exit_status;
		if (mu_rndwn_all_helper_error)
		{	/* Encountered a runtime error while processing this ipc. Make sure we return with
			 * MUNOTALLSEC and reset this static variable before starting processing on next ipc.
			 */
			mu_rndwn_all_helper_error = FALSE;
			if (SS_NORMAL == exit_status)
				exit_status = ERR_MUNOTALLSEC;
		}
		if (NULL != parm_buff)
			free(parm_buff);
	}
	pclose(pf);
	free(fname);
	return exit_status;
}