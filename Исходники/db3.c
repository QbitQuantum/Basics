static int db3stat(dbiIndex dbi, unsigned int flags)
{
    DB * db = dbi->dbi_db;
#if (DB_VERSION_MAJOR == 4 && DB_VERSION_MINOR >= 3)
    DB_TXN * txnid = NULL;
#endif
    int rc = 0;

    assert(db != NULL);
#if defined(DB_FAST_STAT)
    if (flags)
	flags = DB_FAST_STAT;
    else
#endif
	flags = 0;
    dbi->dbi_stats = _free(dbi->dbi_stats);
#if (DB_VERSION_MAJOR == 4 && DB_VERSION_MINOR >= 3)
    rc = db->stat(db, txnid, &dbi->dbi_stats, flags);
#else
    rc = db->stat(db, &dbi->dbi_stats, flags);
#endif
    rc = cvtdberr(dbi, "db->stat", rc, _debug);
    return rc;
}