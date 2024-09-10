int repl_log_fd2fp(FILE **fp, int fd)
{
	int fclose_res;

	/* For stats log file, we need to have FCLOSEd *fp because a later open() in repl_log_init() might return the same file
	 * descriptor as a previously closed stats log file. In that case, FCLOSE if done here affects the newly opened file and
	 * FDOPEN will fail returning NULL for the file pointer. */
	if (NULL != *fp)
		FCLOSE(*fp, fclose_res);
	*fp = FDOPEN(fd, "a");
	assert(NULL != *fp); /* we don't expect FDOPEN to fail */
	return(SS_NORMAL);
}