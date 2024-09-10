static int
cursor_scope_ops(WT_CURSOR *cursor)
{
	struct {
		const char *key;
		const char *value;
		int (*apply)(WT_CURSOR *);
	} *op, ops[] = {
		{ "key1", "value1", cursor->insert, },
		{ "key1", "value2", cursor->update, },
		{ "key1", "value2", cursor->search, },
		{ "key1", "value2", cursor->remove, },
		{ NULL, NULL, NULL }
	};
	WT_SESSION *session;
	const char *key, *value;
	char keybuf[10], valuebuf[10];
	int ret;

	session = cursor->session;

	for (op = ops; op->key != NULL; op++) {
		key = value = NULL;

		/*! [cursor scope operation] */
		(void)snprintf(keybuf, sizeof(keybuf), "%s", op->key);
		cursor->set_key(cursor, keybuf);
		(void)snprintf(valuebuf, sizeof(valuebuf), "%s", op->value);
		cursor->set_value(cursor, valuebuf);

		/*
		 * The application must keep the key and value memory valid
		 * until the next operation that positions the cursor.
		 * Modifying either the key or value buffers is not permitted.
		 */

		/* Apply the operation (insert, update, search or remove). */
		if ((ret = op->apply(cursor)) != 0) {
			fprintf(stderr, "Error performing the operation: %s\n",
			    session->strerror(session, ret));
			return (ret);
		}

		/*
		 * Except for WT_CURSOR::insert, the cursor has been positioned
		 * and no longer references application memory, so application
		 * buffers can be safely overwritten.
		 */
		if (op->apply != cursor->insert) {
			strcpy(keybuf, "no key");
			strcpy(valuebuf, "no value");
		}

		/*
		 * Check that get_key/value behave as expected after the
		 * operation.
		 */
		if ((ret = cursor->get_key(cursor, &key)) != 0 ||
		    (op->apply != cursor->remove &&
		    (ret = cursor->get_value(cursor, &value)) != 0)) {
			fprintf(stderr, "Error in get_key/value: %s\n",
			     session->strerror(session, ret));
			return (ret);
		}

		/*
		 * Except for WT_CURSOR::insert (which does not position the
		 * cursor), the application now has pointers to memory owned
		 * by the cursor.  Modifying the memory referenced by either
		 * key or value is not permitted.
		 */

		/* Check that the cursor's key and value are what we expect. */
		if (op->apply != cursor->insert)
			if (key == keybuf ||
			    (op->apply != cursor->remove &&
			    value == valuebuf)) {
				fprintf(stderr,
				    "Cursor points at application memory!\n");
				return (EINVAL);
			}

		if (strcmp(key, op->key) != 0 ||
		    (op->apply != cursor->remove &&
		    strcmp(value, op->value) != 0)) {
			fprintf(stderr, "Unexpected key / value!\n");
			return (EINVAL);
		}
		/*! [cursor scope operation] */
	}

	return (0);
}