/*
 * __wt_las_sweep --
 *	Sweep the lookaside table.
 */
int
__wt_las_sweep(WT_SESSION_IMPL *session)
{
	WT_CONNECTION_IMPL *conn;
	WT_CURSOR *cursor;
	WT_DECL_ITEM(las_addr);
	WT_DECL_ITEM(las_key);
	WT_DECL_RET;
	WT_ITEM *key;
	uint64_t cnt, las_counter, las_txnid;
	uint32_t las_id, session_flags;
	int notused;

	conn = S2C(session);
	cursor = NULL;
	key = &conn->las_sweep_key;
	session_flags = 0;		/* [-Werror=maybe-uninitialized] */

	WT_ERR(__wt_scr_alloc(session, 0, &las_addr));
	WT_ERR(__wt_scr_alloc(session, 0, &las_key));

	WT_ERR(__wt_las_cursor(session, &cursor, &session_flags));

	/*
	 * If we're not starting a new sweep, position the cursor using the key
	 * from the last call (we don't care if we're before or after the key,
	 * just roughly in the same spot is fine).
	 */
	if (conn->las_sweep_call != 0 && key->data != NULL) {
		__wt_cursor_set_raw_key(cursor, key);
		if ((ret = cursor->search_near(cursor, &notused)) != 0)
			goto srch_notfound;
	}

	/*
	 * The sweep server wakes up every 10 seconds (by default), it's a slow
	 * moving thread. Try to review the entire lookaside table once every 5
	 * minutes, or every 30 calls.
	 *
	 * The reason is because the lookaside table exists because we're seeing
	 * cache/eviction pressure (it allows us to trade performance and disk
	 * space for cache space), and it's likely lookaside blocks are being
	 * evicted, and reading them back in doesn't help things. A trickier,
	 * but possibly better, alternative might be to review all lookaside
	 * blocks in the cache in order to get rid of them, and slowly review
	 * lookaside blocks that have already been evicted.
	 *
	 * We can't know for sure how many records are in the lookaside table,
	 * the cursor insert and remove statistics aren't updated atomically.
	 * Start with reviewing 100 rows, and if it takes more than the target
	 * number of calls to finish, increase the number of rows checked on
	 * each call; if it takes less than the target calls to finish, then
	 * decrease the number of rows reviewed on each call (but never less
	 * than 100).
	 */
#define	WT_SWEEP_LOOKASIDE_MIN_CNT	100
#define	WT_SWEEP_LOOKASIDE_PASS_TARGET	 30
	++conn->las_sweep_call;
	if ((cnt = conn->las_sweep_cnt) < WT_SWEEP_LOOKASIDE_MIN_CNT)
		cnt = conn->las_sweep_cnt = WT_SWEEP_LOOKASIDE_MIN_CNT;

	/* Walk the file. */
	for (; cnt > 0 && (ret = cursor->next(cursor)) == 0; --cnt) {
		/*
		 * If the loop terminates after completing a work unit, we will
		 * continue the table sweep next time. Get a local copy of the
		 * sweep key, we're going to reset the cursor; do so before
		 * calling cursor.remove, cursor.remove can discard our hazard
		 * pointer and the page could be evicted from underneath us.
		 */
		if (cnt == 1) {
			WT_ERR(__wt_cursor_get_raw_key(cursor, key));
			if (!WT_DATA_IN_ITEM(key))
				WT_ERR(__wt_buf_set(
				    session, key, key->data, key->size));
		}

		WT_ERR(cursor->get_key(cursor,
		    &las_id, las_addr, &las_counter, &las_txnid, las_key));

		/*
		 * If the on-page record transaction ID associated with the
		 * record is globally visible, the record can be discarded.
		 *
		 * Cursor opened overwrite=true: won't return WT_NOTFOUND should
		 * another thread remove the record before we do, and the cursor
		 * remains positioned in that case.
		 */
		if (__wt_txn_visible_all(session, las_txnid))
			WT_ERR(cursor->remove(cursor));
	}

	/*
	 * When reaching the lookaside table end or the target number of calls,
	 * adjust the row count. Decrease/increase the row count depending on
	 * if the number of calls is less/more than the target.
	 */
	if (ret == WT_NOTFOUND ||
	    conn->las_sweep_call > WT_SWEEP_LOOKASIDE_PASS_TARGET) {
		if (conn->las_sweep_call < WT_SWEEP_LOOKASIDE_PASS_TARGET &&
		    conn->las_sweep_cnt > WT_SWEEP_LOOKASIDE_MIN_CNT)
			conn->las_sweep_cnt -= WT_SWEEP_LOOKASIDE_MIN_CNT;
		if (conn->las_sweep_call > WT_SWEEP_LOOKASIDE_PASS_TARGET)
			conn->las_sweep_cnt += WT_SWEEP_LOOKASIDE_MIN_CNT;
	}

srch_notfound:
	if (ret == WT_NOTFOUND)
		conn->las_sweep_call = 0;

	WT_ERR_NOTFOUND_OK(ret);

	if (0) {
err:		__wt_buf_free(session, key);
	}

	WT_TRET(__wt_las_cursor_close(session, &cursor, session_flags));

	__wt_scr_free(session, &las_addr);
	__wt_scr_free(session, &las_key);

	return (ret);
}