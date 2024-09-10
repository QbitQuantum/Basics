/*! [thread scan] */
void *
scan_thread(void *conn_arg)
{
	WT_CONNECTION *conn;
	WT_CURSOR *cursor;
	WT_SESSION *session;
	const char *key, *value;
	int ret;

	conn = conn_arg;
	ret = conn->open_session(conn, NULL, NULL, &session);
	ret = session->open_cursor(
	    session, "table:access", NULL, NULL, &cursor);

	/* Show all records. */
	while ((ret = cursor->next(cursor)) == 0) {
		ret = cursor->get_key(cursor, &key);
		ret = cursor->get_value(cursor, &value);

		printf("Got record: %s : %s\n", key, value);
	}
	if (ret != WT_NOTFOUND)
		fprintf(stderr,
		    "WT_CURSOR.next: %s\n", session->strerror(session, ret));

	return (NULL);
}