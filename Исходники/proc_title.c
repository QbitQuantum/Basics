void
proc_title_set(const char *format, ...)
{
#ifndef PS_USE_NONE
	va_list ap;
	int buflen;

#ifdef PS_USE_CLOBBER_ARGV
	/* If ps_buffer is a pointer, it might still be null */
	if (!ps_buffer)
		return;
#endif

	/* Update ps_buffer to contain both fixed part and activity */
	va_start(ap, format);
	buflen = vsnprintf(ps_buffer,
		  ps_buffer_size - ps_sentinel_size, format, ap);
	va_end(ap);

	if (buflen < 0)
		return;

	/* Transmit new setting to kernel, if necessary */
#ifdef PS_USE_SETPROCTITLE
	setproctitle("-%s", ps_buffer);
#endif

#ifdef PS_USE_PSTAT
	{
		union pstun pst;

		pst.pst_command = ps_buffer;
		pstat(PSTAT_SETCMD, pst, strlen(ps_buffer), 0, 0);
	}
#endif /* PS_USE_PSTAT */

#ifdef PS_USE_PS_STRINGS
    static char *argvstr[2];
    argvstr[0] = ps_buffer;
	PS_STRINGS->ps_nargvstr = 1;
	PS_STRINGS->ps_argvstr = argvstr;
#endif /* PS_USE_PS_STRINGS */

#ifdef PS_USE_CLOBBER_ARGV
	{
		/* clobber remainder of old status string */
		if (ps_last_status_len > (size_t)buflen)
			memset(ps_buffer + buflen, PS_PADDING, ps_last_status_len - buflen);
		ps_last_status_len = buflen;
	}
#endif /* PS_USE_CLOBBER_ARGV */

#ifdef PS_USE_WIN32
	{
		/*
		 * Win32 does not support showing any changed arguments. To make it at
		 * all possible to track which backend is doing what, we create a
		 * named object that can be viewed with for example Process Explorer.
		 */
		static HANDLE ident_handle = INVALID_HANDLE_VALUE;
		char name[PS_BUFFER_SIZE + 32];

		if (ident_handle != INVALID_HANDLE_VALUE)
			CloseHandle(ident_handle);

		sprintf(name, "pgident(%d): %s", MyProcPid, ps_buffer);

		ident_handle = CreateEvent(NULL, TRUE, FALSE, name);
	}
#endif /* PS_USE_WIN32 */
#endif /* not PS_USE_NONE */
}