int
main(int argc, char **argv)
{
    char *log_file = NULL;
    char *queue_dir = NULL;
    char *list[2];
    int num_to_send = DEFAULT_NUM, chunk;
    int fd;
    FTS *fts;
    FTSENT *ftsent;
    int piece, npieces;
    char filename[PATH_MAX];

    err_prog_name(argv[0]);

    OPTIONS("[-l log] [-n num] queuedir")
	NUMBER('n', num_to_send)
	STRING('l', log_file)
    ENDOPTS

    if (argc != 2)
	usage();

    if (log_file)
	err_set_log(log_file);

    queue_dir = argv[1];
    list[0] = queue_dir;
    list[1] = NULL;

    fts = fts_open(list, FTS_PHYSICAL|FTS_COMFOLLOW, fts_sort);
    if (fts == NULL)
    {
	err("fts failed on `%s'", queue_dir);
	exit(1);
    }

    ftsent = fts_read(fts);
    if (ftsent == NULL || ftsent->fts_info != FTS_D)
    {
	err("not a directory: %s", queue_dir);
	exit(1);
    }

    ftsent = fts_children(fts, 0);
    if (ftsent == NULL && errno)
    {
	err("*ftschildren failed");
	exit(1);
    }

    for (chunk = 1; ftsent != NULL; ftsent = ftsent->fts_link)
    {
	/*
	 * Skip non-files and ctm_smail tmp files (ones starting with `.')
	 */
	if (ftsent->fts_info != FTS_F || ftsent->fts_name[0] == '.')
	    continue;

	snprintf(filename, sizeof(filename), "%s/%s", queue_dir,
	    ftsent->fts_name);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
	    err("*open: %s", filename);
	    exit(1);
	}

	if (run_sendmail(fd))
	    exit(1);

	close(fd);
	
	if (unlink(filename) < 0)
	{
	    err("*unlink: %s", filename);
	    exit(1);
	}
	
	/*
	 * Deduce the delta, piece number, and number of pieces from
	 * the name of the file in the queue.  Ideally, we should be
	 * able to get the mail alias name too.
	 *
	 * NOTE: This depends intimately on the queue name used in ctm_smail.
	 */
	npieces = atoi(&ftsent->fts_name[ftsent->fts_namelen-3]);
	piece = atoi(&ftsent->fts_name[ftsent->fts_namelen-7]);
	err("%.*s %d/%d sent", (int)(ftsent->fts_namelen-8), ftsent->fts_name,
		piece, npieces);

	if (chunk++ == num_to_send)
	    break;
    }

    fts_close(fts);

    return(0);
}