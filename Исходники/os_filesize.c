/*
 * __wt_filesize_name --
 *	Return the size of a file in bytes, given a file name.
 */
int
__wt_filesize_name(
    WT_SESSION_IMPL *session, const char *filename, wt_off_t *sizep)
{
	WT_DECL_RET;
	WIN32_FILE_ATTRIBUTE_DATA data;
	char *path;

	WT_RET(__wt_filename(session, filename, &path));

	ret = GetFileAttributesExA(path, GetFileExInfoStandard, &data);

	__wt_free(session, path);

	if (ret != 0) {
		*sizep =
		    ((int64_t)data.nFileSizeHigh << 32) | data.nFileSizeLow;
		return (0);
	}

	WT_RET_MSG(session, __wt_errno(), "%s: GetFileAttributesEx", filename);
}