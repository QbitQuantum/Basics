/*
 * Call this to update the ps status display to a fixed prefix plus an
 * indication of what you're currently doing passed in the argument.
 */
void
set_ps_display(const char *activity)
{
#ifndef PS_USE_NONE
	/* no ps display for stand-alone backend */
	if (!IsUnderPostmaster)
		return;

#ifdef PS_USE_CLOBBER_ARGV
	/* If ps_buffer is a pointer, it might still be null */
	if (!ps_buffer)
		return;
#endif

	/* Update ps_buffer to contain both fixed part and activity */
	StrNCpy(ps_buffer + ps_buffer_fixed_size, activity,
			ps_buffer_size - ps_buffer_fixed_size);

	/* Transmit new setting to kernel, if necessary */

#ifdef PS_USE_SETPROCTITLE
	setproctitle("%s", ps_buffer);
#endif

#ifdef PS_USE_PSTAT
	{
		union pstun pst;

		pst.pst_command = ps_buffer;
		pstat(PSTAT_SETCMD, pst, strlen(ps_buffer), 0, 0);
	}
#endif   /* PS_USE_PSTAT */

#ifdef PS_USE_PS_STRINGS
	PS_STRINGS->ps_nargvstr = 1;
	PS_STRINGS->ps_argvstr = ps_buffer;
#endif   /* PS_USE_PS_STRINGS */

#ifdef PS_USE_CLOBBER_ARGV
	{
		int			buflen;

		/* pad unused memory */
		buflen = strlen(ps_buffer);
		MemSet(ps_buffer + buflen, PS_PADDING, ps_buffer_size - buflen);
	}
#endif   /* PS_USE_CLOBBER_ARGV */
#endif   /* not PS_USE_NONE */
}