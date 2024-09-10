/*ARGSUSED*/
static void *
mdb_umem_handler(size_t nbytes, size_t align, uint_t flags)
{
#ifdef _KMDB

	/*
	 * kmdb has a fixed, dedicated VA range in which to play.  This range
	 * won't change size while the debugger is running, regardless of how
	 * long we wait.  As a result, the only sensible course of action is
	 * to fail the request.  If we're here, however, the request was made
	 * with UM_SLEEP.  The caller is thus not expecting a NULL back.  We'll
	 * have to fail the current dcmd set.
	 */
	if (mdb.m_depth > 0) {
		warn("failed to allocate %lu bytes -- recovering\n",
		    (ulong_t)nbytes);

		kmdb_print_stack();

		longjmp(mdb.m_frame->f_pcb, MDB_ERR_NOMEM);
	}

#else

	/*
	 * mdb, on the other hand, can afford to wait, as someone may actually
	 * free something.
	 */
	if (errno == EAGAIN) {
		void *ptr = NULL;
		char buf[64];

		(void) mdb_iob_snprintf(buf, sizeof (buf),
		    "[ sleeping for %lu bytes of free memory ... ]",
		    (ulong_t)nbytes);

		(void) mdb_iob_puts(mdb.m_err, buf);
		(void) mdb_iob_flush(mdb.m_err);

		do {
			(void) poll(NULL, 0, 1000);
			if (align != 0)
				ptr = memalign(align, nbytes);
			else
				ptr = malloc(nbytes);
		} while (ptr == NULL && errno == EAGAIN);

		if (ptr != NULL)
			return (ptr);

		(void) memset(buf, '\b', strlen(buf));
		(void) mdb_iob_puts(mdb.m_err, buf);
		(void) mdb_iob_flush(mdb.m_err);

		(void) memset(buf, ' ', strlen(buf));
		(void) mdb_iob_puts(mdb.m_err, buf);
		(void) mdb_iob_flush(mdb.m_err);

		(void) memset(buf, '\b', strlen(buf));
		(void) mdb_iob_puts(mdb.m_err, buf);
		(void) mdb_iob_flush(mdb.m_err);
	}
#endif

	die("failed to allocate %lu bytes -- terminating\n", (ulong_t)nbytes);

	/*NOTREACHED*/

	return (NULL);
}