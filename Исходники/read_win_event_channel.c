/* Update the log position of a bookmark */
int update_bookmark(EVT_HANDLE evt, os_channel *channel)
{
	DWORD size = 0;
	DWORD count = 0;
	wchar_t *buffer = NULL;
	int result = 0;
	EVT_HANDLE bookmark = NULL;
	FILE *fp = NULL;
	char tmp_file[OS_MAXSTR];

	/* Create bookmark temporary file name */
	snprintf(
		tmp_file,
		sizeof(tmp_file),
		"%s/%s-XXXXXX",
		TMP_DIR,
		channel->evt_log
	);

	replace_slash(tmp_file);

	if ((bookmark = EvtCreateBookmark(NULL)) == NULL)
	{
		log2file(
			"%s: ERROR: Could not EvtCreateBookmark() bookmark (%s) for (%s) which returned (%lu)",
			ARGV0,
			channel->bookmark_filename,
			channel->evt_log,
			GetLastError()
		);

		return(0);
	}

	if (!EvtUpdateBookmark(bookmark, evt))
	{
		log2file(
			"%s: ERROR: Could not EvtUpdateBookmark() bookmark (%s) for (%s) which returned (%lu)",
			ARGV0,
			channel->bookmark_filename,
			channel->evt_log,
			GetLastError()
		);

		return(0);
	}

	/* Make initial call to determine buffer size */
	result = EvtRender(NULL, bookmark, EvtRenderBookmark, 0, NULL, &size, &count);

	if (result != FALSE || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
	{
		log2file(
			"%s: ERROR: Could not EvtRender() to get buffer size to update bookmark (%s) for (%s) which returned (%lu)",
			ARGV0,
			channel->bookmark_filename,
			channel->evt_log,
			GetLastError()
		);

		return(0);
	}

	if ((buffer = calloc(size, 1)) == NULL)
	{
		log2file(
			"%s: ERROR: Could not calloc() memory to save bookmark (%s) for (%s) which returned [(%d)-(%s)]",
			ARGV0,
			channel->bookmark_filename,
			channel->evt_log,
			errno,
			strerror(errno)
		);

		return(0);
	}

	if (!EvtRender(NULL, bookmark, EvtRenderBookmark, size, buffer, &size, &count))
	{
		log2file(
			"%s: ERROR: Could not EvtRender() bookmark (%s) for (%s) which returned (%lu)",
			ARGV0,
			channel->bookmark_filename,
			channel->evt_log,
			GetLastError()
		);

		return(0);
	}

	if (mkstemp_ex(tmp_file))
	{
		log2file(
			"%s: ERROR: Could not mkstemp_ex() temporary bookmark (%s) for (%s)",
			ARGV0,
			tmp_file,
			channel->evt_log
		);

		return(0);
	}

	if ((fp = fopen(tmp_file, "w")) == NULL)
	{
		log2file(
			"%s: ERROR: Could not fopen() temporary bookmark (%s) for (%s) which returned [(%d)-(%s)]",
			ARGV0,
			tmp_file,
			channel->evt_log,
			errno,
			strerror(errno)
		);

		goto error;
	}

	if ((fwrite(buffer, 1, size, fp)) < size)
	{
		log2file(
			"%s: ERROR: Could not fwrite() to temporary bookmark (%s) for (%s) which returned [(%d)-(%s)]",
			ARGV0,
			tmp_file,
			channel->evt_log,
			errno,
			strerror(errno)
		);

		goto error;
	}

	fclose(fp);

	if (rename_ex(tmp_file, channel->bookmark_filename))
	{
		log2file(
			"%s: ERROR: Could not rename_ex() temporary bookmark (%s) to (%s) for (%s)",
			ARGV0,
			tmp_file,
			channel->bookmark_filename,
			channel->evt_log
		);

		goto error;
	}

	/* success */
	return(1);

error:
	if (fp)
		fclose(fp);

	if (unlink(tmp_file))
	{
		log2file(DELETE_ERROR, ARGV0, tmp_file, errno, strerror(errno));
	}

	return(0);
}