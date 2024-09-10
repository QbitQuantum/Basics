/*
 * __wt_btree_stat_init --
 *	Initialize the Btree statistics.
 */
int
__wt_btree_stat_init(WT_SESSION_IMPL *session, WT_CURSOR_STAT *cst)
{
	WT_BM *bm;
	WT_BTREE *btree;
	WT_DECL_RET;
	WT_DSRC_STATS **stats;
	WT_REF *next_walk;

	btree = S2BT(session);
	bm = btree->bm;
	stats = btree->dhandle->stats;

	WT_RET(bm->stat(bm, session, stats[0]));

	WT_STAT_SET(session, stats, btree_fixed_len, btree->bitcnt);
	WT_STAT_SET(session, stats, btree_maximum_depth, btree->maximum_depth);
	WT_STAT_SET(session, stats, btree_maxintlkey, btree->maxintlkey);
	WT_STAT_SET(session, stats, btree_maxintlpage, btree->maxintlpage);
	WT_STAT_SET(session, stats, btree_maxleafkey, btree->maxleafkey);
	WT_STAT_SET(session, stats, btree_maxleafpage, btree->maxleafpage);
	WT_STAT_SET(session, stats, btree_maxleafvalue, btree->maxleafvalue);

	/* Everything else is really, really expensive. */
	if (!F_ISSET(cst, WT_CONN_STAT_ALL))
		return (0);

	/*
	 * Clear the statistics we're about to count.
	 */
	WT_STAT_SET(session, stats, btree_column_deleted, 0);
	WT_STAT_SET(session, stats, btree_column_fix, 0);
	WT_STAT_SET(session, stats, btree_column_internal, 0);
	WT_STAT_SET(session, stats, btree_column_rle, 0);
	WT_STAT_SET(session, stats, btree_column_variable, 0);
	WT_STAT_SET(session, stats, btree_entries, 0);
	WT_STAT_SET(session, stats, btree_overflow, 0);
	WT_STAT_SET(session, stats, btree_row_internal, 0);
	WT_STAT_SET(session, stats, btree_row_leaf, 0);

	next_walk = NULL;
	while ((ret = __wt_tree_walk(
	    session, &next_walk, 0)) == 0 && next_walk != NULL) {
		WT_WITH_PAGE_INDEX(session,
		    ret = __stat_page(session, next_walk->page, stats));
		WT_RET(ret);
	}
	return (ret == WT_NOTFOUND ? 0 : ret);
}