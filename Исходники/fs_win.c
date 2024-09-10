int fs_move(const char *oldpath, const char *newpath)
{
	int rc = ERROR_SUCCESS;
	wchar_t *old_w = utf8_to_wchar(oldpath);
	wchar_t *new_w = utf8_to_wchar(newpath);

	if ((old_w == NULL) || (new_w == NULL)) {
		rc = GetLastError();
		goto out;
	}

	if (MoveFileW(old_w, new_w) == 0) {
		rc = GetLastError();
	}

out:
	free(old_w);
	free(new_w);
	return rc;
}