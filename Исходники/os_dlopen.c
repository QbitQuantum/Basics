/*
 * __wt_dlopen --
 *	Open a dynamic library.
 */
int
__wt_dlopen(WT_SESSION_IMPL *session, const char *path, WT_DLH **dlhp)
{
	DWORD windows_error;
	WT_DECL_RET;
	WT_DLH *dlh;

	WT_RET(__wt_calloc_one(session, &dlh));
	WT_ERR(__wt_strdup(session, path, &dlh->name));
	WT_ERR(__wt_strdup(session, path == NULL ? "local" : path, &dlh->name));

	/* NULL means load from the current binary */
	if (path == NULL) {
		if (GetModuleHandleExW(
		    0, NULL, (HMODULE *)&dlh->handle) == FALSE) {
			windows_error = __wt_getlasterror();
			__wt_errx(session,
			    "GetModuleHandleExW: %s: %s",
			    path, __wt_formatmessage(session, windows_error));
			WT_ERR(__wt_map_windows_error(windows_error));
		}
	} else {
		// TODO: load dll here
		DebugBreak();
	}

	*dlhp = dlh;
	if (0) {
err:		__wt_free(session, dlh->name);
		__wt_free(session, dlh);
	}
	return (ret);
}