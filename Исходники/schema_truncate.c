/*
 * __truncate_dsrc --
 *	WT_SESSION::truncate for a data-source without a truncate operation.
 */
static int
__truncate_dsrc(WT_SESSION_IMPL *session, const char *uri)
{
	WT_CURSOR *cursor;
	WT_DECL_RET;
	const char *cfg[2];

	/* Open a cursor and traverse the object, removing every entry. */
	cfg[0] = WT_CONFIG_BASE(session, session_open_cursor);
	cfg[1] = NULL;
	WT_RET(__wt_open_cursor(session, uri, NULL, cfg, &cursor));
	while ((ret = cursor->next(cursor)) == 0)
		WT_ERR(cursor->remove(cursor));
	WT_ERR_NOTFOUND_OK(ret);

err:	WT_TRET(cursor->close(cursor));
	return (ret);
}