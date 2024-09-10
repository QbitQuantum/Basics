/*
 * __wt_schema_rename --
 *	WT_SESSION::rename.
 */
int
__wt_schema_rename(WT_SESSION_IMPL *session,
    const char *uri, const char *newuri, const char *cfg[])
{
	WT_DATA_SOURCE *dsrc;
	WT_DECL_RET;
	const char *oldname, *newname;

	WT_UNUSED(cfg);

	/* Disallow renames to/from the WiredTiger name space. */
	WT_RET(__wt_schema_name_check(session, uri));
	WT_RET(__wt_schema_name_check(session, newuri));

	/*
	 * We track rename operations, if we fail in the middle, we want to
	 * back it all out.
	 */
	WT_RET(__wt_meta_track_on(session));

	oldname = uri;
	newname = newuri;
	if (WT_PREFIX_SKIP(oldname, "file:")) {
		if (!WT_PREFIX_SKIP(newname, "file:"))
			WT_RET_MSG(session, EINVAL,
			    "rename target type must match URI: %s to %s",
			    uri, newuri);
		ret = __rename_file(session, uri, newuri);
	} else if (WT_PREFIX_SKIP(oldname, "table:")) {
		if (!WT_PREFIX_SKIP(newname, "table:"))
			WT_RET_MSG(session, EINVAL,
			    "rename target type must match URI: %s to %s",
			    uri, newuri);
		ret = __rename_table(session, oldname, newname);
	} else if ((ret = __wt_schema_get_source(session, oldname, &dsrc)) == 0)
		ret = dsrc->rename(dsrc,
		    &session->iface, oldname, newname, cfg[1]);

	WT_TRET(__wt_meta_track_off(session, ret != 0));

	/* If we didn't find a metadata entry, map that error to ENOENT. */
	return (ret == WT_NOTFOUND ? ENOENT : ret);
}