int gtmsource()
{
	int			status, log_init_status, waitpid_res, save_errno;
	char			print_msg[1024], tmpmsg[1024];
	gd_region		*reg, *region_top;
	sgmnt_addrs		*csa, *repl_csa;
	boolean_t		all_files_open, isalive;
	pid_t			pid, ppid, procgp;
	seq_num			read_jnl_seqno, jnl_seqno;
	unix_db_info		*udi;
	gtmsource_local_ptr_t	gtmsource_local;
	boolean_t		this_side_std_null_coll;
	int			null_fd, rc;

	memset((uchar_ptr_t)&jnlpool, 0, SIZEOF(jnlpool_addrs));
	call_on_signal = gtmsource_sigstop;
	ESTABLISH_RET(gtmsource_ch, SS_NORMAL);
	if (-1 == gtmsource_get_opt())
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_MUPCLIERR);
	if (gtmsource_options.shut_down)
	{	/* Wait till shutdown time nears even before going to "jnlpool_init". This is because the latter will return
		 * with the ftok semaphore and access semaphore held and we do not want to be holding those locks (while
		 * waiting for the user specified timeout to expire) as that will affect new GTM processes and/or other
		 * MUPIP REPLIC commands that need these locks for their function.
		 */
		if (0 < gtmsource_options.shutdown_time)
		{
			repl_log(stdout, TRUE, TRUE, "Waiting for %d seconds before signalling shutdown\n",
												gtmsource_options.shutdown_time);
			LONG_SLEEP(gtmsource_options.shutdown_time);
		} else
			repl_log(stdout, TRUE, TRUE, "Signalling shutdown immediate\n");
	} else if (gtmsource_options.start)
	{
		repl_log(stdout, TRUE, TRUE, "Initiating START of source server for secondary instance [%s]\n",
			gtmsource_options.secondary_instname);
	}
	if (gtmsource_options.activate && (ROOTPRIMARY_SPECIFIED == gtmsource_options.rootprimary))
	{	/* MUPIP REPLIC -SOURCE -ACTIVATE -UPDOK has been specified. We need to open the gld and db regions now
		 * in case this is a secondary -> primary transition. This is so we can later switch journal files in all
		 * journaled regions when the transition actually happens inside "gtmsource_rootprimary_init". But since
		 * we have not yet done a "jnlpool_init", we dont know if updates are disabled in it or not. Although we
		 * need to do the gld/db open only if updates are currently disabled in the jnlpool, we do this always
		 * because once we do a jnlpool_init, we will come back with the ftok on the jnlpool held and that has
		 * issues with later db open since we will try to hold the db ftok as part of db open and the ftok logic
		 * currently has assumptions that a process holds only one ftok at any point in time.
		 */
		assert(NULL == gd_header);
		gvinit();
		all_files_open = region_init(FALSE);
		if (!all_files_open)
		{
			gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_NOTALLDBOPN);
			gtmsource_exit(ABNORMAL_SHUTDOWN);
		}
	}
	jnlpool_init(GTMSOURCE, gtmsource_options.start, &is_jnlpool_creator);
	/* is_jnlpool_creator == TRUE ==> this process created the journal pool
	 * is_jnlpool_creator == FALSE ==> journal pool already existed and this process simply attached to it.
	 */
	if (gtmsource_options.shut_down)
		gtmsource_exit(gtmsource_shutdown(FALSE, NORMAL_SHUTDOWN) - NORMAL_SHUTDOWN);
	else if (gtmsource_options.activate)
		gtmsource_exit(gtmsource_mode_change(GTMSOURCE_MODE_ACTIVE_REQUESTED) - NORMAL_SHUTDOWN);
	else if (gtmsource_options.deactivate)
		gtmsource_exit(gtmsource_mode_change(GTMSOURCE_MODE_PASSIVE_REQUESTED) - NORMAL_SHUTDOWN);
	else if (gtmsource_options.checkhealth)
		gtmsource_exit(gtmsource_checkhealth() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.changelog)
		 gtmsource_exit(gtmsource_changelog() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.showbacklog)
		gtmsource_exit(gtmsource_showbacklog() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.stopsourcefilter)
		gtmsource_exit(gtmsource_stopfilter() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.jnlpool)
		gtmsource_exit(gtmsource_jnlpool() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.losttncomplete)
		gtmsource_exit(gtmsource_losttncomplete() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.needrestart)
		gtmsource_exit(gtmsource_needrestart() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.showfreeze)
		gtmsource_exit(gtmsource_showfreeze() - NORMAL_SHUTDOWN);
	else if (gtmsource_options.setfreeze)
		gtmsource_exit(gtmsource_setfreeze() - NORMAL_SHUTDOWN);
	else if (!gtmsource_options.start)
	{
		assert(CLI_PRESENT == cli_present("STATSLOG"));
		gtmsource_exit(gtmsource_statslog() - NORMAL_SHUTDOWN);
	}
	assert(gtmsource_options.start);
#	ifndef REPL_DEBUG_NOBACKGROUND
	/* Set "child_server_running" to FALSE before forking off child. Wait for it to be set to TRUE by the child. */
	gtmsource_local = jnlpool.gtmsource_local;
	gtmsource_local->child_server_running = FALSE;
	FORK(pid);
	if (0 > pid)
	{
		save_errno = errno;
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_JNLPOOLSETUP, 0,
			ERR_TEXT, 2, RTS_ERROR_LITERAL("Could not fork source server"), save_errno);
	} else if (0 < pid)
	{	/* Parent. Wait until child sets "child_server_running" to FALSE. That is an indication that the child
		 * source server has completed its initialization phase and is all set so the parent command can return.
		 */
		while (isalive = is_proc_alive(pid, 0))	/* note : intended assignment */
		{
			if (gtmsource_local->child_server_running)
				break;
			/* To take care of reassignment of PIDs, the while condition should be && with the condition
			 * (PPID of pid == process_id)
			 */
			SHORT_SLEEP(GTMSOURCE_WAIT_FOR_SRV_START);
			WAITPID(pid, &status, WNOHANG, waitpid_res); /* Release defunct child if dead */
		}
		if (isalive)
		{	/* Child process is alive and started with no issues */
			if (0 != (save_errno = rel_sem(SOURCE, JNL_POOL_ACCESS_SEM)))
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_JNLPOOLSETUP, 0,
					ERR_TEXT, 2, RTS_ERROR_LITERAL("Error in rel_sem"), save_errno);
			ftok_sem_release(jnlpool.jnlpool_dummy_reg, TRUE, TRUE);
		} else
		{	/* Child source server process errored out at startup and is no longer alive.
			 * If we were the one who created the journal pool, let us clean it up.
			 */
			repl_log(stdout, TRUE, TRUE, "Source server startup failed. See source server log file\n");
			if (is_jnlpool_creator)
				status = gtmsource_shutdown(TRUE, NORMAL_SHUTDOWN);
		}
		/* If the parent is killed (or crashes) between the fork and exit, checkhealth may not detect that startup
		 * is in progress - parent forks and dies, the system will release sem 0 and 1, checkhealth might test the
		 * value of sem 1 before the child grabs sem 1.
		 */
		gtmsource_exit(isalive ? SRV_ALIVE : SRV_ERR);
	}
	/* Point stdin to /dev/null */
	OPENFILE("/dev/null", O_RDONLY, null_fd);
	if (0 > null_fd)
		rts_error_csa(CSA_ARG(NULL) ERR_REPLERR, RTS_ERROR_LITERAL("Failed to open /dev/null for read"), errno, 0);
	FCNTL3(null_fd, F_DUPFD, 0, rc);
	if (0 > rc)
		rts_error_csa(CSA_ARG(NULL) ERR_REPLERR, RTS_ERROR_LITERAL("Failed to set stdin to /dev/null"), errno, 0);
	CLOSEFILE(null_fd, rc);
	if (0 > rc)
		rts_error_csa(CSA_ARG(NULL) ERR_REPLERR, RTS_ERROR_LITERAL("Failed to close /dev/null"), errno, 0);
	/* The parent process (source server startup command) will be holding the ftok semaphore and jnlpool access semaphore
	 * at this point. The variables that indicate this would have been copied over to the child during the fork. This will
	 * make the child think it is actually holding them as well when actually it is not. Reset those variables in the child
	 * to ensure they do not misrepresent the holder of those semaphores.
	 */
	ftok_sem_reg = NULL;
	udi = FILE_INFO(jnlpool.jnlpool_dummy_reg);
	assert(udi->grabbed_ftok_sem);
	udi->grabbed_ftok_sem = FALSE;
	assert(holds_sem[SOURCE][JNL_POOL_ACCESS_SEM]);
	holds_sem[SOURCE][JNL_POOL_ACCESS_SEM] = FALSE;
	assert(!holds_sem[SOURCE][SRC_SERV_COUNT_SEM]);
	/* Start child source server initialization */
	is_src_server = TRUE;
	OPERATOR_LOG_MSG;
	process_id = getpid();
	/* Reinvoke secshr related initialization with the child's pid */
	INVOKE_INIT_SECSHR_ADDRS;
	/* Initialize mutex socket, memory semaphore etc. before any "grab_lock" is done by this process on the journal pool.
	 * Note that the initialization would already have been done by the parent receiver startup command but we need to
	 * redo the initialization with the child process id.
	 */
	assert(mutex_per_process_init_pid && (mutex_per_process_init_pid != process_id));
	mutex_per_process_init();
	START_HEARTBEAT_IF_NEEDED;
	ppid = getppid();
	log_init_status = repl_log_init(REPL_GENERAL_LOG, &gtmsource_log_fd, gtmsource_options.log_file);
	assert(SS_NORMAL == log_init_status);
	repl_log_fd2fp(&gtmsource_log_fp, gtmsource_log_fd);
	if (-1 == (procgp = setsid()))
		send_msg_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_JNLPOOLSETUP, 0, ERR_TEXT, 2,
				RTS_ERROR_LITERAL("Source server error in setsid"), errno);
#	endif /* REPL_DEBUG_NOBACKGROUND */
	if (ZLIB_CMPLVL_NONE != gtm_zlib_cmp_level)
		gtm_zlib_init();	/* Open zlib shared library for compression/decompression */
	REPL_DPRINT1("Setting up regions\n");
	gvinit();

	/* We use the same code dse uses to open all regions but we must make sure they are all open before proceeding. */
	all_files_open = region_init(FALSE);
	if (!all_files_open)
	{
		gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_NOTALLDBOPN);
		gtmsource_exit(ABNORMAL_SHUTDOWN);
	}
	/* Determine primary side null subscripts collation order */
	/* Also check whether all regions have same null collation order */
	this_side_std_null_coll = -1;
	for (reg = gd_header->regions, region_top = gd_header->regions + gd_header->n_regions; reg < region_top; reg++)
	{
		csa = &FILE_INFO(reg)->s_addrs;
		if (this_side_std_null_coll != csa->hdr->std_null_coll)
		{
			if (-1 == this_side_std_null_coll)
				this_side_std_null_coll = csa->hdr->std_null_coll;
			else
			{
				gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_NULLCOLLDIFF);
				gtmsource_exit(ABNORMAL_SHUTDOWN);
			}
		}
		if (!REPL_ALLOWED(csa) && JNL_ALLOWED(csa))
		{
			gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(4) ERR_REPLOFFJNLON, 2, DB_LEN_STR(reg));
			gtmsource_exit(ABNORMAL_SHUTDOWN);
		}
		if (reg->read_only && REPL_ALLOWED(csa))
		{
			gtm_putmsg_csa(CSA_ARG(NULL) VARLSTCNT(6) ERR_JNLPOOLSETUP, 0, ERR_TEXT, 2,
				   RTS_ERROR_LITERAL("Source Server does not have write permissions to one or "
					             "more database files that are replicated"));
			gtmsource_exit(ABNORMAL_SHUTDOWN);
		}
	}
	/* Initialize source server alive/dead state related fields in "gtmsource_local" before the ftok semaphore is released */
	gtmsource_local->gtmsource_pid = process_id;
	gtmsource_local->gtmsource_state = GTMSOURCE_START;
	if (is_jnlpool_creator)
	{
		DEBUG_ONLY(jnlpool.jnlpool_ctl->jnlpool_creator_pid = process_id);
		gtmsource_seqno_init(this_side_std_null_coll);
		if (ROOTPRIMARY_SPECIFIED == gtmsource_options.rootprimary)
		{	/* Created the journal pool as a root primary. Append a history record to the replication instance file.
			 * Invoke the function "gtmsource_rootprimary_init" to do that.
			 */
			gtmsource_rootprimary_init(jnlpool.jnlpool_ctl->jnl_seqno);
		}
	}
	/* after this point we can no longer have the case where all the regions are unreplicated/non-journaled. */
#	ifndef REPL_DEBUG_NOBACKGROUND
	/* It is necessary for every process that is using the ftok semaphore to increment the counter by 1. This is used
	 * by the last process that shuts down to delete the ftok semaphore when it notices the counter to be 0.
	 * Note that the parent source server startup command would have done an increment of the ftok counter semaphore
	 * for the replication instance file. But the source server process (the child) that comes here would not have done
	 * that. Do that while the parent is still holding on to the ftok semaphore waiting for our okay.
	 */
	if (!ftok_sem_incrcnt(jnlpool.jnlpool_dummy_reg))
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_JNLPOOLSETUP);
	/* Increment the source server count semaphore */
	status = incr_sem(SOURCE, SRC_SERV_COUNT_SEM);
	if (0 != status)
	{
		save_errno = errno;
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_JNLPOOLSETUP, 0, ERR_TEXT, 2,
			RTS_ERROR_LITERAL("Counter semaphore increment failure in child source server"), save_errno);
	}
#	else
	if (0 != (save_errno = rel_sem_immediate(SOURCE, JNL_POOL_ACCESS_SEM)))
	{
		rts_error_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_JNLPOOLSETUP, 0, ERR_TEXT, 2,
			RTS_ERROR_LITERAL("Error in rel_sem_immediate"), save_errno);
	}
#	endif /* REPL_DEBUG_NOBACKGROUND */

	gtmsource_srv_count++;
	gtmsource_local->child_server_running = TRUE;	/* At this point, the parent startup command will stop waiting for child */
	gtm_event_log_init();
	/* Log source server startup command line first */
	SPRINTF(tmpmsg, "%s %s\n", cli_lex_in_ptr->argv[0], cli_lex_in_ptr->in_str);
	repl_log(gtmsource_log_fp, TRUE, TRUE, tmpmsg);

	SPRINTF(tmpmsg, "GTM Replication Source Server with Pid [%d] started for Secondary Instance [%s]",
		process_id, gtmsource_local->secondary_instname);
	sgtm_putmsg(print_msg, VARLSTCNT(4) ERR_REPLINFO, 2, LEN_AND_STR(tmpmsg));
	repl_log(gtmsource_log_fp, TRUE, TRUE, print_msg);
	if (is_jnlpool_creator)
	{
		repl_log(gtmsource_log_fp, TRUE, TRUE, "Created jnlpool with shmid = [%d] and semid = [%d]\n",
			jnlpool.repl_inst_filehdr->jnlpool_shmid, jnlpool.repl_inst_filehdr->jnlpool_semid);
	} else
		repl_log(gtmsource_log_fp, TRUE, TRUE, "Attached to existing jnlpool with shmid = [%d] and semid = [%d]\n",
			jnlpool.repl_inst_filehdr->jnlpool_shmid, jnlpool.repl_inst_filehdr->jnlpool_semid);
	gtm_event_log(GTM_EVENT_LOG_ARGC, "MUPIP", "REPLINFO", print_msg);
#	ifdef GTM_TLS
	if (REPL_TLS_REQUESTED)
	{
		repl_do_tls_init(gtmsource_log_fp);
		assert(REPL_TLS_REQUESTED || PLAINTEXT_FALLBACK);
	}
#	endif
	if (jnlpool.jnlpool_ctl->freeze)
	{
		last_seen_freeze_flag = jnlpool.jnlpool_ctl->freeze;
		sgtm_putmsg(print_msg, VARLSTCNT(3) ERR_REPLINSTFROZEN, 1, jnlpool.repl_inst_filehdr->inst_info.this_instname);
		repl_log(gtmsource_log_fp, TRUE, FALSE, print_msg);
		sgtm_putmsg(print_msg, VARLSTCNT(3) ERR_REPLINSTFREEZECOMMENT, 1, jnlpool.jnlpool_ctl->freeze_comment);
		repl_log(gtmsource_log_fp, TRUE, TRUE, print_msg);
	}
	gtmsource_local->jnlfileonly = gtmsource_options.jnlfileonly;
	do
	{ 	/* If mode is passive, go to sleep. Wakeup every now and then and check to see if I have to become active. */
		gtmsource_state = gtmsource_local->gtmsource_state = GTMSOURCE_START;
		if ((gtmsource_local->mode == GTMSOURCE_MODE_PASSIVE) && (gtmsource_local->shutdown == NO_SHUTDOWN))
		{
			gtmsource_poll_actions(FALSE);
			SHORT_SLEEP(GTMSOURCE_WAIT_FOR_MODE_CHANGE);
			continue;
		}
		if (GTMSOURCE_MODE_PASSIVE == gtmsource_local->mode)
		{	/* Shutdown initiated */
			assert(gtmsource_local->shutdown == SHUTDOWN);
			sgtm_putmsg(print_msg, VARLSTCNT(4) ERR_REPLINFO, 2,
				    RTS_ERROR_LITERAL("GTM Replication Source Server Shutdown signalled"));
			repl_log(gtmsource_log_fp, TRUE, TRUE, print_msg);
			gtm_event_log(GTM_EVENT_LOG_ARGC, "MUPIP", "REPLINFO", print_msg);
			break;
		}
		gtmsource_poll_actions(FALSE);
		if (GTMSOURCE_CHANGING_MODE == gtmsource_state)
			continue;
		if (GTMSOURCE_MODE_ACTIVE_REQUESTED == gtmsource_local->mode)
			gtmsource_local->mode = GTMSOURCE_MODE_ACTIVE;
		SPRINTF(tmpmsg, "GTM Replication Source Server now in ACTIVE mode using port %d", gtmsource_local->secondary_port);
		sgtm_putmsg(print_msg, VARLSTCNT(4) ERR_REPLINFO, 2, LEN_AND_STR(tmpmsg));
		repl_log(gtmsource_log_fp, TRUE, TRUE, print_msg);
		gtm_event_log(GTM_EVENT_LOG_ARGC, "MUPIP", "REPLINFO", print_msg);
		DEBUG_ONLY(repl_csa = &FILE_INFO(jnlpool.jnlpool_dummy_reg)->s_addrs;)
		assert(!repl_csa->hold_onto_crit);	/* so it is ok to invoke "grab_lock" and "rel_lock" unconditionally */
		grab_lock(jnlpool.jnlpool_dummy_reg, TRUE, HANDLE_CONCUR_ONLINE_ROLLBACK);
		if (GTMSOURCE_HANDLE_ONLN_RLBK == gtmsource_state)
		{
			repl_log(gtmsource_log_fp, TRUE, TRUE, "Starting afresh due to ONLINE ROLLBACK\n");
			repl_log(gtmsource_log_fp, TRUE, TRUE, "REPL INFO - Current Jnlpool Seqno : %llu\n",
					jnlpool.jnlpool_ctl->jnl_seqno);
			continue;
		}
		QWASSIGN(gtmsource_local->read_addr, jnlpool.jnlpool_ctl->write_addr);
		gtmsource_local->read = jnlpool.jnlpool_ctl->write;
		gtmsource_local->read_state = gtmsource_local->jnlfileonly ? READ_FILE : READ_POOL;
		read_jnl_seqno = gtmsource_local->read_jnl_seqno;
		assert(read_jnl_seqno <= jnlpool.jnlpool_ctl->jnl_seqno);
		if (read_jnl_seqno < jnlpool.jnlpool_ctl->jnl_seqno)
		{
			gtmsource_local->read_state = READ_FILE;
			QWASSIGN(gtmsource_save_read_jnl_seqno, jnlpool.jnlpool_ctl->jnl_seqno);
			gtmsource_pool2file_transition = TRUE; /* so that we read the latest gener jnl files */
		}
		rel_lock(jnlpool.jnlpool_dummy_reg);
		if (SS_NORMAL != (status = gtmsource_alloc_tcombuff()))
			rts_error_csa(CSA_ARG(NULL) VARLSTCNT(7) ERR_REPLCOMM, 0, ERR_TEXT, 2,
				  RTS_ERROR_LITERAL("Error allocating initial tcom buffer space. Malloc error"), status);
		gtmsource_filter = NO_FILTER;
		if ('\0' != gtmsource_local->filter_cmd[0])
		{
			if (SS_NORMAL == (status = repl_filter_init(gtmsource_local->filter_cmd)))
				gtmsource_filter |= EXTERNAL_FILTER;
			else
				gtmsource_exit(ABNORMAL_SHUTDOWN);
		}
		gtmsource_process();
		/* gtmsource_process returns only when mode needs to be changed to PASSIVE */
		assert(gtmsource_state == GTMSOURCE_CHANGING_MODE);
		gtmsource_ctl_close();
		gtmsource_free_msgbuff();
		gtmsource_free_tcombuff();
		gtmsource_free_filter_buff();
		gtmsource_stop_heartbeat();
		if (FD_INVALID != gtmsource_sock_fd)
			repl_close(&gtmsource_sock_fd);
		if (gtmsource_filter & EXTERNAL_FILTER)
			repl_stop_filter();
	} while (TRUE);