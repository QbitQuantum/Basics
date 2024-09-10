static void
test_reopen(const char *path)
{
	PMEMlogpool *log1 = pmemlog_create(path, PMEMLOG_MIN_POOL,
			S_IWUSR | S_IRUSR);
	if (!log1)
		FATAL("!create");

	PMEMlogpool *log2 = pmemlog_open(path);
	if (log2)
		FATAL("pmemlog_open should not succeed");

	if (errno != EWOULDBLOCK)
		FATAL("!pmemlog_open failed but for unexpected reason");

	pmemlog_close(log1);

	log2 = pmemlog_open(path);
	if (!log2)
		FATAL("pmemlog_open should succeed after close");

	pmemlog_close(log2);

	UNLINK(path);
}