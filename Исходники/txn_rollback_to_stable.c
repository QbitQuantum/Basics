/*
 * __txn_rollback_to_stable_lookaside_fixup --
 *	Remove any updates that need to be rolled back from the lookaside file.
 */
static int
__txn_rollback_to_stable_lookaside_fixup(WT_SESSION_IMPL *session)
{
	WT_CONNECTION_IMPL *conn;
	WT_CURSOR *cursor;
	WT_DECL_RET;
	WT_DECL_TIMESTAMP(rollback_timestamp)
	WT_ITEM las_addr, las_key, las_timestamp;
	WT_TXN_GLOBAL *txn_global;
	uint64_t las_counter, las_txnid, remove_cnt;
	uint32_t las_id, session_flags;

	conn = S2C(session);
	cursor = NULL;
	remove_cnt = 0;
	session_flags = 0;		/* [-Werror=maybe-uninitialized] */
	WT_CLEAR(las_timestamp);

	/*
	 * Copy the stable timestamp, otherwise we'd need to lock it each time
	 * it's accessed. Even though the stable timestamp isn't supposed to be
	 * updated while rolling back, accessing it without a lock would
	 * violate protocol.
	 */
	txn_global = &S2C(session)->txn_global;
	__wt_readlock(session, &txn_global->rwlock);
	__wt_timestamp_set(&rollback_timestamp, &txn_global->stable_timestamp);
	__wt_readunlock(session, &txn_global->rwlock);

	__wt_las_cursor(session, &cursor, &session_flags);

	/* Discard pages we read as soon as we're done with them. */
	F_SET(session, WT_SESSION_NO_CACHE);

	/* Walk the file. */
	for (; (ret = cursor->next(cursor)) == 0; ) {
		WT_ERR(cursor->get_key(cursor, &las_id, &las_addr, &las_counter,
		    &las_txnid, &las_timestamp, &las_key));

		/* Check the file ID so we can skip durable tables */
		if (__bit_test(conn->stable_rollback_bitstring, las_id))
			continue;

		/*
		 * Entries with no timestamp will have a timestamp of zero,
		 * which will fail the following check and cause them to never
		 * be removed.
		 */
		if (__wt_timestamp_cmp(
		    &rollback_timestamp, las_timestamp.data) < 0) {
			WT_ERR(cursor->remove(cursor));
			++remove_cnt;
		}
	}
	WT_ERR_NOTFOUND_OK(ret);
err:	WT_TRET(__wt_las_cursor_close(session, &cursor, session_flags));
	/*
	 * If there were races to remove records, we can over-count. Underflow
	 * isn't fatal, but check anyway so we don't skew low over time.
	 */
	if (remove_cnt > conn->las_record_cnt)
		conn->las_record_cnt = 0;
	else if (remove_cnt > 0)
		(void)__wt_atomic_sub64(&conn->las_record_cnt, remove_cnt);

	F_CLR(session, WT_SESSION_NO_CACHE);

	return (ret);
}