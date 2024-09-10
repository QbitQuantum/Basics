/*
 * __wt_metadata_remove --
 *	Remove a row from the metadata.
 */
int
__wt_metadata_remove(WT_SESSION_IMPL *session, const char *key)
{
	WT_CURSOR *cursor;
	WT_DECL_RET;

	if (__metadata_turtle(key))
		WT_RET_MSG(session, EINVAL,
		    "%s: remove not supported on the turtle file", key);

	WT_RET(__wt_metadata_cursor(session, NULL, &cursor));
	cursor->set_key(cursor, key);
	WT_ERR(cursor->search(cursor));
	if (WT_META_TRACKING(session))
		WT_ERR(__wt_meta_track_update(session, key));
	WT_ERR(cursor->remove(cursor));

err:	WT_TRET(cursor->close(cursor));
	return (ret);
}