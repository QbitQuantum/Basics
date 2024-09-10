static int
cursor_ops(WT_SESSION *session)
{
	WT_CURSOR *cursor;
	int ret;

	/*! [Open a cursor] */
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));
	/*! [Open a cursor] */

	/*! [Open a cursor on the metadata] */
	error_check(session->open_cursor(
	    session, "metadata:", NULL, NULL, &cursor));
	/*! [Open a cursor on the metadata] */

	{
	const char *key = "some key", *value = "some value";
	/*! [Reconfigure a cursor] */
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=false", &cursor));

	/* Reconfigure the cursor to overwrite the record. */
	error_check(cursor->reconfigure(cursor, "overwrite=true"));

	cursor->set_key(cursor, key);
	cursor->set_value(cursor, value);
	error_check(cursor->insert(cursor));
	/*! [Reconfigure a cursor] */
	}

	{
	WT_CURSOR *duplicate;
	const char *key = "some key";
	/*! [Duplicate a cursor] */
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));
	cursor->set_key(cursor, key);
	error_check(cursor->search(cursor));

	/* Duplicate the cursor. */
	error_check(
	    session->open_cursor(session, NULL, cursor, NULL, &duplicate));
	/*! [Duplicate a cursor] */
	}

	{
	/*! [boolean configuration string example] */
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite", &cursor));
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=true", &cursor));
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=1", &cursor));
	/*! [boolean configuration string example] */
	}

	error_check(session->checkpoint(session, "name=midnight"));

	{
	/*! [open a named checkpoint] */
	error_check(session->open_cursor(session,
	    "table:mytable", NULL, "checkpoint=midnight", &cursor));
	/*! [open a named checkpoint] */
	}

	{
	/*! [open the default checkpoint] */
	error_check(session->open_cursor(session,
	    "table:mytable", NULL, "checkpoint=WiredTigerCheckpoint", &cursor));
	/*! [open the default checkpoint] */
	}

	{
	/*! [Set the cursor's string key] */
				/* Set the cursor's string key. */
	const char *key = "another key";
	cursor->set_key(cursor, key);
	/*! [Set the cursor's string key] */
	}

	{
	/*! [Get the cursor's string key] */
	const char *key;	/* Get the cursor's string key. */
	error_check(cursor->get_key(cursor, &key));
	/*! [Get the cursor's string key] */
	}

	/* Switch to a recno table. */
	error_check(session->create(
	    session, "table:recno", "key_format=r,value_format=S"));
	error_check(session->open_cursor(
	    session, "table:recno", NULL, NULL, &cursor));

	{
	/*! [Set the cursor's record number key] */
	uint64_t recno = 37;	/* Set the cursor's record number key. */
	cursor->set_key(cursor, recno);
	/*! [Set the cursor's record number key] */
	}

	{
	/*! [Get the cursor's record number key] */
	uint64_t recno;		/* Get the cursor's record number key. */
	error_check(cursor->get_key(cursor, &recno));
	/*! [Get the cursor's record number key] */
	}

	/* Switch to a composite table. */
	error_check(session->create(
	    session, "table:composite", "key_format=SiH,value_format=S"));
	error_check(session->open_cursor(
	    session, "table:recno", NULL, NULL, &cursor));

	{
	/*! [Set the cursor's composite key] */
			/* Set the cursor's "SiH" format composite key. */
	cursor->set_key(cursor, "first", (int32_t)5, (uint16_t)7);
	/*! [Set the cursor's composite key] */
	}

	{
	/*! [Get the cursor's composite key] */
			/* Get the cursor's "SiH" format composite key. */
	const char *first;
	int32_t second;
	uint16_t third;
	error_check(cursor->get_key(cursor, &first, &second, &third));
	/*! [Get the cursor's composite key] */
	}

	{
	/*! [Set the cursor's string value] */
				/* Set the cursor's string value. */
	const char *value = "another value";
	cursor->set_value(cursor, value);
	/*! [Set the cursor's string value] */
	}

	{
	/*! [Get the cursor's string value] */
	const char *value;	/* Get the cursor's string value. */
	error_check(cursor->get_value(cursor, &value));
	/*! [Get the cursor's string value] */
	}

	{
	/*! [Get the cursor's raw value] */
	WT_ITEM value;		/* Get the cursor's raw value. */
	error_check(cursor->get_value(cursor, &value));
	/*! [Get the cursor's raw value] */
	}

	{
	/*! [Set the cursor's raw value] */
	WT_ITEM value;		/* Set the cursor's raw value. */
	value.data = "another value";
	value.size = strlen("another value");
	cursor->set_value(cursor, &value);
	/*! [Set the cursor's raw value] */

	error_check(cursor->insert(cursor));
	}

	/*! [Return the next record] */
	error_check(cursor->next(cursor));
	/*! [Return the next record] */

	/*! [Reset the cursor] */
	error_check(cursor->reset(cursor));
	/*! [Reset the cursor] */

	/*! [Return the previous record] */
	error_check(cursor->prev(cursor));
	/*! [Return the previous record] */

	{
	WT_CURSOR *other = NULL;
	error_check(
	    session->open_cursor(session, NULL, cursor, NULL, &other));

	{
	/*! [Cursor comparison] */
	int compare;
	error_check(cursor->compare(cursor, other, &compare));
	if (compare == 0) {
		/* Cursors reference the same key */
	} else if (compare < 0) {
		/* Cursor key less than other key */
	} else if (compare > 0) {
		/* Cursor key greater than other key */
	}
	/*! [Cursor comparison] */
	}

	{
	/*! [Cursor equality] */
	int equal;
	error_check(cursor->equals(cursor, other, &equal));
	if (equal) {
		/* Cursors reference the same key */
	}
	/*! [Cursor equality] */
	}
	}

	{
	/*! [Insert a new record or overwrite an existing record] */
	/* Insert a new record or overwrite an existing record. */
	const char *key = "some key", *value = "some value";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));
	cursor->set_key(cursor, key);
	cursor->set_value(cursor, value);
	error_check(cursor->insert(cursor));
	/*! [Insert a new record or overwrite an existing record] */
	}

	{
	/*! [Search for an exact match] */
	const char *key = "some key";
	cursor->set_key(cursor, key);
	error_check(cursor->search(cursor));
	/*! [Search for an exact match] */
	}

	cursor_search_near(cursor);

	{
	/*! [Insert a new record and fail if the record exists] */
	/* Insert a new record and fail if the record exists. */
	const char *key = "new key", *value = "some value";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=false", &cursor));
	cursor->set_key(cursor, key);
	cursor->set_value(cursor, value);
	error_check(cursor->insert(cursor));
	/*! [Insert a new record and fail if the record exists] */
	}

	error_check(session->open_cursor(
	    session, "table:recno", NULL, "append", &cursor));

	{
	/*! [Insert a new record and assign a record number] */
	/* Insert a new record and assign a record number. */
	uint64_t recno;
	const char *value = "some value";
	cursor->set_value(cursor, value);
	error_check(cursor->insert(cursor));
	error_check(cursor->get_key(cursor, &recno));
	/*! [Insert a new record and assign a record number] */
	}

	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));

	{
	/*! [Reserve a record] */
	const char *key = "some key";
	error_check(session->begin_transaction(session, NULL));
	cursor->set_key(cursor, key);
	error_check(cursor->reserve(cursor));
	error_check(session->commit_transaction(session, NULL));
	/*! [Reserve a record] */
	}

	error_check(session->create(
	    session, "table:blob", "key_format=S,value_format=u"));
	error_check(session->open_cursor(
	    session, "table:blob", NULL, NULL, &cursor));
	{
	WT_ITEM value;
	value.data = "abcdefghijklmnopqrstuvwxyz"
	    "abcdefghijklmnopqrstuvwxyz"
	    "abcdefghijklmnopqrstuvwxyz";
	value.size = strlen(value.data);
	cursor->set_key(cursor, "some key");
	cursor->set_value(cursor, &value);
	error_check(cursor->insert(cursor));
	}

	/* Modify requires an explicit transaction. */
	error_check(session->begin_transaction(session, NULL));
	{
	/*! [Modify an existing record] */
	WT_MODIFY entries[3];
	const char *key = "some key";

	/* Position the cursor. */
	cursor->set_key(cursor, key);
	error_check(cursor->search(cursor));

	/* Replace 20 bytes starting at byte offset 5. */
	entries[0].data.data = "some data";
	entries[0].data.size = strlen(entries[0].data.data);
	entries[0].offset = 5;
	entries[0].size = 20;

	/* Insert data at byte offset 40. */
	entries[1].data.data = "and more data";
	entries[1].data.size = strlen(entries[1].data.data);
	entries[1].offset = 40;
	entries[1].size = 0;

	/* Replace 2 bytes starting at byte offset 10. */
	entries[2].data.data = "and more data";
	entries[2].data.size = strlen(entries[2].data.data);
	entries[2].offset = 10;
	entries[2].size = 2;

	error_check(cursor->modify(cursor, entries, 3));
	/*! [Modify an existing record] */
	}
	error_check(session->commit_transaction(session, NULL));

	{
	/*! [Update an existing record or insert a new record] */
	const char *key = "some key", *value = "some value";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));
	cursor->set_key(cursor, key);
	cursor->set_value(cursor, value);
	error_check(cursor->update(cursor));
	/*! [Update an existing record or insert a new record] */
	}

	{
	/*! [Update an existing record and fail if DNE] */
	const char *key = "some key", *value = "some value";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=false", &cursor));
	cursor->set_key(cursor, key);
	cursor->set_value(cursor, value);
	error_check(cursor->update(cursor));
	/*! [Update an existing record and fail if DNE] */
	}

	{
	/*! [Remove a record and fail if DNE] */
	const char *key = "some key";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, "overwrite=false", &cursor));
	cursor->set_key(cursor, key);
	error_check(cursor->remove(cursor));
	/*! [Remove a record and fail if DNE] */
	}

	{
	/*! [Remove a record] */
	const char *key = "some key";
	error_check(session->open_cursor(
	    session, "table:mytable", NULL, NULL, &cursor));
	cursor->set_key(cursor, key);
	error_check(cursor->remove(cursor));
	/*! [Remove a record] */
	}

	{
	/*! [Display an error] */
	const char *key = "non-existent key";
	cursor->set_key(cursor, key);
	if ((ret = cursor->remove(cursor)) != 0) {
		fprintf(stderr,
		    "cursor.remove: %s\n", wiredtiger_strerror(ret));
		return (ret);
	}
	/*! [Display an error] */
	}

	{
	/*! [Display an error thread safe] */
	const char *key = "non-existent key";
	cursor->set_key(cursor, key);
	if ((ret = cursor->remove(cursor)) != 0) {
		fprintf(stderr,
		    "cursor.remove: %s\n",
		    cursor->session->strerror(cursor->session, ret));
		return (ret);
	}
	/*! [Display an error thread safe] */
	}

	/*! [Close the cursor] */
	error_check(cursor->close(cursor));
	/*! [Close the cursor] */

	return (0);
}