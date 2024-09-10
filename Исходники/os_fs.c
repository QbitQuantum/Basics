/*
 * __win_fs_rename --
 *	Rename a file.
 */
static int
__win_fs_rename(WT_FILE_SYSTEM *file_system,
    WT_SESSION *wt_session, const char *from, const char *to, uint32_t flags)
{
	DWORD windows_error;
	WT_DECL_RET;
	WT_DECL_ITEM(from_wide);
	WT_DECL_ITEM(to_wide);
	WT_SESSION_IMPL *session;

	WT_UNUSED(file_system);
	WT_UNUSED(flags);
	session = (WT_SESSION_IMPL *)wt_session;

	WT_ERR(__wt_to_utf16_string(session, from, &from_wide));
	WT_ERR(__wt_to_utf16_string(session, to, &to_wide));

	/*
	 * Check if file exists since Windows does not override the file if
	 * it exists.
	 */
	if (GetFileAttributesW(to_wide->data) != INVALID_FILE_ATTRIBUTES)
		if (DeleteFileW(to_wide->data) == FALSE) {
			windows_error = __wt_getlasterror();
			__wt_errx(session,
			    "%s: file-rename: DeleteFileW: %s",
			    to, __wt_formatmessage(session, windows_error));
			WT_ERR(__wt_map_windows_error(windows_error));
		}

	if (MoveFileW(from_wide->data, to_wide->data) == FALSE) {
		windows_error = __wt_getlasterror();
		__wt_errx(session,
		    "%s to %s: file-rename: MoveFileW: %s",
		    from, to, __wt_formatmessage(session, windows_error));
		WT_ERR(__wt_map_windows_error(windows_error));
	}

err:	__wt_scr_free(session, &from_wide);
	__wt_scr_free(session, &to_wide);
	return (ret);
}