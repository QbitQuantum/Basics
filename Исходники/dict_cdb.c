static DICT *dict_cdbq_open(const char *path, int dict_flags)
{
    DICT_CDBQ *dict_cdbq;
    struct stat st;
    char   *cdb_path;
    int     fd;

    cdb_path = concatenate(path, CDB_SUFFIX, (char *) 0);

    if ((fd = open(cdb_path, O_RDONLY)) < 0)
	return (dict_surrogate(DICT_TYPE_CDB, path, O_RDONLY, dict_flags,
			       "open database %s: %m", cdb_path));

    dict_cdbq = (DICT_CDBQ *) dict_alloc(DICT_TYPE_CDB,
					 cdb_path, sizeof(*dict_cdbq));
#if defined(TINYCDB_VERSION)
    if (cdb_init(&(dict_cdbq->cdb), fd) != 0)
	msg_fatal("dict_cdbq_open: unable to init %s: %m", cdb_path);
#else
    cdb_init(&(dict_cdbq->cdb), fd);
#endif
    dict_cdbq->dict.lookup = dict_cdbq_lookup;
    dict_cdbq->dict.close = dict_cdbq_close;
    dict_cdbq->dict.stat_fd = fd;
    if (fstat(fd, &st) < 0)
	msg_fatal("dict_dbq_open: fstat: %m");
    dict_cdbq->dict.mtime = st.st_mtime;
    dict_cdbq->dict.owner.uid = st.st_uid;
    dict_cdbq->dict.owner.status = (st.st_uid != 0);
    close_on_exec(fd, CLOSE_ON_EXEC);

    /*
     * Warn if the source file is newer than the indexed file, except when
     * the source file changed only seconds ago.
     */
    if (stat(path, &st) == 0
	&& st.st_mtime > dict_cdbq->dict.mtime
	&& st.st_mtime < time((time_t *) 0) - 100)
	msg_warn("database %s is older than source file %s", cdb_path, path);

    /*
     * If undecided about appending a null byte to key and value, choose to
     * try both in query mode.
     */
    if ((dict_flags & (DICT_FLAG_TRY1NULL | DICT_FLAG_TRY0NULL)) == 0)
	dict_flags |= DICT_FLAG_TRY0NULL | DICT_FLAG_TRY1NULL;
    dict_cdbq->dict.flags = dict_flags | DICT_FLAG_FIXED;
    if (dict_flags & DICT_FLAG_FOLD_FIX)
	dict_cdbq->dict.fold_buf = vstring_alloc(10);

    myfree(cdb_path);
    return (&dict_cdbq->dict);
}