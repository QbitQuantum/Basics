/*
 * __curds_remove --
 *	WT_CURSOR.remove method for the data-source cursor type.
 */
static int
__curds_remove(WT_CURSOR *cursor)
{
	WT_CURSOR *source;
	WT_DECL_RET;
	WT_SESSION_IMPL *session;

	source = ((WT_CURSOR_DATA_SOURCE *)cursor)->source;

	CURSOR_REMOVE_API_CALL(cursor, session, NULL);

	WT_STAT_CONN_INCR(session, cursor_remove);
	WT_STAT_DATA_INCR(session, cursor_remove);
	WT_STAT_DATA_INCRV(session, cursor_remove_bytes, cursor->key.size);

	WT_ERR(__curds_txn_enter(session, true));

	WT_ERR(__curds_key_set(cursor));
	ret = __curds_cursor_resolve(cursor, source->remove(source));

err:	__curds_txn_leave(session);

	CURSOR_UPDATE_API_END(session, ret);
	return (ret);
}