/* Given a journal file name, this function opens that file explicitly without going through "jnl_ensure_open" */
int repl_open_jnl_file_by_name(repl_ctl_element *tmp_ctl, int jnl_fn_len, char *jnl_fn, int *fd_ptr, void *stat_buf_ptr)
{
	int		tmp_fd;
	int		status;
#ifdef UNIX
	struct stat	stat_buf;
#elif defined(VMS)
	struct FAB	fab;
	struct NAM	stat_buf;
#else
#error Unsupported platform
#endif

	tmp_ctl->jnl_fn_len = jnl_fn_len;
	memcpy(tmp_ctl->jnl_fn, jnl_fn, jnl_fn_len);
	tmp_ctl->jnl_fn[jnl_fn_len] = '\0';
	status = SS_NORMAL;

	/* Open Journal File */
#	ifdef UNIX
	OPENFILE(tmp_ctl->jnl_fn, O_RDONLY, tmp_fd);
	if (0 > tmp_fd)
	{
		status = errno;
		assert(FALSE);
	}
	if (SS_NORMAL == status)
	{
		FSTAT_FILE(tmp_fd, &stat_buf, status);
		if (0 > status)
		{
			status = errno;
			assert(FALSE);
		}
#		ifdef __MVS
		else if (-1 == gtm_zos_tag_to_policy(tmp_fd, TAG_BINARY))
		{
			status = errno;
			assert(FALSE);
		}
#		endif
	}
	*((struct stat *)stat_buf_ptr) = stat_buf;
#	elif defined(VMS)
	fab = cc$rms_fab;
	fab.fab$l_fna = tmp_ctl->jnl_fn;
	fab.fab$b_fns = tmp_ctl->jnl_fn_len;
	fab.fab$l_fop = FAB$M_UFO;
	fab.fab$b_fac = FAB$M_GET | FAB$M_PUT | FAB$M_BIO;
	fab.fab$b_shr = FAB$M_SHRPUT | FAB$M_SHRGET | FAB$M_UPI;
	stat_buf      = cc$rms_nam;
	fab.fab$l_nam = &stat_buf;
	fab.fab$l_dna = JNL_EXT_DEF;
	fab.fab$b_dns = SIZEOF(JNL_EXT_DEF) - 1;
	status = sys$open(&fab);
	if (RMS$_NORMAL == status)
	{
		status = SS_NORMAL;
		tmp_fd = fab.fab$l_stv;
	}
	assert(SS_NORMAL == status);
	*((struct NAM *)stat_buf_ptr) = stat_buf;
#	endif
	REPL_DPRINT2("CTL INIT :  Direct open of file %s\n", tmp_ctl->jnl_fn);
	*fd_ptr = tmp_fd;
	return status;
}