void db_init(gd_region *reg, sgmnt_data_ptr_t tsd)
{
	static boolean_t	mutex_init_done = FALSE;
	boolean_t       	is_bg, read_only;
	char            	machine_name[MAX_MCNAMELEN];
	file_control    	*fc;
	int			gethostname_res, stat_res, mm_prot;
	int4            	status, semval, dblksize, fbwsize;
	sm_long_t       	status_l;
	sgmnt_addrs     	*csa;
	sgmnt_data_ptr_t        csd;
	struct sembuf   	sop[3];
	struct stat     	stat_buf;
	union semun		semarg;
	struct semid_ds		semstat;
	struct shmid_ds         shmstat;
	struct statvfs		dbvfs;
	uint4           	sopcnt;
	unix_db_info    	*udi;
#ifdef periodic_timer_removed
	void            	periodic_flush_check();
#endif

	error_def(ERR_CLSTCONFLICT);
	error_def(ERR_CRITSEMFAIL);
	error_def(ERR_DBNAMEMISMATCH);
	error_def(ERR_DBIDMISMATCH);
	error_def(ERR_NLMISMATCHCALC);
	error_def(ERR_REQRUNDOWN);
	error_def(ERR_SYSCALL);

	assert(tsd->acc_meth == dba_bg  ||  tsd->acc_meth == dba_mm);
	is_bg = (dba_bg == tsd->acc_meth);
	read_only = reg->read_only;
	new_dbinit_ipc = FALSE;	/* we did not create a new ipc resource */
	udi = FILE_INFO(reg);
	memset(machine_name, 0, sizeof(machine_name));
	if (GETHOSTNAME(machine_name, MAX_MCNAMELEN, gethostname_res))
		rts_error(VARLSTCNT(5) ERR_TEXT, 2, LEN_AND_LIT("Unable to get the hostname"), errno);
	assert(strlen(machine_name) < MAX_MCNAMELEN);
	csa = &udi->s_addrs;
	csa->db_addrs[0] = csa->db_addrs[1] = csa->lock_addrs[0] = NULL;   /* to help in dbinit_ch  and gds_rundown */
	reg->opening = TRUE;
	/*
	 * Create ftok semaphore for this region.
	 * We do not want to make ftok counter semaphore to be 2 for on mupip journal recover process.
	 */
	if (!ftok_sem_get(reg, !mupip_jnl_recover, GTM_ID, FALSE))
		rts_error(VARLSTCNT(4) ERR_DBFILERR, 2, DB_LEN_STR(reg));
	/*
	 * At this point we have ftok_semid sempahore based on ftok key.
	 * Any ftok conflicted region will block at this point.
	 * Say, a.dat and b.dat both has same ftok and we have process A to access a.dat and
	 * process B to access b.dat. In this case only one can continue to do db_init()
	 */
	fc = reg->dyn.addr->file_cntl;
	fc->file_type = reg->dyn.addr->acc_meth;
	fc->op = FC_READ;
	fc->op_buff = (sm_uc_ptr_t)tsd;
	fc->op_len = sizeof(*tsd);
	fc->op_pos = 1;
	dbfilop(fc);		/* Read file header */
	udi->shmid = tsd->shmid;
	udi->semid = tsd->semid;
	udi->sem_ctime = tsd->sem_ctime.ctime;
	udi->shm_ctime = tsd->shm_ctime.ctime;
	dbsecspc(reg, tsd); 	/* Find db segment size */
	if (!mupip_jnl_recover)
	{
		if (INVALID_SEMID == udi->semid)
		{
			if (0 != udi->sem_ctime || INVALID_SHMID != udi->shmid || 0 != udi->shm_ctime)
			/* We must have somthing wrong in protocol or, code, if this happens */
				GTMASSERT;
			/*
			 * Create new semaphore using IPC_PRIVATE. System guarantees a unique id.
			 */
			if (-1 == (udi->semid = semget(IPC_PRIVATE, FTOK_SEM_PER_ID, RWDALL | IPC_CREAT)))
			{
				udi->semid = INVALID_SEMID;
				rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, LEN_AND_LIT("Error with database control semget"), errno);
			}
			udi->shmid = INVALID_SHMID;	/* reset shmid so dbinit_ch does not get confused in case we go there */
			new_dbinit_ipc = TRUE;
			tsd->semid = udi->semid;
			semarg.val = GTM_ID;
			/*
			 * Following will set semaphore number 2 (=FTOK_SEM_PER_ID - 1)  value as GTM_ID.
			 * In case we have orphaned semaphore for some reason, mupip rundown will be
			 * able to identify GTM semaphores from the value and can remove.
			 */
			if (-1 == semctl(udi->semid, FTOK_SEM_PER_ID - 1, SETVAL, semarg))
				rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, LEN_AND_LIT("Error with database control semctl SETVAL"), errno);
			/*
			 * Warning: We must read the sem_ctime using IPC_STAT after SETVAL, which changes it.
			 *	    We must NOT do any more SETVAL after this. Our design is to use
			 *	    sem_ctime as creation time of semaphore.
			 */
			semarg.buf = &semstat;
			if (-1 == semctl(udi->semid, FTOK_SEM_PER_ID - 1, IPC_STAT, semarg))
				rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, LEN_AND_LIT("Error with database control semctl IPC_STAT"), errno);
			tsd->sem_ctime.ctime = udi->sem_ctime = semarg.buf->sem_ctime;
		} else
		{
			if (INVALID_SHMID == udi->shmid)
				/* if mu_rndwn_file gets standalone access of this region and
				 * somehow mupip process crashes, we can have semid != -1 but shmid == -1
				 */
				rts_error(VARLSTCNT(10) ERR_REQRUNDOWN, 4, DB_LEN_STR(reg), LEN_AND_STR(tsd->machine_name),
						ERR_TEXT, 2, LEN_AND_LIT("semid is valid but shmid is invalid"));
			semarg.buf = &semstat;
			if (-1 == semctl(udi->semid, 0, IPC_STAT, semarg))
				/* file header has valid semid but semaphore does not exists */
				rts_error(VARLSTCNT(6) ERR_REQRUNDOWN, 4, DB_LEN_STR(reg), LEN_AND_STR(tsd->machine_name));
			else if (semarg.buf->sem_ctime != tsd->sem_ctime.ctime)
				rts_error(VARLSTCNT(10) ERR_REQRUNDOWN, 4, DB_LEN_STR(reg), LEN_AND_STR(tsd->machine_name),
						ERR_TEXT, 2, LEN_AND_LIT("sem_ctime does not match"));
			if (-1 == shmctl(udi->shmid, IPC_STAT, &shmstat))
				rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
					ERR_TEXT, 2, LEN_AND_LIT("Error with database control shmctl"), errno);
			else if (shmstat.shm_ctime != tsd->shm_ctime.ctime)
				rts_error(VARLSTCNT(10) ERR_REQRUNDOWN, 4, DB_LEN_STR(reg), LEN_AND_STR(tsd->machine_name),
					ERR_TEXT, 2, LEN_AND_LIT("shm_ctime does not match"));
		}
		/* We already have ftok semaphore of this region, so just plainly do semaphore operation */
		/* This is the database access control semaphore for any region */
		sop[0].sem_num = 0; sop[0].sem_op = 0;	/* Wait for 0 */
		sop[1].sem_num = 0; sop[1].sem_op = 1;	/* Lock */
		sopcnt = 2;
		if (!read_only)
		{
			sop[2].sem_num = 1; sop[2].sem_op  = 1;	 /* increment r/w access counter */
			sopcnt = 3;
		}
		sop[0].sem_flg = sop[1].sem_flg = sop[2].sem_flg = SEM_UNDO | IPC_NOWAIT;
		SEMOP(udi->semid, sop, sopcnt, status);
		if (-1 == status)
		{
			errno_save = errno;
			gtm_putmsg(VARLSTCNT(4) ERR_CRITSEMFAIL, 2, DB_LEN_STR(reg));
			rts_error(VARLSTCNT(8) ERR_SYSCALL, 5, RTS_ERROR_LITERAL("semop()"), CALLFROM, errno_save);
		}
	} else /* for mupip_jnl_recover we were already in mu_rndwn_file and got "semid" semaphore  */
	{
		if (INVALID_SEMID == udi->semid || 0 == udi->sem_ctime)
			/* make sure mu_rndwn_file() has reset created semaphore for standalone access */
			GTMASSERT;
		if (INVALID_SHMID != udi->shmid || 0 != udi->shm_ctime)
			/* make sure mu_rndwn_file() has reset shared memory */
			GTMASSERT;
		udi->shmid = INVALID_SHMID;	/* reset shmid so dbinit_ch does not get confused in case we go there */
		new_dbinit_ipc = TRUE;
	}
	sem_incremented = TRUE;
	if (new_dbinit_ipc)
	{
		/* Create new shared memory using IPC_PRIVATE. System guarantees a unique id */
#ifdef __MVS__
		if (-1 == (status_l = udi->shmid = shmget(IPC_PRIVATE, ROUND_UP(reg->sec_size, MEGA_BOUND),
			__IPC_MEGA | IPC_CREAT | RWDALL)))
#else
		if (-1 == (status_l = udi->shmid = shmget(IPC_PRIVATE, reg->sec_size, RWDALL | IPC_CREAT)))
#endif
		{
			udi->shmid = status_l = INVALID_SHMID;
			rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
				  ERR_TEXT, 2, LEN_AND_LIT("Error with database shmget"), errno);
		}
		tsd->shmid = udi->shmid;
		if (-1 == shmctl(udi->shmid, IPC_STAT, &shmstat))
			rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
				ERR_TEXT, 2, LEN_AND_LIT("Error with database control shmctl"), errno);
		tsd->shm_ctime.ctime = udi->shm_ctime = shmstat.shm_ctime;
	}
#ifdef DEBUG_DB64
	status_l = (sm_long_t)(csa->db_addrs[0] = (sm_uc_ptr_t)do_shmat(udi->shmid, next_smseg, SHM_RND));
	next_smseg = (sm_uc_ptr_t)ROUND_UP((sm_long_t)(next_smseg + reg->sec_size), SHMAT_ADDR_INCS);
#else
	status_l = (sm_long_t)(csa->db_addrs[0] = (sm_uc_ptr_t)do_shmat(udi->shmid, 0, SHM_RND));
#endif
	if (-1 == status_l)
	{
		rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
			  ERR_TEXT, 2, LEN_AND_LIT("Error attaching to database shared memory"), errno);
	}
	csa->nl = (node_local_ptr_t)csa->db_addrs[0];
	csa->critical = (mutex_struct_ptr_t)(csa->db_addrs[0] + NODE_LOCAL_SIZE);
	assert(((int)csa->critical & 0xf) == 0); 			/* critical should be 16-byte aligned */
#ifdef CACHELINE_SIZE
	assert(0 == ((int)csa->critical & (CACHELINE_SIZE - 1)));
#endif
	/* Note: Here we check jnl_sate from database file and its value cannot change without standalone access.
	 * The jnl_buff buffer should be initialized irrespective of read/write process */
	JNL_INIT(csa, reg, tsd);
	csa->backup_buffer = (backup_buff_ptr_t)(csa->db_addrs[0] + NODE_LOCAL_SPACE + JNL_SHARE_SIZE(tsd));
	csa->lock_addrs[0] = (sm_uc_ptr_t)csa->backup_buffer + BACKUP_BUFFER_SIZE + 1;
	csa->lock_addrs[1] = csa->lock_addrs[0] + LOCK_SPACE_SIZE(tsd) - 1;
	csa->total_blks = tsd->trans_hist.total_blks;   		/* For test to see if file has extended */
	if (new_dbinit_ipc)
	{
		memset(csa->nl, 0, sizeof(*csa->nl));			/* We allocated shared storage -- we have to init it */
		if (JNL_ALLOWED(csa))
		{	/* initialize jb->cycle to a value different from initial value of jpc->cycle (0). although this is not
			 * necessary right now, in the future, the plan is to change jnl_ensure_open() to only do a cycle mismatch
			 * check in order to determine whether to call jnl_file_open() or not. this is in preparation for that.
			 */
			csa->jnl->jnl_buff->cycle = 1;
		}
	}
	if (is_bg)
		csd = csa->hdr = (sgmnt_data_ptr_t)(csa->lock_addrs[1] + 1 + CACHE_CONTROL_SIZE(tsd));
	else
	{
		csa->acc_meth.mm.mmblk_state = (mmblk_que_heads_ptr_t)(csa->lock_addrs[1] + 1);
		FSTAT_FILE(udi->fd, &stat_buf, stat_res);
		if (-1 == stat_res)
			rts_error(VARLSTCNT(5) ERR_DBFILERR, 2, DB_LEN_STR(reg), errno);
		mm_prot = read_only ? PROT_READ : (PROT_READ | PROT_WRITE);
#ifdef DEBUG_DB64
		if (-1 == (sm_long_t)(csa->db_addrs[0] = (sm_uc_ptr_t)mmap((caddr_t)get_mmseg((size_t)stat_buf.st_size),
									   (size_t)stat_buf.st_size,
									   mm_prot,
									   GTM_MM_FLAGS, udi->fd, (off_t)0)))
			rts_error(VARLSTCNT(5) ERR_DBFILERR, 2, DB_LEN_STR(reg), errno);
		put_mmseg((caddr_t)(csa->db_addrs[0]), (size_t)stat_buf.st_size);
#else
		if (-1 == (sm_long_t)(csa->db_addrs[0] = (sm_uc_ptr_t)mmap((caddr_t)NULL,
									   (size_t)stat_buf.st_size,
									   mm_prot,
									   GTM_MM_FLAGS, udi->fd, (off_t)0)))
			rts_error(VARLSTCNT(5) ERR_DBFILERR, 2, DB_LEN_STR(reg), errno);
#endif
		csa->db_addrs[1] = csa->db_addrs[0] + stat_buf.st_size - 1;
		csd = csa->hdr = (sgmnt_data_ptr_t)csa->db_addrs[0];
	}
	if (!csa->nl->glob_sec_init)
	{
		assert(new_dbinit_ipc);
		if (is_bg)
			*csd = *tsd;
		if (csd->machine_name[0])                  /* crash occured */
		{
			if (0 != memcmp(csd->machine_name, machine_name, MAX_MCNAMELEN))  /* crashed on some other node */
				rts_error(VARLSTCNT(6) ERR_CLSTCONFLICT, 4, DB_LEN_STR(reg), LEN_AND_STR(csd->machine_name));
			else
				rts_error(VARLSTCNT(6) ERR_REQRUNDOWN, 4, DB_LEN_STR(reg), LEN_AND_STR(csd->machine_name));
		}
		if (is_bg)
		{
			bt_malloc(csa);
			csa->nl->cache_off = -CACHE_CONTROL_SIZE(tsd);
			db_csh_ini(csa);
		}
		db_csh_ref(csa);
		strcpy(csa->nl->machine_name, machine_name);					/* machine name */
		assert(MAX_REL_NAME > gtm_release_name_len);
		memcpy(csa->nl->now_running, gtm_release_name, gtm_release_name_len + 1);	/* GT.M release name */
		memcpy(csa->nl->label, GDS_LABEL, GDS_LABEL_SZ - 1);				/* GDS label */
		memcpy(csa->nl->fname, reg->dyn.addr->fname, reg->dyn.addr->fname_len);		/* database filename */
		csa->nl->creation_date_time = csd->creation.date_time;
		csa->nl->highest_lbm_blk_changed = -1;
		csa->nl->wcs_timers = -1;
		csa->nl->nbb = BACKUP_NOT_IN_PROGRESS;
		csa->nl->unique_id.uid = FILE_INFO(reg)->fileid;            /* save what file we initialized this storage for */
		/* save pointers in csa to access shared memory */
		csa->nl->critical = (sm_off_t)((sm_uc_ptr_t)csa->critical - (sm_uc_ptr_t)csa->nl);
		if (JNL_ALLOWED(csa))
			csa->nl->jnl_buff = (sm_off_t)((sm_uc_ptr_t)csa->jnl->jnl_buff - (sm_uc_ptr_t)csa->nl);
		csa->nl->backup_buffer = (sm_off_t)((sm_uc_ptr_t)csa->backup_buffer - (sm_uc_ptr_t)csa->nl);
		csa->nl->hdr = (sm_off_t)((sm_uc_ptr_t)csd - (sm_uc_ptr_t)csa->nl);
		csa->nl->lock_addrs = (sm_off_t)((sm_uc_ptr_t)csa->lock_addrs[0] - (sm_uc_ptr_t)csa->nl);
		if (!read_only || is_bg)
		{
			csd->trans_hist.early_tn = csd->trans_hist.curr_tn;
			csd->max_update_array_size = csd->max_non_bm_update_array_size
				= ROUND_UP2(MAX_NON_BITMAP_UPDATE_ARRAY_SIZE(csd), UPDATE_ARRAY_ALIGN_SIZE);
			csd->max_update_array_size += ROUND_UP2(MAX_BITMAP_UPDATE_ARRAY_SIZE, UPDATE_ARRAY_ALIGN_SIZE);
			/* add current db_csh counters into the cumulative counters and reset the current counters */
#define TAB_DB_CSH_ACCT_REC(COUNTER, DUMMY1, DUMMY2)					\
				csd->COUNTER.cumul_count += csd->COUNTER.curr_count;	\
				csd->COUNTER.curr_count = 0;
#include "tab_db_csh_acct_rec.h"
#undef TAB_DB_CSH_ACCT_REC
		}
		if (!read_only)
		{
			if (is_bg)
			{
				assert(memcmp(csd, GDS_LABEL, GDS_LABEL_SZ - 1) == 0);
				LSEEKWRITE(udi->fd, (off_t)0, (sm_uc_ptr_t)csd, sizeof(sgmnt_data), errno_save);
				if (0 != errno_save)
				{
					rts_error(VARLSTCNT(9) ERR_DBFILERR, 2, DB_LEN_STR(reg),
						  ERR_TEXT, 2, LEN_AND_LIT("Error with database write"), errno_save);
				}
			}
		}
		reg->dyn.addr->ext_blk_count = csd->extension_size;
		mlk_shr_init(csa->lock_addrs[0], csd->lock_space_size, csa, (FALSE == read_only));
		DEBUG_ONLY(locknl = csa->nl;)	/* for DEBUG_ONLY LOCK_HIST macro */