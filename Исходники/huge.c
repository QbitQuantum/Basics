static void
run(CONFIG *cp, int bigkey, size_t bytes)
{
	WT_CONNECTION *conn;
	WT_SESSION *session;
	WT_CURSOR *cursor;
	uint64_t keyno;
	int ret;
	void *p;

	big[bytes - 1] = '\0';

	printf(SIZET_FMT "%s%s: %s %s big %s\n",
	    bytes < MEGABYTE ? bytes :
	    (bytes < GIGABYTE ? bytes / MEGABYTE : bytes / GIGABYTE),
	    bytes < MEGABYTE ? "" :
	    (bytes < GIGABYTE ?
	    (bytes % MEGABYTE == 0 ? "" : "+") :
	    (bytes % GIGABYTE == 0 ? "" : "+")),
	    bytes < MEGABYTE ? "B" : (bytes < GIGABYTE ? "MB" : "GB"),
	    cp->uri, cp->config, bigkey ? "key" : "value");

	testutil_make_work_dir(home);

	/*
	 * Open/create the database, connection, session and cursor; set the
	 * cache size large, we don't want to try and evict anything.
	 */
	if ((ret = wiredtiger_open(
	    home, NULL, "create,cache_size=10GB", &conn)) != 0)
		testutil_die(ret, "wiredtiger_open");
	if ((ret = conn->open_session(conn, NULL, NULL, &session)) != 0)
		testutil_die(ret, "WT_CONNECTION.open_session");
	if ((ret = session->create(session, cp->uri, cp->config)) != 0)
		testutil_die(ret,
		    "WT_SESSION.create: %s %s", cp->uri, cp->config);
	if ((ret =
	    session->open_cursor(session, cp->uri, NULL, NULL, &cursor)) != 0)
		testutil_die(ret, "WT_SESSION.open_cursor: %s", cp->uri);

	/* Set the key/value. */
	if (bigkey)
		cursor->set_key(cursor, big);
	else if (cp->recno) {
		keyno = 1;
		cursor->set_key(cursor, keyno);
	} else
		cursor->set_key(cursor, "key001");
	cursor->set_value(cursor, big);

	/* Insert the record (use update, insert discards the key). */
	if ((ret = cursor->update(cursor)) != 0)
		testutil_die(ret, "WT_CURSOR.insert");

	/* Retrieve the record and check it. */
	if ((ret = cursor->search(cursor)) != 0)
		testutil_die(ret, "WT_CURSOR.search");
	if (bigkey && (ret = cursor->get_key(cursor, &p)) != 0)
		testutil_die(ret, "WT_CURSOR.get_key");
	if ((ret = cursor->get_value(cursor, &p)) != 0)
		testutil_die(ret, "WT_CURSOR.get_value");
	if (memcmp(p, big, bytes) != 0)
		testutil_die(0,
		    "retrieved big key/value item did not match original");

	/* Remove the record. */
	if ((ret = cursor->remove(cursor)) != 0)
		testutil_die(ret, "WT_CURSOR.remove");

	if ((ret = conn->close(conn, NULL)) != 0)
		testutil_die(ret, "WT_CONNECTION.close");

	big[bytes - 1] = 'a';
}