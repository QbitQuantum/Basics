int
doloop(DB_ENV *dbenv)
{
    DB *dbp;
    DBT key, data;
    char buf[BUFSIZE], *rbuf;
    int ret;
    u_int32_t db_flags;

    dbp = NULL;
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));
    ret = 0;

    for (;;) {
	if (dbp == NULL) {
	    if ((ret = db_create(&dbp, dbenv, 0)) != 0)
		return (ret);

	    db_flags = DB_AUTO_COMMIT | DB_CREATE;

	    if ((ret = dbp->open(dbp,
		NULL, DATABASE, NULL, DB_BTREE, db_flags, 0)) != 0) {
		dbenv->err(dbenv, ret, "DB->open");
		goto err;
	    }
	}

	printf("QUOTESERVER> ");
	fflush(stdout);

	if (fgets(buf, sizeof(buf), stdin) == NULL)
	    break;
	if (strtok(&buf[0], " \t\n") == NULL) {
	    switch ((ret = print_stocks(dbp))) {
	    case 0:
		continue;
	    default:
		dbp->err(dbp, ret, "Error traversing data");
		goto err;
	    }
	}
	rbuf = strtok(NULL, " \t\n");
	if (rbuf == NULL || rbuf[0] == '\0') {
	    if (strncmp(buf, "exit", 4) == 0 ||
		strncmp(buf, "quit", 4) == 0)
		break;
	    dbenv->errx(dbenv, "Format: TICKER VALUE");
	    continue;
	}

	key.data = buf;
	key.size = (u_int32_t)strlen(buf);

	data.data = rbuf;
	data.size = (u_int32_t)strlen(rbuf);

	if ((ret = dbp->put(dbp, NULL, &key, &data, 0)) != 0)
	{
	    dbp->err(dbp, ret, "DB->put");
	    if (ret != DB_KEYEXIST)
		goto err;
	}
    }
err: if (dbp != NULL)
	(void)dbp->close(dbp, DB_NOSYNC);

    return (ret);
}