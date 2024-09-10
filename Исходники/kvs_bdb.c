static int
kvs_session_rename(WT_DATA_SOURCE *wtds, WT_SESSION *session,
    const char *uri, const char *newname, WT_CONFIG_ARG *config)
{
	DATA_SOURCE *ds;
	DB *db;
	WT_EXTENSION_API *wt_api;
	int ret = 0;
	const char *name;

	(void)config;				/* Unused parameters */

	ds = (DATA_SOURCE *)wtds;
	wt_api = ds->wt_api;
						/* Get the object name */
	if ((ret = uri2name(wt_api, session, uri, &name)) != 0)
		return (ret);

	if ((ret = single_thread(wtds, session, &ds->rwlock)) != 0)
		return (ret);

	if ((ret = db_create(&db, ds->dbenv, 0)) != 0)
		ESET(wt_api,
		    session, WT_ERROR, "db_create: %s", db_strerror(ret));
	else if ((ret = db->rename(db, name, NULL, newname, 0)) != 0)
		ESET(wt_api,
		    session, WT_ERROR, "Db.rename: %s", db_strerror(ret));
	/* db handle is dead */

	ETRET(unlock(wt_api, session, &ds->rwlock));
	return (ret);
}